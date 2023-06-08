#ifndef VARIABLE
#define VARIABLE

#include <string>
#include <vector>

namespace pac
{
	class MainMenuState;
	class PausedState;
	class InputState;
	class EndState;
	class IdleState;
	class WaitState;
	class LoadingState;
	
	class UIState
	{
	public:
		UIState() = default;
		virtual ~UIState() = default;

		virtual UIState* HandleInput(const std::string& /*action*/) { return nullptr; }
		virtual UIState* Update() { return nullptr; }

		virtual void OnEnter() {}
		virtual void OnExit() {}
	};

	class MainMenuState : public UIState
	{
	public:
		MainMenuState() = default;
		virtual ~MainMenuState() override = default;

		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

		virtual void OnEnter() override {}
		virtual void OnExit() override;
	};

	class PausedState : public UIState
	{
	public:
		PausedState() = default;
		virtual ~PausedState() override = default;

		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};

	class InputState : public UIState
	{
	public:
		InputState() = default;
		virtual ~InputState() override = default;

		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

		virtual void OnEnter() override {}
		virtual void OnExit() override;

	private:
		std::string m_Name;
	};

	class EndState : public UIState
	{
	public:
		EndState() = default;
		virtual ~EndState() override = default;

		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		std::vector<std::tuple<int, std::string>> m_Scores;
	};

	class IdleState : public UIState
	{
	public:
		IdleState() = default;
		virtual ~IdleState() override = default;

		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};

	class WaitState : public UIState
	{
	public:
		WaitState() = default;
		virtual ~WaitState() override = default;

		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};

	class LoadingState : public UIState
	{
	public:
		LoadingState() = default;
		virtual ~LoadingState() override = default;

		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}

#endif //UI_STATE