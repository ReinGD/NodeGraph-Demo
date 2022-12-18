/*====================
	MADE BY REINGD
====================*/
#include "Connector.h"
#include "NodeCreator.h"

Connector::Connector()
	:NodeBase(),
	inputA(this, Pin::PinType::INPUT, "A"),
	inputB(this, Pin::PinType::INPUT, "B"),
	output(this, Pin::PinType::OUTPUT, "Out")
{

}

Connector::~Connector()
{
}

void Connector::Execute()
{
	//----------- Guards here
	{
		NodeCreator createdNode(this);
		createdNode.PrepareNode(&this->inputA, &this->inputB, &this->output);
	}
	//----------- Scope ends Here

	this->NodeFunction();

}

void Connector::CreateNode(const char* const _name, float xPosition, float yPosition)
{
	NodeGraph::Add(new Connector(), Nodes::Connector, _name, xPosition, yPosition);
}

void Connector::NodeFunction()
{
	result = inputA.GetValue();
	result.append("\n\n *** A connector node was used here *** \n\n");
	result.append(inputB.GetValue());

	output.SetValue(result);
}
