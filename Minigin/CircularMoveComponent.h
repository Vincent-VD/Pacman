#ifndef CIRCULAR_MOVE_COMPONENT
#define CIRCULAR_MOVE_COMPONENT

#include "MiniginPCH.h"
#include "RootComponent.h"

namespace dae
{
	class CircularMoveComponent : public RootComponent
	{
	public:
		CircularMoveComponent(GameObject* pOwner, float radius, float moveSpeed);
		virtual ~CircularMoveComponent() override = default;
		CircularMoveComponent(const CircularMoveComponent& other) = delete;
		CircularMoveComponent(CircularMoveComponent&& other) noexcept = delete;
		CircularMoveComponent& operator=(const CircularMoveComponent& other) = delete;
		CircularMoveComponent& operator=(CircularMoveComponent&& other) noexcept = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		float m_Radius;
		float m_MoveSpeed;
		float m_CurrAngle{};
		glm::vec3 m_Center;
	};

}

#endif //CIRCULAR_MOVE_COMPONENT