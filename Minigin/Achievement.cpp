#include "Achievement.h"

#include "CSteamAchievements.h"
#include "GameObject.h"
#include "ScoreComponent.h"

dae::Achievement::Achievement(GameObject* pOwner)
	: RootComponent(pOwner)
	, Observer()
{
}

void dae::Achievement::OnNotify(const std::string& msg, const GameObject* gameObject)
{
	if(msg == "player died")
	{
		std::cout << "Player died\n";
		CSteamAchievements::GetInstance()->SetAchievement("ACH_WIN_100_GAMES");
	}
	if(msg == "score")
	{
		const int score{ gameObject->GetComponent<ScoreComponent>()->GetScore() };
		if(score > 500)
		{
			CSteamAchievements::GetInstance()->SetAchievement("ACH_TRAVEL_FAR_SINGLE");
		}
	}
}
