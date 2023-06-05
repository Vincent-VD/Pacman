#ifndef GHOSTSTATE
#define GHOSTSTATE

#include <string>

namespace dae
{
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
		virtual void OnCollision() {}
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
		NormalState(dae::GameObject* pActor);
		virtual ~NormalState() override = default;

		virtual GhostState* HandleInput(const std::string& action) override;
		virtual void OnCollision() override;
		virtual GhostState* Update() override;

		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};

	class BlueState : public GhostState
	{
	public:
		explicit BlueState(dae::GameObject* pActor);
		virtual ~BlueState() override = default;

		virtual GhostState* HandleInput(const std::string& /*action*/) override;
		virtual void OnCollision() override;
		virtual GhostState* Update() override;

		virtual void OnEnter() override {}
		virtual void OnExit() override {}

	private:
		float m_CurrTime{};
		const float m_MaxTime{ 15.f };
	};

	class WeakState : public GhostState
	{
	public:
		explicit WeakState(dae::GameObject* pActor);
		virtual ~WeakState() override = default;

		virtual GhostState* HandleInput(const std::string& /*action*/) override;
		virtual void OnCollision() override;
		virtual GhostState* Update() override;

		virtual void OnEnter() override {}
		virtual void OnExit() override {}
	};

}

#endif //GHOSTSTATE