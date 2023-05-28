#pragma once
#include <functional>

#include "MiniginPCH.h"
#include "Singleton.h"
#include "imgui.h"
#include "UIWindow.h"

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