#include "Exercise2.h"

#include "TrashTheCache.h"

dae::Exercise2::Exercise2(const std::string& windowTitle, ImGuiWindowFlags windowFlags)
	: UIWindow(windowTitle, windowFlags)
{
}

void dae::Exercise2::Render()
{
	ImGui::Begin(GetWindowTitle()/*, &m_IsOpen, GetWindowFlags()*/);

	ImGui::InputInt("Iterations", &m_Iterations, 10, 20);
	if (ImGui::Button("Trash The Cache with GameObject3D"))
	{
		m_XData1 = TrashTheCache::Exercise2<TrashTheCache::GameObject3D>(m_Iterations);

		m_PlotConfig1.values.xs = &m_XData1[0];
		m_PlotConfig1.values.ys = &m_YData[0];
		m_PlotConfig1.values.count = static_cast<int>(m_YData.size());
		m_PlotConfig1.values.colors = &colors[0];
		m_PlotConfig1.scale.min = 0;
		m_PlotConfig1.scale.max = 700;
		m_PlotConfig1.tooltip.show = true;
		m_PlotConfig1.tooltip.format = "x=%f, y=%f";
		m_PlotConfig1.grid_x.show = true;
		m_PlotConfig1.grid_y.show = true;
		m_PlotConfig1.frame_size = ImVec2(200, 200);
		m_PlotConfig1.line_thickness = 2.f;
					
		m_DrawPlot1 = true;
	}

	if (ImGui::Button("Trash The Cache with GameObject3DAlt"))
	{
		m_XData2 = TrashTheCache::Exercise2<TrashTheCache::GameObject3DAlt>(m_Iterations);

		m_PlotConfig2.values.xs = &m_XData2[0];
		m_PlotConfig2.values.ys = &m_YData[0];
		m_PlotConfig2.values.count = static_cast<int>(m_YData.size());
		m_PlotConfig2.values.colors = &colors[1];
		m_PlotConfig2.scale.min = 0;
		m_PlotConfig2.scale.max = 650;
		m_PlotConfig1.tooltip.show = true;
		m_PlotConfig1.tooltip.format = "x=%f, y=%f";
		m_PlotConfig2.grid_x.show = true;
		m_PlotConfig2.grid_y.show = true;
		m_PlotConfig2.frame_size = ImVec2(200, 200);
		m_PlotConfig2.line_thickness = 2.f;

		m_DrawPlot2 = true;
	}

	if (m_DrawPlot1)
	{
		ImGui::Plot("Trash The Cache GO3D", m_PlotConfig1);
	}

	if (m_DrawPlot2)
	{
		ImGui::Plot("Trash The Cache GO3DAlt", m_PlotConfig2);
	}

	if(m_DrawPlot1 && m_DrawPlot2)
	{
		auto yDataList{ std::vector<const float*>{m_PlotConfig1.values.ys, m_PlotConfig2.values.ys} };
		m_PlotConfigCombined.values.xs = m_PlotConfig1.values.xs;
		m_PlotConfigCombined.values.ys_list = &yDataList[0];
		m_PlotConfigCombined.values.ys_count = 2;
		m_PlotConfigCombined.values.count = 11;
		m_PlotConfigCombined.values.colors = colors;
		m_PlotConfigCombined.scale.min = 0;
		m_PlotConfigCombined.scale.max = 650;
		m_PlotConfigCombined.tooltip.show = true;
		m_PlotConfigCombined.tooltip.format = "x=%f, y=%f";
		m_PlotConfigCombined.grid_x.show = true;
		m_PlotConfigCombined.grid_y.show = true;
		m_PlotConfigCombined.frame_size = ImVec2(200, 200);
		m_PlotConfigCombined.line_thickness = 2.f;

		ImGui::Plot("Combined", m_PlotConfigCombined);
	}

	ImGui::End();
}
