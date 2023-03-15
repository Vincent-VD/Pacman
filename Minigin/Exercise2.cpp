#include "Exercise2.h"

dae::Exercise2::Exercise2(const std::string& windowTitle, ImGuiWindowFlags windowFlags)
	: UIWindow(windowTitle, windowFlags)
{
}

void dae::Exercise2::Render()
{
	ImGui::Begin(GetWindowTitle()/*, &m_IsOpen, GetWindowFlags()*/);

	ImGui::Text("Button!");

	if (ImGui::Button("Test BUTTON"))
	{

	}

	ImGui::End();
}
