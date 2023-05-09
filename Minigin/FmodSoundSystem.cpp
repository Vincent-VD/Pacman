#include "FmodSoundSystem.h"
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

	void PlayAudio(const std::string filename, const float volume)
	{
		FMOD::Sound* sound{};
		if (m_pFmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, nullptr, &sound) != FMOD_OK)
		{
			std::cout << "FMOD: Failed to create sound\n";
		}

		FMOD::Channel* fmodChannel{};
		fmodChannel->setVolume(volume);
		if (m_pFmodSystem->playSound(sound, nullptr, false, &fmodChannel) != FMOD_OK)
		{
			std::cout << "FMOD: Failed to play sound\n";
		}
    }

	void PauseSound()
	{
		
	}

	void ResumeSound()
	{
		
	}

private:
	FMOD::System* m_pFmodSystem{ nullptr };
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

void FmodSoundSystem::PauseSound()
{
	m_pImpl->PauseSound();
}

void FmodSoundSystem::ResumeSound()
{
	m_pImpl->ResumeSound();
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

		m_pImpl->PlayAudio(path + m_SoundPaths[soundDesc.id], soundDesc.volume);

		m_Head = (m_Head + 1) % MAX_PENDING;
	}
}
