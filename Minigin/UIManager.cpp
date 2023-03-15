#include "UIManager.h"
#include "UIWindow.h"

void dae::UIManager::Init()
{
}

void dae::UIManager::Render()
{
	for(auto& window : m_pWindows)
	{
		window->Render();
	}
}
