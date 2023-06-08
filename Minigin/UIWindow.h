#ifndef UI_WINDOW
#define UI_WINDOW

#include "MiniginPCH.h"
#include "imgui.h"

namespace dae
{
	class UIWindow
	{
	public:
		UIWindow(const std::string& windowTitle, ImGuiWindowFlags windowFlags);
		virtual ~UIWindow() = default;
		UIWindow(const UIWindow& other) = delete;
		UIWindow(UIWindow&& other) noexcept = delete;
		UIWindow& operator=(const UIWindow& other) = delete;
		UIWindow& operator=(UIWindow&& other) noexcept = delete;

		virtual void Render() = 0;

	protected:
		const char* GetWindowTitle() const { return m_WindowTitle.c_str(); }
		ImGuiWindowFlags GetWindowFlags() const{ return m_WindowFlags; }

	private:
		const ImGuiWindowFlags m_WindowFlags;
		const std::string m_WindowTitle;
	};
}

#endif //UI_WINDOW