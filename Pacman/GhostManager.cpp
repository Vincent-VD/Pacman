#include "GhostManager.h"

#include "GameObject.h"
#include "GhostComponent.h"

void pac::GhostManager::RegisterGhost(dae::GameObject* pGhost)
{
	m_pGhosts.emplace_back(pGhost);
}

void pac::GhostManager::OnNotify(PickupType pickup)
{
	if(pickup == PickupType::powerPellet)
	{
		for (const auto& ghost : m_pGhosts)
		{
			ghost->GetComponent<GhostComponent>()->Weaken();
		}
		return;
	}
	if(pickup == PickupType::reset)
	{
		for (const auto& ghost : m_pGhosts)
		{
			ghost->GetComponent<GhostComponent>()->Recover();
		}
		return;
	}
}
