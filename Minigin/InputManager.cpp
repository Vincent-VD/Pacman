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
				values.leftStick = rightStickValues;
				command->Execute(values);
			}
			break;
		}
	}

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

void dae::InputManager::AddCommand(int playerID, SDL_KeyCode keyboardKey, unsigned int controllerButtons, InputType inputType, const std::shared_ptr<Command>& command)
{
	m_ControllerBindings.emplace_back() = std::make_tuple(playerID, controllerButtons, inputType, command);
	m_KeyboardBindings.emplace_back() = std::make_tuple(playerID, keyboardKey, inputType, command);
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
