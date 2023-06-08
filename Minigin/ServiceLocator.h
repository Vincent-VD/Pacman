#ifndef SERVICE_LOCATOR
#define SERVICE_LOCATOR

#include "MiniginPCH.h"

#include "NullSoundSystem.h"
#include "SoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *m_pSoundSystem; }
		static void RegisterSoundSystem(SoundSystem* pSoundManager)
		{
			m_pSoundSystem = pSoundManager == nullptr ? &m_pNullSoundSystem : pSoundManager;
		}

		static void Shutdown()
		{
			if(m_pSoundSystem != &m_pNullSoundSystem)
			{
				delete m_pSoundSystem;
			}
			m_pSoundSystem = &m_pNullSoundSystem;
		}

	private:
		static SoundSystem* m_pSoundSystem;
		static NullSoundSystem m_pNullSoundSystem;
	};
}

#endif //SERVICE_LOCATOR