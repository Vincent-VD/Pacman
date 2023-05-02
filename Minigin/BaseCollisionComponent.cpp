#include "BaseCollisionComponent.h"

void dae::CollisionManager::Init()
{
	m_pCollisionComponents = std::vector<BaseCollisionComponent*>{};
}

void dae::CollisionManager::AddCollision(BaseCollisionComponent* collision)
{
	m_pCollisionComponents.push_back(collision);
}

void dae::CollisionManager::SetLayerCollision(int layer1, int layer2)
{
	m_Layers[layer1].set(layer2);
}

bool dae::CollisionManager::CheckForCollision(int layer1, int layer2) const
{
	return (m_Layers[layer1] & m_Layers[layer2]).any();
}

//std::vector<dae::BaseCollisionComponent*> dae::CollisionManager::GetCollisions()
//{
//}

dae::BaseCollisionComponent::BaseCollisionComponent(GameObject* pOwner, bool isDynamic)
	: RootComponent(pOwner)
	, m_IsDynamic(isDynamic)
{
	CollisionManager::GetInstance().AddCollision(this);
}
