#pragma once
#include <RectCollisionComponent.h>

namespace pac
{
	class TileCollisionComponent : public dae::RectCollisionComponent
	{
	public:
		TileCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect);
		virtual ~TileCollisionComponent() override = default;
		TileCollisionComponent(const TileCollisionComponent& other) = delete;
		TileCollisionComponent(TileCollisionComponent&& other) noexcept = delete;
		TileCollisionComponent& operator=(const TileCollisionComponent& other) = delete;
		TileCollisionComponent& operator=(TileCollisionComponent&& other) noexcept = delete;

		virtual void OnCollision(BaseCollisionComponent* other) override;
	};
}


