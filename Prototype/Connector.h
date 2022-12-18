/*====================
	MADE BY REINGD
====================*/
#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "NodeBase.h"
#include "Pin.h"

class Connector : public NodeBase
{
public:
	Connector();
	~Connector();

	virtual void Execute() override;

	static void CreateNode(const char* const _name, float xPosition, float yPosition);
	void NodeFunction() override;

private:
	Pin inputA;
	Pin inputB;
	Pin output;

	std::string result;
};

#endif // !CONNECTOR_H
