#include "XInputController.h"

#include <iostream>
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "xinput.lib")

using namespace dae;

class XInputController::XInputControllerImpl
{
public:
	XInputControllerImpl()
	{
		DWORD dwResult;
		for(DWORD  iter = 0; iter < XUSER_MAX_COUNT; ++iter)
		{
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
			ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
			dwResult = XInputGetState(iter, &m_CurrentState[iter]);

			if (dwResult != ERROR_SUCCESS)
			{
				// Controller is connected
				std::cout << "Controller not detected\n";
			}
			else
			{
				++m_ConnectedControllers;
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
		for (DWORD  iter = 0; iter < 4; ++iter)
		{
			//CopyMemory(&m_PreviousState[iter], &m_CurrentState[iter], sizeof(XINPUT_STATE));
			//ZeroMemory(&m_CurrentState[iter], sizeof(XINPUT_STATE));
			XInputGetState(iter, &m_CurrentState[iter]);

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
		return m_ConnectedControllers;
		//int res{};
		//for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		//{
		//	XINPUT_STATE state;
		//	ZeroMemory(&state, sizeof(XINPUT_STATE));

		//	// Simply get the state of the controller from XInput.
		//	const DWORD dwResult = XInputGetState(i, &state);

		//	if (dwResult == ERROR_SUCCESS)
		//	{
		//		++res;
		//	}
		//}
		//return res;
	}

private:
	XINPUT_STATE m_CurrentState[XUSER_MAX_COUNT]{};
	XINPUT_STATE m_PreviousState[XUSER_MAX_COUNT]{};

	WORD m_ButtonsPressedThisFrame[XUSER_MAX_COUNT]{};
	WORD m_ButtonsReleasedThisFrame[XUSER_MAX_COUNT]{};

	float m_TriggerDZ{ .05f }; //Trigger dead zone
	float m_AnalogueDZ{ .02f }; //Analogue stick dead zone

	int m_ConnectedControllers{};
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

int XInputController::GetConnectedControllers() const
{
	return m_pImpl->GetConnectedControllers();
}
