#include "PelletCollisionComponent.h"

#include "GameObject.h"
#include "HeroComponent.h"
#include "LevelManager.h"
#include "PacmanGame.h"

pac::PelletCollisionComponent::PelletCollisionComponent(dae::GameObject* pOwner, const dae::Rectf& rect)
	: RectCollisionComponent(pOwner, rect, false, true)
{
}

void pac::PelletCollisionComponent::OnCollision(BaseCollisionComponent* other)
{
	if(other->GetOwner()->GetTag() == "player" && !GetOwner()->IsMarkedForDeletion())
	{
		LevelManager::GetInstance().DestroyPellet();
		GetOwner()->Destroy();
	}
}
