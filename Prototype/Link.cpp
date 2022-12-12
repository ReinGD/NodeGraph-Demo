#include "Link.h"

Link::~Link()
{
	Clean();
}

bool Link::operator==(const Link& rhL)
{
	bool A = this->pSideA == rhL.pSideA;
	bool B = this->pSideB == rhL.pSideB;

	bool C = this->pSideA == rhL.pSideB;
	bool D = this->pSideB == rhL.pSideA;

	return (A && B) || (C && D);

}

Link::Link()
	:pSideA(nullptr), pSideB(nullptr), linkID(0)
{
}
/// <summary>
/// Establishes the relation between 2 pins
/// </summary>
/// <param name="sideA"></param>
/// <param name="sideB"></param>
/// <returns>False if at least one pin is missing</returns>
bool Link::EstablishConnection(Pin* sideA, Pin* sideB)
{
	bool result = true;
	this->pSideA = sideA;
	this->pSideB = sideB;
	result = this->pSideA == nullptr || this->pSideB == nullptr;
	return !result;
}

void Link::DrawLink() 
{
	auto color = ImColor(18, 186, 79, 120);
	auto offset = 200.0f;


	auto sideApos = this->pSideA->GetPosition();
	auto sideBpos = this->pSideB->GetPosition();

	auto drawList = ImGui::GetForegroundDrawList();

	ImVec2 points[4] = { sideBpos,
						 ImVec2(sideBpos.x + offset, sideBpos.y),
						 ImVec2(sideApos.x - offset, sideApos.y),
						 sideApos };

	drawList->AddBezierCubic(points[0], points[1], points[2], points[3], color, 5.0f);

	//set the values
	if (this->pSideA->GetType() == Pin::PinType::OUTPUT)
		this->pSideB->SetValue(this->pSideA->GetValue());
	else
		this->pSideA->SetValue(this->pSideB->GetValue());
	

}

void Link::Clean()
{
	this->pSideA = nullptr;
	this->pSideB = nullptr;
}

void Link::SetID(unsigned int ID)
{
	this->linkID = ID;
}