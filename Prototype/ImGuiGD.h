/*====================
	MADE BY REINGD
====================*/
#ifndef IM_GUI_GD_H
#define IM_GUI_GD_H
#include "imgui.h"

class ImGuiGD
{
public:
	ImGuiGD() = default;
	~ImGuiGD() = default;
	ImGuiGD(const ImGuiGD&) = delete;
	ImGuiGD& operator=(const ImGuiGD&) = delete;


	static void BeginPin();
	static void EndPin();

	static void BeginColumn();
	static void NextColumn();
	static void EndColumn();

	static bool CheckBoundaries(ImVec2 min, ImVec2 max, ImVec2 mousePosition);


private:

};

#endif // !IM_GUI_GD_H
