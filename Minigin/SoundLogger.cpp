#include "SoundLogger.h"

#include <iostream>


dae::SoundLogger::SoundLogger(SoundSystem* pSoundSystem)
	: m_pSoundSystem{ pSoundSystem }
{
}

dae::SoundLogger::~SoundLogger()
{
	delete m_pSoundSystem;
}

int dae::SoundLogger::AddSound(const std::string& soundPath)
{
	const int res{ m_pSoundSystem->AddSound(soundPath) };

	std::cout << "Sound added: \"" << soundPath << " \"with id: " << res << std::endl;

	return res;
}

void dae::SoundLogger::PlaySound(SoundDesc soundDesc)
{
	m_pSoundSystem->PlaySound(soundDesc);

	std::cout << "Sound played with id: " << soundDesc.id << " @ " << soundDesc.volume << "volume\n";
}

void dae::SoundLogger::PauseSound()
{
	m_pSoundSystem->PauseSound();

	std::cout << "Sound paused\n";
}

void dae::SoundLogger::ResumeSound()
{
	m_pSoundSystem->ResumeSound();

	std::cout << "Sound resumed";
}

void dae::SoundLogger::Update()
{
	m_pSoundSystem->Update();
}

