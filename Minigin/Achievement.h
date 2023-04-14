#pragma once
#include "CSteamAchievements.h"
#include "Observer.h"

namespace dae
{
	class CSteamAchievements;

	class Achievement : public Observer
	{
	public:
		Achievement();
		virtual ~Achievement() override = default;
		Achievement(const Achievement& other) = delete;
		Achievement(Achievement&& other) noexcept = delete;
		Achievement& operator=(const Achievement& other) = delete;
		Achievement& operator=(Achievement&& other) noexcept = delete;

		virtual void OnNotify(const std::string& msg, const GameObject* gameObject) override;

	private:
		// Defining our achievements
		enum EAchievements
		{
			ACH_WIN_ONE_GAME = 0,
			ACH_WIN_100_GAMES = 1,
			ACH_TRAVEL_FAR_ACCUM = 2,
			ACH_TRAVEL_FAR_SINGLE = 3,
		};

		// Achievement array which will hold data about the achievements and their state
		Achievement_t m_Achievements[4] =
		{
			ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
			ACH_ID(ACH_WIN_100_GAMES, "Champion"),
			ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
			ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
		};

		std::unique_ptr<CSteamAchievements> m_pSteamAchievements;
	};


}
