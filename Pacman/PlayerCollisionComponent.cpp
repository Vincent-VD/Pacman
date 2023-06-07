#include "PlayerCollisionComponent.h"

#include "GameObject.h"
#include "GhostComponent.h"
#include "HeroComponent.h"

pac::PlayerCollisionComponent::PlayerCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect)
	: RectCollisionComponent(pOwner, rect, true)
{
}

void pac::PlayerCollisionComponent::OnCollision(BaseCollisionComponent* other)
{
	if(other->GetOwner()->GetTag() == "pellet")
	{
		GetOwner()->GetComponent<HeroComponent>()->Pickup(PickupType::pellet);
	}
	if (other->GetOwner()->GetTag() == "power pellet")
	{
		const auto& hero{ GetOwner()->GetComponent<HeroComponent>() };
		hero->Pickup(PickupType::powerPellet);
		hero->ActivatePowerMode();
	}
	if (other->GetOwner()->GetTag() == "enemy")
	{
		const auto& hero{ GetOwner()->GetComponent<HeroComponent>() };
		if(!hero->IsPowerModeActive())
		{
			hero->Damage();
		}
		else
		{
			if(other->GetOwner()->GetComponent<GhostComponent>()->IsWeak())
			{
				hero->Pickup(PickupType::ghost);
			}
		}
		
	}
}
