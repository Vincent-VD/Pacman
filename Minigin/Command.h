#pragma once
#include "GameObject.h"
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
		MoveCommand(GameObject* pActor, const float speed, const glm::vec2& direction = glm::vec2{}) : Command(pActor), m_Speed(speed), m_Direction(direction) {}
		virtual ~MoveCommand() override = default;

		virtual void Execute(const InputAction& inputAction) override
		{
			auto currentPos{ GetActor()->GetTransform()->GetWorldPosition() };
			if (glm::length2(inputAction.leftStick) > FLT_EPSILON * FLT_EPSILON)
			{
				GetActor()->GetTransform()->SetPosition(currentPos + m_Speed * glm::vec3(inputAction.leftStick.x, -inputAction.leftStick.y, 0.f));
			}
			else
			{
				GetActor()->GetTransform()->SetPosition(currentPos + m_Speed * glm::vec3(m_Direction.x, m_Direction.y, 0.f));
			}
		}

	private:
		const float m_Speed{};
		const glm::vec2 m_Direction{};
	};
}
