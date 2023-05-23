#include "PlayerCollisionComponent.h"

#include "GameObject.h"
#include "InputComponent.h"

pac::PlayerCollisionComponent::PlayerCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect)
	: RectCollisionComponent(pOwner, rect, true)
{
}

void pac::PlayerCollisionComponent::OnCollision(BaseCollisionComponent* /*other*/)
{
	/*auto thisPlayerID{ GetOwner()->GetComponent<dae::InputComponent>()->GetPlayerID() };
	auto otherPlayerID{ -1 };


	std::cout << GetOwner()->GetTag() << " " << thisPlayerID << " collided with " << other->GetOwner()->GetTag() << " " << otherPlayerID << std::endl;*/
}
