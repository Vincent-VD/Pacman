#ifndef GHOSTMOVECOMPONENT
#define GHOSTMOVECOMPONENT

#include <glm/vec2.hpp>

#include "RootComponent.h"

namespace dae
{
	class TextureComponent2D;
}

namespace pac
{
	class GhostMoveComponent : public dae::RootComponent
	{
	public:
		GhostMoveComponent(dae::GameObject* pOwner);
		virtual ~GhostMoveComponent() override = default;
		GhostMoveComponent(const GhostMoveComponent& other) = delete;
		GhostMoveComponent(GhostMoveComponent&& other) noexcept = delete;
		GhostMoveComponent& operator=(const GhostMoveComponent& other) = delete;
		GhostMoveComponent& operator=(GhostMoveComponent&& other) noexcept = delete;

		void InvertDirection();
		void SetRandomDirection();

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		glm::vec2 m_MoveDirection;
		float m_Speed;
		dae::TextureComponent2D* m_pTextureComp{nullptr};

	};
}


#endif //GHOSTMOVECOMPONENT