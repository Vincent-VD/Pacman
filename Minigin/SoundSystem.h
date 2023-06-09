#ifndef SOUND_SYSTEM
#define SOUND_SYSTEM

#include "MiniginPCH.h"

namespace dae
{

	struct SoundDesc
	{
		int id;
		float volume;
		bool loop;
	};


	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;
		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) noexcept = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) noexcept = delete;

		//Add sound path and return its position (sound id)
		virtual int AddSound(const std::string& soundPath) = 0;
		virtual void PlaySound(SoundDesc soundDesc) = 0;

		virtual void PlayPause(int soundId, bool pause) = 0;

		virtual void Update() = 0;
	};
}

#endif //SOUND_SYSTEM