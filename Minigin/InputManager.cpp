#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

#include "SceneManager.h"

void dae::InputManager::Init()
{
	m_pController = std::make_unique<XInputController>();
}

bool dae::InputManager::ProcessInput()
{
	m_pController->Update();


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}

	return true;
}

void dae::InputManager::AddCommand(SDL_KeyCode keyboardKey, unsigned int controllerButtons, InputType inputType, const std::shared_ptr<Command>& command)
{
	m_ControllerBindings.emplace_back() = std::make_tuple(controllerButtons, inputType, command);
	m_KeyboardBinding.emplace_back() = std::make_tuple(keyboardKey, inputType, command);
}
