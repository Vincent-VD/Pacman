#pragma once
#include <map>

#include "Singleton.h"
#include "XInputController.h"

namespace dae
{
	class Command;
	enum class InputType;
	class GameObject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Init();

		bool ProcessInput();

		auto GetControllerBindings() const { return m_ControllerBindings; }
		XInputController* GetController() const { return m_pController.get(); }
		int GetNewPlayerId() { return m_NrOfPlayers++; }
		int GetNrOfPlayers() const { return m_NrOfPlayers; }
		int GetConnectedControllers() const { return m_pController->GetConnectedControllers(); }

		//void AddCommand(int playerID, SDL_KeyCode key, unsigned int buttons, InputType inputType,const std::shared_ptr<Command>& command);
		void AddControllerCommand(int playerID, unsigned int buttons, InputType inputType,const std::shared_ptr<Command>& command);
		void AddKeyboardCommand(int playerID, SDL_KeyCode key, InputType inputType,const std::shared_ptr<Command>& command);
		void AddAxisCommand(int playerID, InputType inputType, const std::shared_ptr<Command>& command, bool bEnableKeyboard = false);

	private:
		bool m_CanPlayerJoin{ false };
		int m_NrOfPlayers{ 0 };
		std::unique_ptr<XInputController> m_pController;
		std::vector<std::tuple<int, unsigned int, InputType, std::shared_ptr<Command>>> m_ControllerBindings{};
		std::vector<std::tuple<int, SDL_KeyCode, InputType, std::shared_ptr<Command>>> m_KeyboardBindings{};

		void CheckForPlayerJoin();
		glm::vec2 GetKeyboardAxisValues(const Uint8* keystate) const;

		const std::map<SDL_KeyCode, glm::vec2> m_KeyboardAxis {
			{ SDLK_w, { 0, 1 } },
		   { SDLK_s, { 0, -1 } },
		   { SDLK_a, { -1, 0 } },
		   { SDLK_d, { 1, 0 } }
		};
	};

}
