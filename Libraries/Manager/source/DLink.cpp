#include "DLink.h"
#include <iostream>

DLink::DLink()
	:pNext(nullptr), pPrev(nullptr), position(0)
{
}

DLink::DLink(const DLink& in)
	:pNext(in.pNext), pPrev(in.pPrev), position(in.position)
{
}

const DLink& DLink::operator=(const DLink& in)
{
	this->pNext = in.pNext;
	this->pPrev = in.pPrev;
	this->position = in.position;
	return *this;
}

void DLink::privClear()
{
	this->pNext = nullptr;
	this->pPrev = nullptr;
	this->position = 0;
}


void DLink::Print()
{
	std::cout << "Node at position: %i\n" << this->position;
	std::cout << "Next Node: %p\n" << this->pNext;
	std::cout << "Prev Node: %p\n" << this->pPrev;
}

void DLink::Clear()
{
	this->privClear();
}
