/*====================
	MADE BY REINGD
====================*/
#include "NodeCreator.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <string>

NodeCreator::NodeCreator(NodeBase* node)
{
	controlID = node->controlID;

	std::string fullName = node->name;
	fullName.append("##");
	fullName.append(std::to_string(this->controlID).c_str());

	ImGui::SetNextWindowPos(ImVec2(node->x, node->y), ImGuiCond_Once);
	ImGui::SetNextWindowSize(NodeGraph::DEFAULT_WINDOW_SIZE, ImGuiCond_Once);

	ImGui::Begin(fullName.c_str(), nullptr, node->windowFlags);

	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

}

NodeCreator::~NodeCreator()
{
	ImGui::Separator();

	
	ImGui::PopStyleVar();

	ImGui::End();
}

void NodeCreator::PrepareNode(Pin* inputA, Pin* inputB, Pin* outputA, Pin* outputB)
{
	//For now the setup is BeginColumn to start the table, next column writes to the right, EndColumn closes the table
	ImGuiGD::BeginColumn();
	if (inputA != nullptr)
	{
		inputA->Draw();
	}
	if (inputB != nullptr)
	{
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Dummy(ImVec2(10.0f, 0.0f));
		ImGui::SameLine();

		inputB->Draw();
	}

	//adjustment for when no inputs or outputs are present
	if (inputA == nullptr && inputB == nullptr)
	{
		ImGui::Dummy(ImVec2(30.0f, 0.0f));
	}


	ImGuiGD::NextColumn();
	if (outputA != nullptr)
	{
		outputA->Draw();
	}
	if (outputB != nullptr)
	{
		ImGui::Dummy(ImVec2(0.0f, 20.0f));

		outputB->Draw();
	}

	if (outputA == nullptr && outputB == nullptr)
		ImGui::Dummy(ImVec2(40.0f, 0.0f));

	ImGuiGD::EndColumn();

}
