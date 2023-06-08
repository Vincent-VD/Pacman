#ifndef RECT_COLLISION_COMPONENT
#define RECT_COLLISION_COMPONENT

#include "MiniginPCH.h"
#include "BaseCollisionComponent.h"

namespace dae
{
	class RectCollisionComponent : public BaseCollisionComponent
	{
	public:
		RectCollisionComponent(GameObject* pOwner, const Rectf& rect, bool isDynamic, bool isTrigger = false);
		virtual ~RectCollisionComponent() override = default;
		RectCollisionComponent(const RectCollisionComponent& other) = delete;
		RectCollisionComponent(RectCollisionComponent&& other) noexcept = delete;
		RectCollisionComponent& operator=(const RectCollisionComponent& other) = delete;
		RectCollisionComponent& operator=(RectCollisionComponent&& other) noexcept = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		virtual void Render() const override;

		virtual bool CheckCollision(const BaseCollisionComponent* other) const override;

		bool CheckLayerCollisionAtPosition(const glm::vec3& pos, int layer) const;

	private:
		Rectf m_CollisionBox;

		bool HandleBoxCollision(const Rectf& rect1, const Rectf& rect2) const;
	};
}

#endif //RECT_COLLISION_COMPONENT