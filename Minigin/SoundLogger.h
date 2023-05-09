#pragma once
#include "SoundSystem.h"

namespace dae
{
	class SoundLogger : public SoundSystem
	{
	public:
		SoundLogger(SoundSystem* pSoundSystem);
		virtual ~SoundLogger() override;
		SoundLogger(const SoundLogger& other) = delete;
		SoundLogger(SoundLogger&& other) noexcept = delete;
		SoundLogger& operator=(const SoundLogger& other) = delete;
		SoundLogger& operator=(SoundLogger&& other) noexcept = delete;

		virtual int AddSound(const std::string& soundPath) override;
		virtual void PlaySound(SoundDesc soundDesc) override;
		virtual void PauseSound() override;
		virtual void ResumeSound() override;
		virtual void Update() override;
	private:
		SoundSystem* m_pSoundSystem;
	};

}

