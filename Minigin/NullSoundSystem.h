#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		virtual ~NullSoundSystem() override = default;
		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) noexcept = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) noexcept = delete;

		virtual int AddSound(const std::string& /*soundPath*/) override { return -1; }
		virtual void PlaySound(SoundDesc /*soundDesc*/) override {}
		virtual void PauseSound() override {}
		virtual void ResumeSound() override {}
		virtual void Update() override {}
	};
}


