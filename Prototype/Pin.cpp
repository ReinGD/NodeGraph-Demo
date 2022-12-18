/*====================
	MADE BY REINGD
====================*/
#include "Pin.h"
#include "NodeGraph.h"
#include "ImGuiGD.h"

Pin::~Pin()
{
	ID = 0;
	pinStatus = Status::Inactive;
}

Pin::Pin(NodeBase* node, PinType type, const char* text)
	:ownedBy(node), pinType(type), pinStatus(Status::Inactive), pinDragStatus(DragStatus::No_Dragging)
{
	strncpy_s(this->pinText, text, NodeBase::SHADER_NODE_NAME_SIZE);
	ID = ++NodeGraph::pinID;
}

Pin::PinType Pin::GetType()
{
	return this->pinType;
}
void Pin::Activate() 
{
	this->pinStatus = Status::Active;
	this->pinDragStatus = DragStatus::No_Dragging;
}

void Pin::Deactivate() 
{
	this->pinStatus = Status::Inactive;
	this->pinDragStatus = DragStatus::No_Dragging;
}

void Pin::Draw()
{
	ImGui::PushID(this);
	ImGui::Text(this->pinText);
	
	ImColor color = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
	auto itemRectMin = ImGui::GetItemRectMin();
	auto itemRectMax = ImGui::GetItemRectMax();
	auto wSize = ImGui::GetItemRectSize();
	float offset = 10.0f;
	float offsetAdjustment = offset * 2.0f;

	//position depends on the pin type
	float positionAdjustment;
	if (this->pinType == PinType::INPUT)
	{
		positionAdjustment = itemRectMin.x - offset;
	}
	else
	{
		positionAdjustment = itemRectMax.x + offset;
	}
	
	this->position = ImVec2(positionAdjustment, itemRectMin.y + wSize.y / 2);




	ImVec2 graphicStart = ImVec2(itemRectMin.x - offsetAdjustment, itemRectMin.y);
	ImVec2 graphicEnd = ImVec2(itemRectMax.x + offsetAdjustment, itemRectMax.y);

	//if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)  && this->pinDragStatus != DragStatus::Dragging && ImGuiGD::CheckBoundaries(itemRectMin, itemRectMax, ImGui::GetMousePos()))
	//{
	//	this->pinDragStatus = DragStatus::Dragging;
	//	ShaderGraph::DragPin(this);
	//}



	ImVec2 buttonSize = ImVec2(graphicEnd.x - graphicStart.x, graphicEnd.y - graphicStart.y);
	auto windowPos = ImGui::GetWindowPos();
	ImVec2 buttonPos = ImVec2(-windowPos.x + graphicStart.x, -windowPos.y + graphicStart.y);
	ImGui::SetCursorPos(buttonPos);
	ImGui::SetItemAllowOverlap();
	
	if (ImGui::InvisibleButton("##dummy", buttonSize))
	{
		this->pinDragStatus = DragStatus::Dragging;
		NodeGraph::DragPin(this);
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_None))
	{

		if (pinDragStatus == DragStatus::Dragging)
		{
			color = ImColor(18, 186, 79, 120);
			ImGui::GetWindowDrawList()->AddRectFilled(graphicStart, graphicEnd, color, 20.f, ImDrawFlags_RoundCornersAll);

		}
		ImGui::GetWindowDrawList()->AddRect(graphicStart, graphicEnd, color, 20.f, ImDrawFlags_RoundCornersAll, 1.5f);


	}


	//try drag for first node and release for second node
	//also if inactive draw a circle border and if active add a smaller circle filled
	ImGui::GetWindowDrawList()->AddCircle(this->position, 8.0f, color);
	if (this->pinStatus == Status::Active)
	{
		color = ImColor(18, 186, 79, 120);
		ImGui::GetWindowDrawList()->AddCircleFilled(this->position, 6.0f, color);
	}


	ImGui::PopID();
}

ImVec2 Pin::GetPosition() 
{
	return this->position;
}

void Pin::SetDrag(DragStatus dS)
{
	this->pinDragStatus = dS;
}

std::string Pin::GetValue()
{
	return this->value;
}

void Pin::SetValue(std::string input)
{
	this->value = input;
}
