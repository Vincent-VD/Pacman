#include "SoundManager.h"
using namespace dae;


class SoundManager::SoundImpl
{
public:
	SoundImpl()
	{
        
	}

    ~SoundImpl()
	{

	}

	SoundImpl(const SoundImpl& other) = delete;
	SoundImpl(SoundImpl&& other) noexcept = delete;
	SoundImpl& operator=(const SoundImpl& other) = delete;
	SoundImpl& operator=(SoundImpl&& other) noexcept = delete;

    bool Init()
	{
        return false;
	}

    void ProcessAudio()
    {
    }
};

void SoundManager::Init()
{
    m_pImpl->Init();
}

void SoundManager::ProcessAudio()
{
    m_pImpl->ProcessAudio();
}

SoundManager::SoundManager()
	: m_pImpl (std::make_unique<SoundImpl>())
{
}

SoundManager::~SoundManager()
{
}
