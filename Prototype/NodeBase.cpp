#include "NodeBase.h"
#include "Pin.h"
#include "ImGuiGD.h"
#include <iostream>

#define UNUSED_VAR(x) (void(x))

NodeBase::NodeBase() 
{
	memset(this->name, 0, SHADER_NODE_NAME_SIZE);
	this->controlID = 0000;
	windowFlags = ImGuiWindowFlags_NoCollapse |
					ImGuiWindowFlags_NoResize | 
				  ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_AlwaysAutoResize;
	hasViewport = false;

}
NodeBase::~NodeBase()
{
	memset(this->name, 0, SHADER_NODE_NAME_SIZE);
	this->controlID = 0000;
}
void NodeBase::Set(const char* const _name, unsigned int id, float xPosition, float yPosition)
{
	Wash();
	strncpy_s(this->name, _name, SHADER_NODE_NAME_SIZE);
	controlID = id;
	x = xPosition;
	y = yPosition;
}
void NodeBase::Execute()
{
	//THIS SHOULDNT BE CALLED
	std::cout << ("THIS SHOULD NOT BE CALLED\n");
}
void NodeBase::Draw()
{
	std::cout << "NOTHING HERE\n";
}
bool NodeBase::Compare(DLink* pTarget)
{
	NodeBase* pData = (NodeBase*)pTarget;
	return this->controlID == pData->controlID;
}

void NodeBase::Print()
{
	std::cout << ("%s\n", this->name);
	std::cout << ("%04u\n", this->controlID);
}
void NodeBase::Wash()
{
	memset(this->name, 0, SHADER_NODE_NAME_SIZE);
	this->controlID = 0000;
}

void NodeBase::CreateNode(const char* const _name, float xPosition, float yPosition)
{
	UNUSED_VAR(_name);
	UNUSED_VAR(xPosition);
	UNUSED_VAR(yPosition);

	std::cout << ("THIS SHOULD NOT BE CALLED\n");
}

void NodeBase::NodeFunction()
{
	std::cout << ("THIS SHOULD NOT BE CALLED\n");
}


