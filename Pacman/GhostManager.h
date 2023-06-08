#ifndef GHOST_MANAGER
#define GHOST_MANAGER

#include "HeroComponent.h"
#include "Observer.h"
#include "Singleton.h"

namespace pac
{
	class GhostManager : public dae::Singleton<GhostManager>, public dae::Observer<PickupType>
	{
	public:
		void RegisterGhost(dae::GameObject* pGhost);

		virtual void OnNotify(PickupType pickup) override;
		virtual void OnSubjectDestroyed() override {}

	private:
		std::vector<dae::GameObject*> m_pGhosts;
	};
}


#endif //GHOST_MANAGER