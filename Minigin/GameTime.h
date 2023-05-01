#pragma once

#include <chrono>
#include <glm/fwd.hpp>

#include "Singleton.h"

namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		void Init(float frameRateTarget = 60.f);

		void Update();

		float GetDeltaTime() const { return m_ElapsedSec; }

		std::chrono::duration<long long, std::nano> GetSleepTime() const;

		glm::uint32_t GetFPS() const { return m_CurrFPS; }
		//float GetElapsedSec() const { return m_ElapsedSec * STOMS; }; //clamp value? 0.016667 or 0.016
		float GetTotal() const { return m_TotalTime; }

	private:
		/*friend class Singleton<Time>;
		Time() = default;*/
		//runtime counters
		std::chrono::time_point<std::chrono::steady_clock> m_PreviousTime;
		std::chrono::time_point<std::chrono::steady_clock> m_CurrentTime;

		//user values
		glm::uint32_t m_CurrFPS{};
		float m_TotalTime{};
		float m_FrameTimeLimit{};
		float m_ElapsedSec{};
	};

}
