#include "Exercise1.h"

#include "TrashTheCache.h"

dae::Exercise1::Exercise1(const std::string& windowTitle, ImGuiWindowFlags windowFlags)
	: UIWindow(windowTitle, windowFlags)
{
}

void dae::Exercise1::Render()
{
	ImGui::Begin(GetWindowTitle(), &m_IsOpen, GetWindowFlags());

	ImGui::InputInt("Iterations", &m_Iterations, 10, 20);
	if(ImGui::Button("Run"))
	{
		 m_XData = TrashTheCache::Exercise1(m_Iterations);

		m_PlotConfig.values.xs = &m_XData[0];
		m_PlotConfig.values.ys = &m_YData[0];
		m_PlotConfig.values.count = static_cast<int>(m_YData.size());
		m_PlotConfig.values.colors = colors;
		m_PlotConfig.scale.min = 0;
		m_PlotConfig.scale.max = 500;
		m_PlotConfig.grid_x.show = true;
		m_PlotConfig.grid_y.show = true;
		m_PlotConfig.frame_size = ImVec2(200, 200);
		m_PlotConfig.line_thickness = 2.f;

		m_DrawPlot = true;
	}

	if(m_DrawPlot)
	{
		ImGui::Plot("Trash The Cache 1", m_PlotConfig);
	}

	ImGui::End();
}
