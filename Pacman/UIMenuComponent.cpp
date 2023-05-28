#include "UIMenuComponent.h"

#include <iostream>

#include "UIState.h"

pac::UIMenuComponent::UIMenuComponent(dae::GameObject* pOwner, const std::string& windowTitle, ImGuiWindowFlags windowFlags)
	: UIBaseComponent(pOwner, windowTitle, windowFlags)
	, m_State(new MainMenuState{})
{
}

pac::UIMenuComponent::~UIMenuComponent()
{
	delete m_State;
}

void pac::UIMenuComponent::RenderUI()
{
	const auto newState{ m_State->Update() };
	if(newState != nullptr)
	{
		delete m_State;
		m_State = newState;
	}

}
