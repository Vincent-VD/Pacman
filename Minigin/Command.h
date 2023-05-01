#pragma once
#include "GameObject.h"
#include "MiniginPCH.h"
#include "GameTime.h"

namespace dae
{
	class GameObject;

	struct InputAction
	{
		float leftTrigger{};
		float rightTrigger{};
		glm::vec2 leftStick{};
		glm::vec2 rightStick{};
	};

	enum class InputType
	{
		pressed = 0,
		held = 1,
		released = 2,
		leftStick = 3,
		rightStick = 4,
		dpadAxis = 5
	};

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		virtual void Execute(const InputAction& inputAction = InputAction{}) = 0;
	};

	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* pActor) : Command{}, m_pActor(pActor) {}
		virtual ~GameObjectCommand() = default;

		const GameObject* GetActor() const { return m_pActor; }

		virtual void Execute(const InputAction& inputAction = InputAction{}) = 0;
	private:
		GameObject* m_pActor;
	};

	class FireCommand : public GameObjectCommand
	{
	public:
		FireCommand(GameObject* pActor) : GameObjectCommand(pActor) {}
		virtual ~FireCommand() override = default;

		virtual void Execute([[maybe_unused]] const InputAction& inputAction = InputAction{}) override { std::cout << "Firing\n"; }
	};

	class MoveCommand : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* pActor, const float speed, const glm::vec2& direction = glm::vec2{}) : GameObjectCommand(pActor), m_Speed(speed), m_Direction(direction) {}
		virtual ~MoveCommand() override = default;

		virtual void Execute(const InputAction& inputAction) override;

	private:
		const float m_Speed{};
		const glm::vec2 m_Direction{};
	};

	class HitCommand : public GameObjectCommand
	{
	public:
		HitCommand(GameObject* pActor) : GameObjectCommand(pActor) {}
		virtual ~HitCommand() override = default;

		virtual void Execute([[maybe_unused]] const InputAction& inputAction) override;
	};

	class ScoreCommand : public GameObjectCommand
	{
	public:
		ScoreCommand(GameObject* pActor) : GameObjectCommand(pActor) {}
		virtual ~ScoreCommand() override = default;

		virtual void Execute([[maybe_unused]] const InputAction& inputAction) override;
	};

}
