#pragma once

#include "MiniginPCH.h"
#include "SoundSystem.h"

namespace dae
{

	class FmodSoundSystem final : public SoundSystem
	{
		class SoundImpl;
		SoundImpl* m_pImpl;

	public:
		FmodSoundSystem();
		virtual ~FmodSoundSystem() override;
		FmodSoundSystem(const FmodSoundSystem& other) = delete;
		FmodSoundSystem(FmodSoundSystem&& other) noexcept = delete;
		FmodSoundSystem& operator=(const FmodSoundSystem& other) = delete;
		FmodSoundSystem& operator=(FmodSoundSystem&& other) noexcept = delete;

		virtual int AddSound(const std::string& soundPath) override;

		virtual void PlaySound(SoundDesc soundDesc) override;

		virtual void PauseSound() override;

		virtual void ResumeSound() override;

		virtual void Update() override;

	private:
		//Condition variable for thread MWAhAHHAHAAHHHAahahAHAHAHHAhahahAAahahHAHAhahaHHAAAAAAAA
		static const int MAX_PENDING{ 16 };
		int m_Head{};
		int m_Tail{};
		std::vector<SoundDesc> m_PendingSounds;
		std::vector<std::string> m_SoundPaths;
	};
}


