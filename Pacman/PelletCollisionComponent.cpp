#include "PelletCollisionComponent.h"

#include "GameObject.h"
#include "HeroComponent.h"
#include "InputComponent.h"

pac::PelletCollisionComponent::PelletCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect)
	: RectCollisionComponent(pOwner, rect, false, true)
{
}

void pac::PelletCollisionComponent::OnCollision(BaseCollisionComponent* other)
{
	if(const auto player{other->GetOwner()->GetComponent<dae::InputComponent>()})
	{
		other->GetOwner()->GetComponent<HeroComponent>()->Pickup(PickupType::pellet);
		GetOwner()->Destroy();
	}
}
