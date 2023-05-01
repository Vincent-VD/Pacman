#include "Achievement.h"

dae::Achievement::Achievement()
	: Observer<std::string>()
{
}


void dae::Achievement::OnNotify(std::string args)
{
	if (args == "player died")
	{
		if (CSteamAchievements::GetInstance())
		{
			CSteamAchievements::GetInstance()->SetAchievement("ACH_WIN_100_GAMES");

		}
	}
}

void dae::Achievement::OnSubjectDestroyed()
{
}