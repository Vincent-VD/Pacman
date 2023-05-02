#pragma once
#include "MiniginPCH.h"
#include "Singleton.h"

namespace dae
{

	class SoundManager : public Singleton<SoundManager>
	{
		class SoundImpl;
		std::unique_ptr<SoundImpl> m_pImpl;

	public:
		void Init();

		virtual ~SoundManager() override = default;
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) noexcept = delete;
		SoundManager& operator=(const SoundManager& other) = delete;
		SoundManager& operator=(SoundManager&& other) noexcept = delete;

		void AddSound(const std::string& soundPath);

		void PlaySound(int soundType, float volume);
		void Update();

	private:
		friend class Singleton<SoundManager>;
		SoundManager() = default;
		static const int MAX_PENDING{ 16 };
		int m_Head{};
		int m_Tail{};
		std::vector<int> m_PendingSounds;
		std::vector<std::string> m_SoundPaths;


	};
}


