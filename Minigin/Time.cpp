#include "Time.h"

#include <chrono>
#include <SDL_timer.h>

namespace dae
{
	void Time::Init(float frameRateTarget)
	{
		//m_CountsPerSecond = static_cast<float>(SDL_GetPerformanceFrequency());
		m_FrameTimeLimit = frameRateTarget;
		m_PreviousTime = std::chrono::high_resolution_clock::now();
	}

	void Time::Update()
	{

		m_CurrentTime = std::chrono::high_resolution_clock::now();
		m_ElapsedSec = std::chrono::duration<float>(m_CurrentTime - m_PreviousTime).count();

		//m_ElapsedSec = static_cast<float>(currentTime) - m_PreviousTime; // in ms
		m_PreviousTime = m_CurrentTime;

		m_CurrFPS = static_cast<int>(1.f / m_ElapsedSec);

		/*if (m_IsVSyncEnabled && m_ElapsedSec > m_FrameTimeLimit)
		{
			m_ElapsedSec = m_FrameTimeLimit;
		}

		m_FPSTimer += m_ElapsedSec;
		++m_FPSCount;
		if (m_FPSTimer >= MSTOS)
		{
			m_CurrFPS = m_FPSCount;
			m_FPSCount = 0;
			m_FPSTimer -= MSTOS;
		}*/
	}
}
