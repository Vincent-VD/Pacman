#include "UIMenuComponent.h"

#include "Minigin.h"
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

void pac::UIMenuComponent::OnNotify(std::string action)
{
	const auto newState{ m_State->HandleInput(action) };
	if (newState != nullptr)
	{
		delete m_State;
		m_State = newState;
	}
}

void pac::UIMenuComponent::RenderUI()
{
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	const auto newState{ m_State->Update() };
	if(newState != nullptr)
	{
		m_State->OnExit();
		delete m_State;
		m_State = newState;
		m_State->OnEnter();
	}
}
