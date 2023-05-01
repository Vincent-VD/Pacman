#include "GameTime.h"

namespace dae
{
	void GameTime::Init(float frameRateTarget)
	{
		//m_CountsPerSecond = static_cast<float>(SDL_GetPerformanceFrequency());
		m_FrameTimeLimit = frameRateTarget;
		m_PreviousTime = std::chrono::high_resolution_clock::now();
	}

	void GameTime::Update()
	{
		m_CurrentTime = std::chrono::high_resolution_clock::now();
		m_ElapsedSec = std::chrono::duration<float>(m_CurrentTime - m_PreviousTime).count();

		m_PreviousTime = m_CurrentTime;

		m_CurrFPS = static_cast<int>(1.f / m_ElapsedSec);
	}

	std::chrono::duration<long long, std::nano> GameTime::GetSleepTime() const
	{
		return m_CurrentTime + std::chrono::milliseconds(static_cast<int>(m_FrameTimeLimit)) - std::chrono::high_resolution_clock::now();
	}
}
