#include "LifeComponent.h"

#include "GameObject.h"
#include "TextRenderComponent.h"

dae::LifeComponent::LifeComponent(GameObject* pOwner, /*TextRenderComponent* pTextRenderComponent, */const int nrOfLives)
	: RootComponent(pOwner)
	, m_CurrLives(nrOfLives)
	, m_MaxLives(nrOfLives)
	//, m_pTextRenderComponent(pTextRenderComponent)
{
}

void dae::LifeComponent::Hit()
{
	--m_CurrLives;
	//m_pTextRenderComponent->SetText("Lives: " + std::to_string(m_CurrLives));
	GetOwner()->NotifyObservers("player hit");
	if(m_CurrLives == 0)
	{
		GetOwner()->NotifyObservers("player died");
		//player dies
	}
}