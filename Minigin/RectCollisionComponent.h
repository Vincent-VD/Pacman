#pragma once
#include "BaseCollisionComponent.h"

namespace dae
{
	class RectCollisionComponent : public BaseCollisionComponent
	{
	public:
		RectCollisionComponent(GameObject* pOwner, const Rectf& rect, bool isDynamic);
		virtual ~RectCollisionComponent() override = default;
		RectCollisionComponent(const RectCollisionComponent& other) = delete;
		RectCollisionComponent(RectCollisionComponent&& other) noexcept = delete;
		RectCollisionComponent& operator=(const RectCollisionComponent& other) = delete;
		RectCollisionComponent& operator=(RectCollisionComponent&& other) noexcept = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		virtual void Render() const override;

		virtual bool CheckCollision(const BaseCollisionComponent* other) const override;

	private:
		const Rectf m_CollisionBox;
	};
}


