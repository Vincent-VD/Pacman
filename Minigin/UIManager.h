#ifndef UI_MANAGER
#define UI_MANAGER

#include "MiniginPCH.h"
#include "Singleton.h"

namespace dae
{
	class GameObject;

	class UIManager : public Singleton<UIManager>
	{
	public:
		void Render();

		void AddWindow(GameObject* window)
		{
			m_pWindows.emplace_back(window);
		}


	private:
		std::vector<GameObject*> m_pWindows;
	};
}

#endif //UI_MANAGER