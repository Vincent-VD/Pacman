#include "UIMenuComponent.h"

#include "Minigin.h"
#include "UIState.h"

pac::UIMenuComponent::UIMenuComponent(dae::GameObject* pOwner, const std::string& windowTitle, ImGuiWindowFlags windowFlags)
	: UIBaseComponent(pOwner, windowTitle, windowFlags)
	, m_pState(new MainMenuState{})
{
}

pac::UIMenuComponent::~UIMenuComponent()
{
	delete m_pState;
}

void pac::UIMenuComponent::OnNotify(const std::string& action)
{
	const auto newState{ m_pState->HandleInput(action) };
	if (newState != nullptr)
	{
		delete m_pState;
		m_pState = newState;
	}
}

void pac::UIMenuComponent::RenderUI()
{
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	const auto newState{ m_pState->Update() };
	if(newState != nullptr)
	{
		m_pState->OnExit();
		delete m_pState;
		m_pState = newState;
		m_pState->OnEnter();
	}
}
