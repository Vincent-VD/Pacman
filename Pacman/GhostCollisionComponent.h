#ifndef GHOSTCOLLISIONCOMPONENT
#define GHOSTCOLLISIONCOMPONENT

#include <RectCollisionComponent.h>

namespace pac
{
	class GhostCollisionComponent : public dae::RectCollisionComponent
	{
	public:
		GhostCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect);
		virtual ~GhostCollisionComponent() override = default;
		GhostCollisionComponent(const GhostCollisionComponent& other) = delete;
		GhostCollisionComponent(GhostCollisionComponent&& other) noexcept = delete;
		GhostCollisionComponent& operator=(const GhostCollisionComponent& other) = delete;
		GhostCollisionComponent& operator=(GhostCollisionComponent&& other) noexcept = delete;

		virtual void OnCollision(BaseCollisionComponent* other) override;
	};

}

#endif //GHOSTCOLLISIONCOMPONENT