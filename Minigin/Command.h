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

		virtual void Execute() = 0;
		virtual void Execute(const InputAction& inputAction) = 0;
	};

	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* pActor) : Command{}, m_pActor(pActor) {}
		virtual ~GameObjectCommand() override = default;

		const GameObject* GetActor() const { return m_pActor; }

		virtual void Execute() override = 0;
		virtual void Execute(const InputAction& inputAction) override = 0;
	private:
		GameObject* m_pActor;
	};

	class FireCommand : public GameObjectCommand
	{
	public:
		FireCommand(GameObject* pActor) : GameObjectCommand(pActor) {}
		virtual ~FireCommand() override = default;

		virtual void Execute() override {}
		virtual void Execute([[maybe_unused]] const InputAction& inputAction) override { std::cout << "Firing\n"; }
	};

	

}
