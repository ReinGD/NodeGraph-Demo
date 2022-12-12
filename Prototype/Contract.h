#ifndef CONTRACT_H
#define CONTRACT_H
#include "NodeBase.h"
#include "Pin.h"

class Contract : public NodeBase
{
public:
	enum struct Signature : int
	{
		HAGD = 0,
		SYLT = 1,
		FMWL = 2,
		EYP = 3
	};

public:
	Contract();
	~Contract();

	virtual void Execute() override;

	static void CreateNode(const char* const _name, float xPosition, float yPosition);

	virtual void NodeFunction() override;

private:
	Pin inputA;
	Pin inputB;
	Pin output;

	Signature signature;
	std::string result;
	std::string message;
	char buff[32];
	int selectedSignature;
};

#endif // !CONTRACT_H
