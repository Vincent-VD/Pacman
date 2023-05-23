#pragma once
#include "RectCollisionComponent.h"

namespace pac
{
	class PlayerCollisionComponent : public dae::RectCollisionComponent
	{
	public:
		PlayerCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect);
		virtual ~PlayerCollisionComponent() override = default;
		PlayerCollisionComponent(const PlayerCollisionComponent& other) = delete;
		PlayerCollisionComponent(PlayerCollisionComponent&& other) noexcept = delete;
		PlayerCollisionComponent& operator=(const PlayerCollisionComponent& other) = delete;
		PlayerCollisionComponent& operator=(PlayerCollisionComponent&& other) noexcept = delete;

		virtual void OnCollision(BaseCollisionComponent* other) override;

	};


}
