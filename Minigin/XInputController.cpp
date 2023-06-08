#include "XInputController.h"

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <Windows.h>

#include <Xinput.h>
#include <glm/glm.hpp>

using namespace dae;

class XInputController::XInputControllerImpl
{
public:
	XInputControllerImpl()
	{
		DWORD dwResult;
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
		for(DWORD  iter = 0; iter < XUSER_MAX_COUNT; ++iter)
		{
			dwResult = XInputGetState(iter, &m_CurrentState[iter]);
			m_ConnectedControllers[iter] = dwResult;

			if (dwResult != ERROR_SUCCESS)
			{
				// Controller is connected
				std::cout << "Controller not detected\n";
			}
		}
		
	}

	~XInputControllerImpl() = default;

	XInputControllerImpl(const XInputControllerImpl& other) = delete;
	XInputControllerImpl(XInputControllerImpl&& other) noexcept = delete;
	XInputControllerImpl& operator=(const XInputControllerImpl& other) = delete;
	XInputControllerImpl& operator=(XInputControllerImpl&& other) noexcept = delete;

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
		for (DWORD  iter = 0; iter < XUSER_MAX_COUNT; ++iter)
		{
			DWORD dwResult = XInputGetState(iter, &m_CurrentState[iter]);
			m_ConnectedControllers[iter] = dwResult;

			auto buttons = m_CurrentState[iter].Gamepad.wButtons ^ m_PreviousState[iter].Gamepad.wButtons;
			m_ButtonsPressedThisFrame[iter] = buttons & m_CurrentState[iter].Gamepad.wButtons;
			m_ButtonsReleasedThisFrame[iter] = buttons & (~m_CurrentState[iter].Gamepad.wButtons);
		}
	}

	bool IsHeldThisFrame(int playerId, unsigned int button) const
	{
		return m_CurrentState[playerId].Gamepad.wButtons & button;
	}
	bool IsPressedThisFrame(int playerId, unsigned int button) const
	{
		return m_ButtonsPressedThisFrame[playerId] & button;
	}
	bool IsReleasedThisFrame(int playerId, unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame[playerId] & button;
	}

	float GetLeftTriggerPressureThisFrame(int playerId) const
	{
		float res{};
		const float leftTrigger = static_cast<float>(m_CurrentState[playerId].Gamepad.bLeftTrigger) / 255;
		if (leftTrigger > m_TriggerDZ)
		{
			res = m_CurrentState[playerId].Gamepad.bLeftTrigger;
		}
		return res;
	}
	float GetRightTriggerPressureThisFrame(int playerId) const
	{
		float res{};
		const float rightTrigger = static_cast<float>(m_CurrentState[playerId].Gamepad.bRightTrigger) / 255;
		if (rightTrigger > m_TriggerDZ)
		{
			res = m_CurrentState[playerId].Gamepad.bRightTrigger;
		}
		return res;
	}

	glm::vec2 GetLeftStickValuesThisFrame(int playerId) const
	{
		const float normLX = fmaxf(-1, static_cast<float>(m_CurrentState[playerId].Gamepad.sThumbLX) / 32767);
		const float normLY = fmaxf(-1, static_cast<float>(m_CurrentState[playerId].Gamepad.sThumbLY) / 32767);
		float leftStickX = (abs(normLX) < m_TriggerDZ ? 0.f : normLX);
		float leftStickY = (abs(normLY) < m_TriggerDZ ? 0.f : normLY);
		return { leftStickX, leftStickY };								
	}																	
	glm::vec2 GetRightStickValuesThisFrame(int playerId) const			
	{
		const float normRX = fmaxf(-1, static_cast<float>(m_CurrentState[playerId].Gamepad.sThumbRX) / 32767);
		const float normRY = fmaxf(-1, static_cast<float>(m_CurrentState[playerId].Gamepad.sThumbRY) / 32767);
		float rightStickX = (abs(normRX) < m_TriggerDZ ? 0.f : normRX);
		float rightStickY = (abs(normRY) < m_TriggerDZ ? 0.f : normRY);
		return { rightStickX, rightStickY };
	}

	int GetConnectedControllers() const
	{
		int res{};
		for (int iter = 0; iter < XUSER_MAX_COUNT; ++iter)
		{
			if(m_ConnectedControllers[iter] == ERROR_SUCCESS)
			{
				++res;
			}
		}
		return res;
	}

	int GetMaxPlayerCount() const
	{
		return XUSER_MAX_COUNT;
	}

private:
	XINPUT_STATE m_CurrentState[XUSER_MAX_COUNT]{};
	XINPUT_STATE m_PreviousState[XUSER_MAX_COUNT]{};

	WORD m_ButtonsPressedThisFrame[XUSER_MAX_COUNT]{};
	WORD m_ButtonsReleasedThisFrame[XUSER_MAX_COUNT]{};

	float m_TriggerDZ{ .05f }; //Trigger dead zone
	float m_AnalogueDZ{ .02f }; //Analogue stick dead zone

	bool m_ConnectedControllers[XUSER_MAX_COUNT]{false};
};

XInputController::XInputController()
	: m_pImpl(std::make_unique<XInputControllerImpl>())
{
}

XInputController::~XInputController()
{
	//delete m_pImpl;
}

void XInputController::Update() const
{
	m_pImpl->Update();
}

bool XInputController::IsHeld(int playerId, unsigned int button) const
{
	return m_pImpl->IsHeldThisFrame(playerId, button);
}

bool XInputController::IsPressed(int playerId, unsigned int button) const
{
	return m_pImpl->IsPressedThisFrame(playerId, button);
}

bool XInputController::IsReleased(int playerId, unsigned int button) const
{
	return m_pImpl->IsReleasedThisFrame(playerId, button);
}

float XInputController::GetLeftTriggerPressure(int playerId) const
{
	return m_pImpl->GetLeftTriggerPressureThisFrame(playerId);
}

float XInputController::GetRightTriggerPressure(int playerId) const
{
	return m_pImpl->GetRightTriggerPressureThisFrame(playerId);
}

glm::vec2 XInputController::GetLeftStickValues(int playerId) const
{
	return m_pImpl->GetLeftStickValuesThisFrame(playerId);
}

glm::vec2 XInputController::GetRightStickValues(int playerId) const
{
	return m_pImpl->GetRightStickValuesThisFrame(playerId);
}

glm::vec2 XInputController::GetDPadAxisValues(int playerId) const
{
	glm::vec2 res{};
	for (const auto& [button, direction] : m_DPadDirections)
	{
		if (IsHeld(playerId, button))
		{
			res += direction;
		}
	}
	return glm::normalize(res);
}

int XInputController::GetConnectedControllers() const
{
	return m_pImpl->GetConnectedControllers();
}

int XInputController::GetMaxPlayerCount()
{
	return m_pImpl->GetMaxPlayerCount();
}
