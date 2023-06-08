#ifndef UI_BASE_COMPONENT
#define UI_BASE_COMPONENT

#include "imgui.h"
#include "RootComponent.h"

namespace dae
{
	class UIBaseComponent : public RootComponent
	{
	public:
		UIBaseComponent(GameObject* pOwner, const std::string& windowTitle, ImGuiWindowFlags windowFlags);
		virtual ~UIBaseComponent() override = default;
		UIBaseComponent(const UIBaseComponent& other) = delete;
		UIBaseComponent(UIBaseComponent&& other) noexcept = delete;
		UIBaseComponent& operator=(const UIBaseComponent& other) = delete;
		UIBaseComponent& operator=(UIBaseComponent&& other) noexcept = delete;

		virtual void RenderUI() = 0;
		virtual void Update() override {}
		virtual void Render() const override {}
		virtual void FixedUpdate() override {}

	protected:
		const char* GetWindowTitle() const { return m_WindowTitle.c_str(); }
		ImGuiWindowFlags GetWindowFlags() const { return m_WindowFlags; }

	private:
		const ImGuiWindowFlags m_WindowFlags;
		const std::string m_WindowTitle;
	};
}


#endif //UI_BASE_COMPONENT