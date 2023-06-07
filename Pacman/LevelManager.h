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

	private:
		int m_PelletAmount{};
	};
}


#endif //LEVEL_MANAGER
