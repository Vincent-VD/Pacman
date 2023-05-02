#include "SoundManager.h"
using namespace dae;


class SoundManager::SoundImpl
{
public:
	SoundImpl() = default;

	~SoundImpl() = default;

	SoundImpl(const SoundImpl& other) = delete;
	SoundImpl(SoundImpl&& other) noexcept = delete;
	SoundImpl& operator=(const SoundImpl& other) = delete;
	SoundImpl& operator=(SoundImpl&& other) noexcept = delete;

	void PlayAudio(const std::string filename, const float volume)
	{
		std::cout << filename << " @ " << volume << std::endl;
    }
};

void SoundManager::Init()
{
	m_Head = 0;
	m_Tail = 0;
	m_PendingSounds = std::vector<SoundDesc>(MAX_PENDING);
	m_pImpl = new SoundImpl ();
}

SoundManager::~SoundManager()
{
	delete m_pImpl;
}

void SoundManager::AddSound(const std::string& soundPath)
{
	m_SoundPaths.emplace_back(soundPath);
}

void SoundManager::PlaySound(SoundDesc soundDesc)
{
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
}

void SoundManager::Update()
{
	if (m_Head == m_Tail) return;

	std::string path{ "../Data/" };

	const SoundDesc soundDesc{ m_PendingSounds[m_Head] };

	m_pImpl->PlayAudio(path.c_str() + m_SoundPaths[soundDesc.id], soundDesc.volume);

	m_Head = (m_Head + 1) % MAX_PENDING;
}
