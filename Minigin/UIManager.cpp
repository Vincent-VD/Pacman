#include "UIManager.h"

#include "GameObject.h"
#include "UIBaseComponent.h"

void dae::UIManager::Render()
{
	for(const auto& window : m_pWindows)
	{
		window->GetComponent<UIBaseComponent>()->RenderUI();
	}
}
