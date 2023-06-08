#ifndef GHOSTCOMPONENT
#define GHOSTCOMPONENT

#include <string>

#include "RootComponent.h"

namespace pac
{
	class GhostState;

	enum class GhostTypes
	{
		Blinky = 1,
		Inky = 2,
		Clyde = 3,
		Pinky = 4
	};

	class GhostComponent : public dae::RootComponent
	{
	public:
		GhostComponent(dae::GameObject* pOwner, GhostTypes type, bool acceptInput);
		virtual ~GhostComponent() override;
		GhostComponent(const GhostComponent& other) = delete;
		GhostComponent(GhostComponent&& other) noexcept = delete;
		GhostComponent& operator=(const GhostComponent& other) = delete;
		GhostComponent& operator=(GhostComponent&& other) noexcept = delete;

		GhostTypes GetType() const { return m_Type; }

		void Weaken();
		void Recover();
		void OnCollision();

		bool IsWeak() const;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		bool m_IsHit{false};
		const bool m_IsPlayerControlled;
		float m_CurrCooldown{};
		const float m_MaxCooldown{ 5.f };

		const GhostTypes m_Type;
		GhostState* m_pState;

		void StateInput(const std::string& msg);
	};
}

#endif //GHOSTCOMPONENT
