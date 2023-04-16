#include "ScoreComponent.h"

#include "GameObject.h"
#include "TextRenderComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner)
	: RootComponent(pOwner)
	, m_Score(0)
{
}

void dae::ScoreComponent::IncreaseScore(const std::string& tag)
{
	if(tag == "orb")
	{
		m_Score += 50;
	}
	GetOwner()->NotifyObservers("score");
}

void dae::ScoreComponent::ResetScore()
{
	m_Score = 0;
	GetOwner()->NotifyObservers("score");
}