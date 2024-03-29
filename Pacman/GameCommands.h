#ifndef GAME_COMMAND
#define GAME_COMMAND

#include "Command.h"
#include "PacmanGame.h"

namespace pac
{
	class MoveCommand : public dae::GameObjectCommand
	{
	public:
		MoveCommand(dae::GameObject* pActor, const float speed) : GameObjectCommand(pActor), m_Speed(speed), m_GameField(PacmanGame::GetGameField()) {}
		virtual ~MoveCommand() override = default;

		virtual void Execute() override {}
		virtual void Execute(const dae::InputAction& inputAction) override;

	private:
		const float m_Speed{};
		const GameField m_GameField{};
	};

	class HitCommand : public dae::GameObjectCommand
	{
	public:
		HitCommand(dae::GameObject* pActor) : GameObjectCommand(pActor) {}
		virtual ~HitCommand() override = default;

		virtual void Execute() override;
		virtual void Execute([[maybe_unused]] const dae::InputAction& inputAction) override {}
	};

	class ScoreCommand : public dae::GameObjectCommand
	{
	public:
		ScoreCommand(dae::GameObject* pActor) : GameObjectCommand(pActor) {}
		virtual ~ScoreCommand() override = default;

		virtual void Execute() override;
		virtual void Execute([[maybe_unused]] const dae::InputAction& inputAction) override {}
	};

	class MusicPauseCommand : public dae::Command
	{
	public:
		MusicPauseCommand() : Command() {}
		virtual ~MusicPauseCommand() override = default;

		virtual void Execute() override;
		virtual void Execute([[maybe_unused]] const dae::InputAction& inputAction) override {}

	private:
		bool m_IsPaused{ false };
	};

	class SoundCommand : public dae::Command
	{
	public:
		SoundCommand() : Command() {}
		virtual ~SoundCommand() override = default;

		virtual void Execute() override;
		virtual void Execute([[maybe_unused]] const dae::InputAction& inputAction) override {}

	private:
		bool m_IsPaused{ false };
	};

	class MuteCommand : public dae::Command
	{
	public:
		MuteCommand() : Command() {}
		virtual ~MuteCommand() override = default;

		virtual void Execute() override;
		virtual void Execute([[maybe_unused]] const dae::InputAction& inputAction) override {}

	private:
		bool m_IsMuted{false};
	};

	class GamePauseCommand : public dae::GameObjectCommand
	{
	public:
		GamePauseCommand(dae::GameObject* pActor) : GameObjectCommand(pActor) {}
		virtual ~GamePauseCommand() override = default;

		virtual void Execute() override;
		virtual void Execute([[maybe_unused]] const dae::InputAction& inputAction) override {}
	};

	class Next : public dae::Command
	{
	public:
		Next() : Command() {}
		virtual ~Next() override = default;

		virtual void Execute() override;
		virtual void Execute([[maybe_unused]] const dae::InputAction& inputAction) override {}
	};
}

#endif //GAME_COMMAND