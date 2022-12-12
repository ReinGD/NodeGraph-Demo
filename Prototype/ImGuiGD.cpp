#include "ImGuiGD.h""
void ImGuiGD::BeginPin()
{
}

void ImGuiGD::EndPin()
{
}

void ImGuiGD::BeginColumn()
{
	ImGui::BeginGroup();
	ImGui::Dummy(ImVec2(10.0f, 0.0f));
	ImGui::SameLine();
}

void ImGuiGD::NextColumn()
{
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(80.0f, 0.0f));
	ImGui::SameLine();
	ImGui::BeginGroup();
}

void ImGuiGD::EndColumn()
{
	ImGui::EndGroup();
}

bool ImGuiGD::CheckBoundaries(ImVec2 min, ImVec2 max, ImVec2 mousePosition) 
{
	return mousePosition.x > min.x && mousePosition.x < max.x && mousePosition.y > min.y && mousePosition.y < max.y;
}