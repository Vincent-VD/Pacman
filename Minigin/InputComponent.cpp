#include "InputComponent.h"

#include "InputManager.h"

void dae::InputComponent::Update()
{
	for (auto& [button, type, command] : InputManager::GetInstance().GetControllerBindings())
	{
		const auto controller{ InputManager::GetInstance().GetController() };

		//Check buttons
		switch (type)
		{
		case InputType::held:
			if (controller->IsHeld(m_PlayerIdx, button))
			{
				command->Execute();
			}
			break;
		case InputType::pressed:
			if (controller->IsPressed(m_PlayerIdx, button))
			{
				command->Execute();
			}
			break;
		case InputType::released:
			if (controller->IsReleased(m_PlayerIdx, button))
			{
				command->Execute();
			}
			break;
		case InputType::leftStick:
			{
			auto leftStickVals{ controller->GetLeftStickValues(m_PlayerIdx) };
				if(glm::length2(leftStickVals) > FLT_EPSILON * FLT_EPSILON)
				{
					InputAction values{};
					values.leftStick = leftStickVals;
					command->Execute(values);
				}
			}
		case InputType::rightStick:
			{
				auto rightStickValues{ controller->GetRightStickValues(m_PlayerIdx) };
				if (glm::length2(rightStickValues) > FLT_EPSILON * FLT_EPSILON)
				{
					InputAction values{};
					values.leftStick = rightStickValues;
					command->Execute(values);
				}
			}
		}
	}
}
