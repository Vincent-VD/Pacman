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

		void AddCommand(SDL_KeyCode key, unsigned int buttons, InputType inputType,const std::shared_ptr<Command>& command);

	private:
		int m_NrOfPlayers{ 0 };
		std::unique_ptr<XInputController> m_pController;
		//Keyboard* m_pKeyboard;
		std::vector<std::tuple<unsigned int, InputType, std::shared_ptr<Command>>> m_ControllerBindings{};
		std::vector<std::tuple<SDL_KeyCode, InputType, std::shared_ptr<Command>>> m_KeyboardBinding{};
	};

}
