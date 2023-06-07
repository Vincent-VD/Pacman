#ifndef GHOSTSTATE
#define GHOSTSTATE

#include <string>
#include <glm/vec2.hpp>

#include "Structs.h"

namespace dae
{
	class TextureComponent2D;
	class GameObject;
}

namespace pac
{
	class GhostState
	{
	public:
		GhostState(dae::GameObject* pActor);
		virtual ~GhostState() = default;

		virtual GhostState* HandleInput(const std::string& /*action*/) { return nullptr; }
		virtual GhostState* Update() { return nullptr; }

		virtual void OnEnter() {}
		virtual void OnExit() {}

	protected:
		dae::GameObject* GetActor() const { return m_pOwner; }

	private:
		dae::GameObject* m_pOwner;
	};

	class NormalState : public GhostState
	{
	public:
		NormalState(dae::GameObject* pActor, const glm::vec2& moveDirection);
		virtual ~NormalState() override = default;

		virtual GhostState* HandleInput(const std::string& action) override;
		virtual GhostState* Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override {}

	private:
		const float m_Speed{30.f};
		glm::vec2 m_MoveDirection{};
		dae::TextureComponent2D* m_pTextureComp{nullptr};

		void SetRandomDirection();
	};

	class BlueState : public GhostState
	{
	public:
		explicit BlueState(dae::GameObject* pActor, const glm::vec2& moveDirection);
		virtual ~BlueState() override = default;

		virtual GhostState* HandleInput(const std::string& /*action*/) override;
		virtual GhostState* Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		dae::Rectf m_PrevRect{};
		const float m_Speed{ 40.f };
		glm::vec2 m_MoveDirection{};
		dae::TextureComponent2D* m_pTextureComp{nullptr};


		void SetRandomDirection();
	};

	class WeakState : public GhostState
	{
	public:
		explicit WeakState(dae::GameObject* pActor, const glm::vec2& moveDirection);
		virtual ~WeakState() override = default;

		virtual GhostState* HandleInput(const std::string& /*action*/) override;
		virtual GhostState* Update() override;

		virtual void OnEnter() override {}
		virtual void OnExit() override {}

	private:
		float m_CurrTime{};
		const float m_MaxTime{ 15.f };
		glm::vec2 m_MoveDirection{};
	};

}

#endif //GHOSTSTATE