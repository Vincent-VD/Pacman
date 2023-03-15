#include "UIWindow.h"

dae::UIWindow::UIWindow(const std::string& windowTitle, ImGuiWindowFlags windowFlags)
	: m_WindowFlags(windowFlags)
	, m_WindowTitle(windowTitle)
{
}
