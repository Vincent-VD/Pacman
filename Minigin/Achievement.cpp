#include "Achievement.h"

dae::Achievement::Achievement()
	: Observer()
	, m_pSteamAchievements(std::make_unique<CSteamAchievements>(m_Achievements, 4))
{
}

void dae::Achievement::OnNotify(const std::string& msg, const GameObject* /*gameObject*/)
{
	if (msg == "player died")
	{
		std::cout << "Player died\n";
		m_pSteamAchievements->SetAchievement("ACH_WIN_100_GAMES");
	}
}
