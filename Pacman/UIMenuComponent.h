#ifndef UI_MENU_COMPONENT
#define UI_MENU_COMPONENT


#include "Observer.h"
#include "UIBaseComponent.h"
#include "UIState.h"

namespace pac
{
	class UIMenuComponent : public dae::UIBaseComponent, public dae::Observer<const std::string&>
	{
	public:
		//Created menu component and adds provided GO pointer to UIManager for rendering
		UIMenuComponent(dae::GameObject* pOwner, const std::string& windowTitle, ImGuiWindowFlags windowFlags = ImGuiBackendFlags_None);
		virtual ~UIMenuComponent() override;
		UIMenuComponent(const UIMenuComponent& other) = delete;
		UIMenuComponent(UIMenuComponent&& other) noexcept = delete;
		UIMenuComponent& operator=(const UIMenuComponent& other) = delete;
		UIMenuComponent& operator=(UIMenuComponent&& other) noexcept = delete;

		virtual void OnNotify(const std::string& action) override;
		virtual void OnSubjectDestroyed() override {}

		virtual void RenderUI() override;

	private:
		UIState* m_pState;
	};
}

#endif //UI_MENU_COMPONENT