#pragma once
#include "Command.h"

namespace pac
{
	class MoveCommand : public dae::GameObjectCommand
	{
	public:
		MoveCommand(dae::GameObject* pActor, const float speed, const glm::vec2& direction = glm::vec2{}) : GameObjectCommand(pActor), m_Speed(speed), m_Direction(direction) {}
		virtual ~MoveCommand() override = default;

		virtual void Execute() override {}
		virtual void Execute(const dae::InputAction& inputAction) override;

	private:
		const float m_Speed{};
		const glm::vec2 m_Direction{};
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

	class GamePauseCommand : public dae::GameObjectCommand
	{
	public:
		GamePauseCommand(dae::GameObject* pActor) : GameObjectCommand(pActor) {}
		virtual ~GamePauseCommand() override = default;

		virtual void Execute() override;
		virtual void Execute([[maybe_unused]] const dae::InputAction& inputAction) override {}
	};
}
