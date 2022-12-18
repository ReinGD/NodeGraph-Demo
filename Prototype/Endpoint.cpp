/*====================
	MADE BY REINGD
====================*/
#include "Endpoint.h"
#include "NodeCreator.h"

Endpoint::Endpoint()
	:NodeBase(), output(this, Pin::PinType::OUTPUT, "Out")
{
	memset(buff, 0, 32);
}

Endpoint::~Endpoint()
{
}

void Endpoint::Execute()
{
	{
		NodeCreator createdNode(this);
		createdNode.PrepareNode(nullptr, nullptr, &this->output);


		ImGui::Separator();
		
		ImGui::SameLine();

		if (ImGui::CollapsingHeader("Enter Values"))
		{
			float width = 100.0f;

			ImGui::Text("Endpoint:");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(width);
			ImGui::InputText("##Bank", buff, 32);
			result = buff;
		}
	}
	this->NodeFunction();

}

void Endpoint::CreateNode(const char* const _name, float xPosition, float yPosition)
{
	NodeGraph::Add(new Endpoint(), Nodes::SpecificBank, _name, xPosition, yPosition);
}

void Endpoint::NodeFunction()
{
	output.SetValue(result);
}
