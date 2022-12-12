#ifndef LINK_H
#define LINK_H

#include "Pin.h"
//This class specifies the link between 2 nodes

class Link
{
public:
	Link();
	~Link();
	Link(const Link&) = delete;
	Link& operator= (const Link&) = delete;
	bool operator==(const Link& rhL);

	//SideB is null in case no Pin is selected when dropped
	bool EstablishConnection(Pin* sideA, Pin* sideB = nullptr);

	void DrawLink();
	void SetID(unsigned int id);
private:
	void Clean();
private:
	Pin* pSideA;
	Pin* pSideB;
	unsigned int linkID;
};
#endif // !LINK_H
