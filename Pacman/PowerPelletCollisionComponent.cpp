#include "PowerPelletCollisionComponent.h"

#include "GameObject.h"
#include "HeroComponent.h"
#include "PacmanGame.h"

pac::PowerPelletCollisionComponent::PowerPelletCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect)
	: RectCollisionComponent(pOwner, rect, false, true)
{
}

void pac::PowerPelletCollisionComponent::OnCollision(dae::BaseCollisionComponent* other)
{
	if (other->GetOwner()->GetTag() == "player")
	{
		GetOwner()->Destroy();
	}
}
