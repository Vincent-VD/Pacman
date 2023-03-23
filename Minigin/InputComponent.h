#pragma once
#include <map>

#include "InputManager.h"
#include "RootComponent.h"
#include "XInputController.h"

namespace dae
{

	class InputComponent : public RootComponent
	{
	public:
		InputComponent(GameObject* pOwner)
			: RootComponent(pOwner)
			//, m_pController{ new XInputController(playerId) }
			//, m_pKeyboard(new Keyboard())
		{
			m_PlayerIdx = InputManager::GetInstance().GetNewPlayerId();

		}

		virtual ~InputComponent() override = default;

		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) noexcept = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) noexcept = delete;

		//void ProcessInput();
		/*bool IsPressed(XInputController::ControllerButton button) const;
		bool IsHeld(XInputController::ControllerButton button) const;
		bool IsReleased(XInputController::ControllerButton button) const;

		float GetLeftTriggerPressure() const;
		float GetRightTriggerPressure() const;
		std::pair<float, float> GetLeftStickValues() const;
		std::pair<float, float> GetRightStickValues() const;*/

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		int m_PlayerIdx;
	};

}

