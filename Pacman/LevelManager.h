#ifndef LEVEL_MANAGER
#define LEVEL_MANAGER

#include "Singleton.h"

namespace pac
{
	class LevelManager : public dae::Singleton<LevelManager>
	{
	public:
		void RegisterPellet();

		void DestroyPellet();

		bool GetLevelTransition() const { return m_LevelTransition; }
		void ResetLevelTransition() { m_LevelTransition = false; }

	private:
		int m_PelletAmount{};
		bool m_LevelTransition{ false };
	};
}


#endif //LEVEL_MANAGER
