/*====================
	MADE BY REINGD
====================*/
#ifndef OUTPUT_NODE_H
#define OUTPUT_NODE_H
#include "Pin.h"
#include "NodeBase.h"
#include "NodeCreator.h"

class OutputNode : public NodeBase
{
public:
	OutputNode();
	~OutputNode();


	virtual void Execute() override;

	static void CreateNode(const char* const _name, float xPosition, float yPosition);

	virtual void NodeFunction() override;

private:
	Pin input;
	std::string result;

	std::string header;
	std::string footer;
};

#endif // !OUTPUT_NODE_H
