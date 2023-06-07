#include "GhostCollisionComponent.h"

#include "GameObject.h"
#include "GhostComponent.h"
#include "GhostMoveComponent.h"
#include "HeroComponent.h"

pac::GhostCollisionComponent::GhostCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect)
	: RectCollisionComponent(pOwner, rect, true, true)
{
}

void pac::GhostCollisionComponent::OnCollision(BaseCollisionComponent* other)
{
	if(other->GetOwner()->GetTag() == "player")
	{
		GetOwner()->GetComponent<GhostComponent>()->OnCollision();
	}
}