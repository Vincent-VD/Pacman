#ifndef PELLET_COLLISION_COMPONENT
#define PELLET_COLLISION_COMPONENT

#include "RectCollisionComponent.h"

namespace pac
{
	class PelletCollisionComponent : public dae::RectCollisionComponent
	{
	public:
		PelletCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect);
		virtual ~PelletCollisionComponent() override = default;
		PelletCollisionComponent(const PelletCollisionComponent& other) = delete;
		PelletCollisionComponent(PelletCollisionComponent&& other) noexcept = delete;
		PelletCollisionComponent& operator=(const PelletCollisionComponent& other) = delete;
		PelletCollisionComponent& operator=(PelletCollisionComponent&& other) noexcept = delete;

		virtual void OnCollision(BaseCollisionComponent* other) override;
	};
}

#endif //PELLET_COLLISION_COMPONENT