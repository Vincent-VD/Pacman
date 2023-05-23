#include "BaseCollisionComponent.h"

void dae::CollisionManager::Init()
{
	m_pCollisionComponents = std::vector<BaseCollisionComponent*>{};
	m_Layers = std::vector<std::bitset<8>>{};
}

void dae::CollisionManager::AddCollision(BaseCollisionComponent* collision)
{
	m_pCollisionComponents.emplace_back(collision);
}

void dae::CollisionManager::AddLayer()
{
	m_Layers.emplace_back(std::bitset<8>{});
}

void dae::CollisionManager::RemoveLayer(int layer)
{
	const auto layerToRemove{ m_Layers[layer] };
	m_Layers.erase(std::remove(m_Layers.begin(), m_Layers.end(), layerToRemove));
}

void dae::CollisionManager::SetLayerCollision(int layer1, int layer2)
{
	m_Layers[layer1].set(layer2);
}

bool dae::CollisionManager::CheckForCollision(int layer1, int layer2) const
{
	return m_Layers[layer1][layer2];
}

dae::BaseCollisionComponent::BaseCollisionComponent(GameObject* pOwner, bool isDynamic)
	: RootComponent(pOwner)
	, m_IsDynamic(isDynamic)
{
	CollisionManager::GetInstance().AddCollision(this);
}
