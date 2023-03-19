#pragma once
#include "imgui_plot.h"
#include "UIWindow.h"

namespace dae
{
	class Exercise1 : public UIWindow
	{
	public:
		Exercise1(const std::string& windowTitle, ImGuiWindowFlags windowFlags = ImGuiBackendFlags_None);
		~Exercise1() = default;
		Exercise1(const Exercise1& other) = delete;
		Exercise1(Exercise1&& other) noexcept = delete;
		Exercise1& operator=(const Exercise1& other) = delete;
		Exercise1& operator=(Exercise1&& other) noexcept = delete;

		virtual void Render() override;

	private:
		bool m_IsOpen{ true };
		bool m_DrawPlot{ false };
		int m_Iterations{ 10 };
		std::vector<float> m_XData{};
		std::vector<float> m_YData{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
		ImGui::PlotConfig m_PlotConfig{};
		ImU32 colors[1] = { ImColor(0, 255, 0) };
	};
}


