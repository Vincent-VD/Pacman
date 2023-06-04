#pragma once
#include "RectCollisionComponent.h"

namespace pac
{
	class PowerPelletCollisionComponent : public dae::RectCollisionComponent
	{
	public:
		PowerPelletCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect);
		virtual ~PowerPelletCollisionComponent() override = default;
		PowerPelletCollisionComponent(const PowerPelletCollisionComponent& other) = delete;
		PowerPelletCollisionComponent(PowerPelletCollisionComponent&& other) noexcept = delete;
		PowerPelletCollisionComponent& operator=(const PowerPelletCollisionComponent& other) = delete;
		PowerPelletCollisionComponent& operator=(PowerPelletCollisionComponent&& other) noexcept = delete;

		virtual void OnCollision(dae::BaseCollisionComponent* other) override;
	};
}
