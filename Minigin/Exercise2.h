#pragma once
#include "imgui_plot.h"
#include "UIWindow.h"

namespace dae
{
	class Exercise2 : public UIWindow
	{
	public:
		Exercise2(const std::string& windowTitle, ImGuiWindowFlags windowFlags = ImGuiBackendFlags_None);
		virtual ~Exercise2() override = default;
		Exercise2(const Exercise2& other) = delete;
		Exercise2(Exercise2&& other) noexcept = delete;
		Exercise2& operator=(const Exercise2& other) = delete;
		Exercise2& operator=(Exercise2&& other) noexcept = delete;

		virtual void Render() override;

	private:
		bool m_IsOpen{ true };
		bool m_DrawPlot1{ false };
		bool m_DrawPlot2{ false };
		int m_Iterations{ 10 };
		std::vector<float> m_XData1{};
		std::vector<float> m_XData2{};
		std::vector<float> m_XData3{};
		std::vector<float> m_YData{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
		ImGui::PlotConfig m_PlotConfig1{};
		ImGui::PlotConfig m_PlotConfig2{};
		ImGui::PlotConfig m_PlotConfigCombined{};
		ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(255, 0, 0) };
	};

}

