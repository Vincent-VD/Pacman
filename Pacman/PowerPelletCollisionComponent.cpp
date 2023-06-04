#include "PowerPelletCollisionComponent.h"

#include "GameObject.h"
#include "HeroComponent.h"
#include "InputComponent.h"

pac::PowerPelletCollisionComponent::PowerPelletCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect)
	: RectCollisionComponent(pOwner, rect, false, true)
{
}

void pac::PowerPelletCollisionComponent::OnCollision(dae::BaseCollisionComponent* other)
{
	if (const auto& player{ other->GetOwner()->GetComponent<dae::InputComponent>() })
	{
		const auto& hero{ other->GetOwner()->GetComponent<HeroComponent>() };
		hero->Pickup(PickupType::powerPellet);
		hero->ActivatePowerMode();
		GetOwner()->Destroy();
	}
}
