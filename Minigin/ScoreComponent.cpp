#include "ScoreComponent.h"

#include "Achievement.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "TextRenderObserver.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner, TextRenderComponent* textRenderComponent)
	: RootComponent(pOwner)
	, m_Score(0)
	, m_AchievementSubject(Subject<std::string>{})
	, m_HUDSubject(Subject<int>{})
{
	auto observer{ new Achievement{} };
	m_AchievementSubject.AddObserver(observer);
	auto HUDObserver{ new TextRenderObserver(textRenderComponent) };
	m_HUDSubject.AddObserver(HUDObserver);
}

void dae::ScoreComponent::IncreaseScore(const std::string& tag)
{
	if(tag == "orb")
	{
		m_Score += 50;
	}
	m_AchievementSubject.Notify("");
	m_HUDSubject.Notify(m_Score);
}

void dae::ScoreComponent::ResetScore()
{
	m_Score = 0;
	m_AchievementSubject.Notify("");
	m_HUDSubject.Notify(m_Score);
}