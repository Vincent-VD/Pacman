#include "PlayerCollisionComponent.h"

#include "GameObject.h"
#include "InputComponent.h"

pac::PlayerCollisionComponent::PlayerCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect, bool isDynamic)
	: RectCollisionComponent(pOwner, rect, isDynamic)
{
}

void pac::PlayerCollisionComponent::OnCollision(BaseCollisionComponent* other)
{
	auto thisPlayerID{ GetOwner()->GetComponent<dae::InputComponent>() };
	auto otherPlayerID{ other->GetOwner()->GetComponent<dae::InputComponent>() };

	std::cout << GetOwner()->GetTag() << " " << thisPlayerID << " collided with " << other->GetOwner()->GetTag() << " " << otherPlayerID << std::endl;
}
