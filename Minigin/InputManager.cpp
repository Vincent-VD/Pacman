#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

#include "Command.h"
#include "SceneManager.h"

void dae::InputManager::Init()
{
	m_pController = std::make_unique<XInputController>();
}

bool dae::InputManager::ProcessInput()
{
	m_pController->Update();

	for (auto& [playerID, button, type, command] : m_ControllerBindings)
	{
		//Check buttons
		switch (type)
		{
		case InputType::held:
			if (m_pController->IsHeld(playerID, button))
			{
				command->Execute();
			}
			break;
		case InputType::pressed:
			if (m_pController->IsPressed(playerID, button))
			{
				command->Execute();
			}
			break;
		case InputType::released:
			if (m_pController->IsReleased(playerID, button))
			{
				command->Execute();
			}
			break;
		case InputType::leftStick:
			auto leftStickVals{ m_pController->GetLeftStickValues(playerID) };
			if (glm::length2(leftStickVals) > FLT_EPSILON * FLT_EPSILON)
			{
				InputAction values{};
				values.leftStick = leftStickVals;
				command->Execute(values);
			}
			break;
		case InputType::rightStick:
			auto rightStickValues{ m_pController->GetRightStickValues(playerID) };
			if (glm::length2(rightStickValues) > FLT_EPSILON * FLT_EPSILON)
			{
				InputAction values{};
				values.rightStick = rightStickValues;
				command->Execute(values);
			}
			break;
		case InputType::dpadAxis:
			auto dPadAxisValues{m_pController->GetDPadAxisValues(playerID)};
			if (glm::length2(dPadAxisValues) > FLT_EPSILON * FLT_EPSILON)
			{
				InputAction values{};
				values.leftStick = dPadAxisValues;
				command->Execute(values);
			}
			break;
		}
	}

	//std::cout << m_pController->GetDPadAxisValues(0).x << "  " << m_pController->GetDPadAxisValues(0).y << std::endl;

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	for (auto& [playerID, button, type, command] : m_KeyboardBindings)
	{
		if(type == InputType::held)
		{
			if(keystate[SDL_GetScancodeFromKey(button)])
			{
				command->Execute();
			}
		}
		if(type == InputType::dpadAxis)
		{
			auto keyboardAxisValues{ GetKeyboardAxisValues(keystate) };
			if (glm::length2(keyboardAxisValues) > FLT_EPSILON * FLT_EPSILON)
			{
				InputAction values{};
				values.leftStick = keyboardAxisValues;
				command->Execute(values);
			}
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		for (auto& [playerID, button, type, command] : m_KeyboardBindings)
		{
			if (e.type == SDL_KEYDOWN && type == InputType::pressed)
			{
				if(e.key.keysym.sym == button)
				{
					command->Execute();
				}
			}
			if (e.type == SDL_KEYUP && type == InputType::released)
			{
				if (e.key.keysym.sym == button)
				{
					command->Execute();
				}
			}
		}
		
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void dae::InputManager::AddControllerCommand(int playerID, unsigned buttons, InputType inputType, const std::shared_ptr<Command>& command)
{
	m_ControllerBindings.emplace_back() = std::make_tuple(playerID, buttons, inputType, command);
}

void dae::InputManager::AddKeyboardCommand(int playerID, SDL_KeyCode key, InputType inputType, const std::shared_ptr<Command>& command)
{
	m_KeyboardBindings.emplace_back() = std::make_tuple(playerID, key, inputType, command);
}

void dae::InputManager::AddAxisCommand(int playerID, InputType inputType, const std::shared_ptr<Command>& command, bool bEnableKeyboard)
{
	m_ControllerBindings.emplace_back() = std::make_tuple(playerID, 0, inputType, command);
	if(bEnableKeyboard)
	{
		m_KeyboardBindings.emplace_back() = std::make_tuple(playerID, SDLK_INSERT, inputType, command);
	}
}

void dae::InputManager::CheckForPlayerJoin()
{
	if(!m_CanPlayerJoin)
	{
		return;
	}

	for(int iter = m_NrOfPlayers; iter < m_pController->GetMaxPlayerCount(); ++iter)
	{
		if (m_pController->IsPressed(iter, static_cast<unsigned int>(XInputController::ControllerButton::Start)))
		{
			//Create new player
		}
	}
}

glm::vec2 dae::InputManager::GetKeyboardAxisValues(const Uint8* keystate) const
{
	glm::vec2 res{};
	for (const auto& [button, direction] : m_KeyboardAxis)
	{
		if (keystate[SDL_GetScancodeFromKey(button)])
		{
			res += direction;
		}
	}
	return glm::normalize(res);
}
