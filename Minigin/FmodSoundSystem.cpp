#include "FmodSoundSystem.h"

#include <unordered_map>

#include "fmod.hpp"
#include "ResourceManager.h"

using namespace dae;


class FmodSoundSystem::SoundImpl
{
public:
	SoundImpl()
	{
		FMOD_RESULT result = FMOD::System_Create(&m_pFmodSystem);
		if (result != FMOD_OK)
		{

			printf("FMOD error! (%d) \n", result);
			//exit(-1);
		}

		result = m_pFmodSystem->init(10, FMOD_INIT_NORMAL, nullptr);	// Initialize FMOD.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) \n", result);
			//exit(-1);
		}
	}

	~SoundImpl()
	{
		m_pFmodSystem->release();
		std::cout << "FMOD released\n";
	}

	SoundImpl(const SoundImpl& other) = delete;
	SoundImpl(SoundImpl&& other) noexcept = delete;
	SoundImpl& operator=(const SoundImpl& other) = delete;
	SoundImpl& operator=(SoundImpl&& other) noexcept = delete;

	void PlayAudio(const std::string& filename, SoundDesc soundDesc, bool loop = false)
	{
		FMOD::Sound* sound{};
		FMOD_MODE mode{ static_cast<FMOD_MODE>(loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT) };
		if (m_pFmodSystem->createSound(filename.c_str(), mode, nullptr, &sound) != FMOD_OK)
		{
			std::cout << "FMOD: Failed to create sound\n";
		}

		FMOD::Channel* fmodChannel{};
		if (m_pFmodSystem->playSound(sound, nullptr, false, &fmodChannel) != FMOD_OK)
		{
			std::cout << "FMOD: Failed to play sound\n";
		}

		fmodChannel->setVolume(soundDesc.volume);

		m_SoundMap.insert(std::pair{soundDesc.id, fmodChannel });
    }

	void PlayPauseSound(int soundId, bool playPause)
	{
		if (m_SoundMap.find(soundId) != m_SoundMap.end())
		{
			const auto pChannel{ m_SoundMap.at(soundId) };
			pChannel->setPaused(playPause);
		}
	}

private:
	FMOD::System* m_pFmodSystem{ nullptr };
	std::unordered_map<int, FMOD::Channel*> m_SoundMap{};
};

std::mutex FmodSoundSystem::m_Mutex;
std::condition_variable FmodSoundSystem::m_ConditionVariable;

int FmodSoundSystem::m_Head = 0;
int FmodSoundSystem::m_Tail = 0;
std::vector<std::string> FmodSoundSystem::m_SoundPaths{};
SoundDesc FmodSoundSystem::m_PendingSounds[FmodSoundSystem::MAX_PENDING] = {};


FmodSoundSystem::FmodSoundSystem()
	: m_pImpl(new SoundImpl{})
	, m_AudioThread(AudioThreadFunctor{ this })
{
}

FmodSoundSystem::~FmodSoundSystem()
{
	delete m_pImpl;
	m_StopThread = true;
	m_ConditionVariable.notify_one();
	m_AudioThread.join();

}

int FmodSoundSystem::AddSound(const std::string& soundPath)
{
	m_SoundPaths.emplace_back(soundPath);

	return static_cast<int>(m_SoundPaths.size()) - 1;
}

void FmodSoundSystem::PlaySound(SoundDesc soundDesc)
{
	std::unique_lock<std::mutex> lock{ m_Mutex };

	for (int iter = m_Head; iter != m_Tail; iter = (iter + 1) % MAX_PENDING)
	{
		SoundDesc curr{ m_PendingSounds[iter] };
		if (curr.id == soundDesc.id)
		{
			curr.volume = std::max(curr.volume, soundDesc.volume);
			return;
		}
	}

	m_PendingSounds[m_Tail] = soundDesc;
	m_Tail = (m_Tail + 1) % MAX_PENDING;

	m_ConditionVariable.notify_one();
}

void FmodSoundSystem::PlayPause(int soundId, bool pause)
{
	m_pImpl->PlayPauseSound(soundId, pause);
}

void FmodSoundSystem::Update()
{
	while(true)
	{
		std::unique_lock<std::mutex> lock{ m_Mutex };

		m_ConditionVariable.wait(lock, [this] { return m_StopThread || m_Head != m_Tail; });

		if (m_StopThread) {
			break;
		}

		const std::string path{ ResourceManager::GetInstance().GetDataPath() };

		const SoundDesc soundDesc{ m_PendingSounds[m_Head] };

		m_pImpl->PlayAudio(path + m_SoundPaths[soundDesc.id], soundDesc);

		m_Head = (m_Head + 1) % MAX_PENDING;
	}
}