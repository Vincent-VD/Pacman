#pragma once
#include <string>

namespace pac
{
	class MainMenuState;
	class PausedState;
	class InputState;
	class EndState;
	class IdleState;
	class WaitState;
	class StartState;

	class UIState
	{
	public:
		UIState()
		{
			OnEnter();
		}
		virtual ~UIState()
		{
			OnExit();
		}
		virtual UIState* HandleInput(const std::string& /*action*/) { return nullptr; }
		virtual UIState* Update() { return nullptr; }

	private:
		virtual void OnEnter() {}
		virtual void OnExit() {}
	};

	class MainMenuState : public UIState
	{
	public:
		MainMenuState()
		{
			OnEnter();
		}
		virtual ~MainMenuState() override
		{
			OnExit();
		}
		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

	private:
		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};

	class PausedState : public UIState
	{
	public:
		PausedState()
		{
			OnEnter();
		}
		virtual ~PausedState() override
		{
			OnExit();
		}
		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

	private:
		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};

	class InputState : public UIState
	{
	public:
		InputState()
		{
			OnEnter();
		}
		virtual ~InputState() override
		{
			OnExit();
		}
		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

	private:
		virtual void OnEnter() override {}
		virtual void OnExit() override;
	};

	class EndState : public UIState
	{
	public:
		EndState()
		{
			OnEnter();
		}
		virtual ~EndState() override
		{
			OnExit();
		}
		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

	private:
		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};

	class IdleState : public UIState
	{
	public:
		IdleState()
		{
			OnEnter();
		}
		virtual ~IdleState() override
		{
			OnExit();
		}
		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

	private:
		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};

	class WaitState : public UIState
	{
	public:
		WaitState()
		{
			OnEnter();
		}
		virtual ~WaitState() override
		{
			OnExit();
		}
		virtual UIState* HandleInput(const std::string& action) override;
		virtual UIState* Update() override;

	private:
		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};
}


