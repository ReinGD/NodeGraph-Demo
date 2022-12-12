#ifndef ENDPOINT_H
#define ENDPOINT_H
#include "NodeBase.h"
#include "Pin.h"

class Endpoint : public NodeBase
{
public:
	Endpoint();
	~Endpoint();

	virtual void Execute() override;

	static void CreateNode(const char* const _name, float xPosition, float yPosition);

	virtual void NodeFunction() override;

private:
	Pin output;

	std::string result;
	char buff[32];

};


#endif // !ENDPOINT_H
