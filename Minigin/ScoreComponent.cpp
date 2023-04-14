#include "ScoreComponent.h"

#include "GameObject.h"
#include "TextRenderComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner, TextRenderComponent* pTextRenderComponent)
	: RootComponent(pOwner)
	, m_Score(0)
	, m_pTextRenderComponent(pTextRenderComponent)
{
}

void dae::ScoreComponent::IncreaseScore(const std::string& tag)
{
	if(tag == "orb")
	{
		m_Score += 50;
	}
	SetScore();
	GetOwner()->NotifyObservers("score");
}

void dae::ScoreComponent::ResetScore()
{
	m_Score = 0;
	SetScore();
}

void dae::ScoreComponent::SetScore() const
{
	m_pTextRenderComponent->SetText("Score: " + std::to_string(m_Score));
}
