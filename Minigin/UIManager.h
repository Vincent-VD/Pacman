#pragma once
#include <functional>

#include "MiniginPCH.h"
#include "Singleton.h"
#include "imgui.h"
#include "UIWindow.h"

namespace dae
{
	class UIManager : public Singleton<UIManager>
	{
	public:
		void Init();

		void Render();

		void AddWindow( std::unique_ptr<UIWindow> window)
		{
			m_pWindows.emplace_back(std::move(window));
		}


	private:
		std::vector<std::unique_ptr<UIWindow>> m_pWindows;
	};
}