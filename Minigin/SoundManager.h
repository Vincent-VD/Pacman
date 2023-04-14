#pragma once
#include "MiniginPCH.h"
#include "Singleton.h"

namespace dae
{
	class SoundManager
	{
		class SoundImpl;
		std::unique_ptr<SoundImpl> m_pImpl;

	public:
		void Init();
		void ProcessAudio();

		SoundManager();
		~SoundManager();
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) noexcept = delete;
		SoundManager& operator=(const SoundManager& other) = delete;
		SoundManager& operator=(SoundManager&& other) noexcept = delete;
	};
}


