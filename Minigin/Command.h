#pragma once
#include "MiniginPCH.h"

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
		rightStick = 4
	};

	class Command
	{
	public:
		Command(GameObject* pActor) : m_pActor(pActor) {}
		virtual ~Command() = default;

		const GameObject* GetActor() const { return m_pActor; }

		virtual void Execute(const InputAction& inputAction = InputAction{}) = 0;
	private:
		GameObject* m_pActor;
	};

	class FireCommand : public Command
	{
	public:
		FireCommand(GameObject* pActor) : Command(pActor) {}
		virtual ~FireCommand() override = default;

		virtual void Execute([[maybe_unused]] const InputAction& inputAction = InputAction{}) override { std::cout << "Firing\n"; }
	};

	class MoveCommand : public Command
	{
	public:
		MoveCommand(GameObject* pActor, glm::vec2 direction) : Command(pActor), m_Direction(direction) {}
		virtual ~MoveCommand() override = default;

		virtual void Execute(const InputAction& inputAction) override
		{
			if (glm::length2(inputAction.leftStick) > FLT_EPSILON * FLT_EPSILON)
			{
				std::cout << inputAction.leftStick.x << ", " << inputAction.leftStick.y << std::endl;
			}
			else
			{
				std::cout << m_Direction.x << ", " << m_Direction.y << std::endl;
			}
		};

	private:
		glm::vec2 m_Direction{};
	};
}
