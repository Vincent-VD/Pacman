#include "UIBaseComponent.h"

#include "UIManager.h"

dae::UIBaseComponent::UIBaseComponent(GameObject* pOwner, const std::string& windowTitle, ImGuiWindowFlags windowFlags)
	: RootComponent(pOwner)
	, m_WindowFlags(windowFlags)
	, m_WindowTitle(windowTitle)
{
	UIManager::GetInstance().AddWindow(pOwner);
}
