#pragma once

#define MSTOS 1000.f //milliseconds to seconds
#define STOMS 0.001f //seconds to milliseconds
#include <chrono>
#include <glm/fwd.hpp>

#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void Init(float frameRateTarget = 60.f);

		void Update();

		float GetDeltaTime() const { return m_ElapsedSec; }

		auto GetSleepTime() const
		{
			return m_CurrentTime + std::chrono::milliseconds(static_cast<int>(m_FrameTimeLimit)) - std::chrono::high_resolution_clock::now();
		}

		glm::uint32_t GetFPS() const { return m_CurrFPS; }
		//float GetElapsedSec() const { return m_ElapsedSec * STOMS; }; //clamp value? 0.016667 or 0.016
		float GetTotal() const { return m_TotalTime; }

	private:
		//runtime counters
		std::chrono::time_point<std::chrono::steady_clock> m_PreviousTime;
		std::chrono::time_point<std::chrono::steady_clock> m_CurrentTime;

		//user values
		glm::uint32_t m_CurrFPS{};
		glm::uint32_t m_FPSCount{};
		float m_TotalTime{};
		float m_FrameTimeLimit{};
		float m_ElapsedSec{};
		float m_FPSTimer{};
		bool m_IsVSyncEnabled{ true };
	};

}
