#ifndef FMOD_SOUND_SYSTEM
#define FMOD_SOUND_SYSTEM

#include <mutex>
#include <thread>

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

		virtual void PlayPause(int soundId, bool pause) override;

		virtual void SetVolume(int soundId, float volume) override;

		virtual void Update() override;

	private:
		class AudioThreadFunctor
		{
		public:
			explicit AudioThreadFunctor(FmodSoundSystem* soundSystem) : m_SoundSystem{ soundSystem } {}
			void operator()() { m_SoundSystem->Update(); }

		private:
			FmodSoundSystem* m_SoundSystem;
		};

		bool m_StopThread{ false };
		std::jthread m_AudioThread;
		static std::condition_variable m_ConditionVariable;
		static std::mutex m_Mutex;

		//Condition variable for thread MWAhAHHAHAAHHHAahahAHAHAHHAhahahAAahahHAHAhahaHHAAAAAAAA
		static constexpr int MAX_PENDING{ 16 };
		static int m_Head;
		static int m_Tail;
		static SoundDesc m_PendingSounds[MAX_PENDING];
		static std::vector<std::string> m_SoundPaths;
	};
}

#endif //FMOD_SOUND_SYSTEM