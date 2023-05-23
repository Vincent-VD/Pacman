#include "TileCollisionComponent.h"

#include <iostream>

#include "GameObject.h"

pac::TileCollisionComponent::TileCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect, bool isDynamic)
	: RectCollisionComponent(pOwner, rect, isDynamic)
{
}

void pac::TileCollisionComponent::OnCollision(BaseCollisionComponent* other)
{
	std::cout << "Tile collision with " << other->GetOwner()->GetTag() << std::endl;
}
