#include "DLink_Iterator.h"

DLink_Iterator::DLink_Iterator()
	: Iterator()
{
	this->privClear();
}


void DLink_Iterator::Reset(DLink* _pHead)
{
	if (_pHead != nullptr)
	{
		this->bDone = false;
		this->pHead = (DLink*)_pHead;
		this->pCurrent = this->pHead;
	}
	else
		this->privClear();
}

DLink* DLink_Iterator::Current()
{
	return this->pCurrent;
}

DLink* DLink_Iterator::First()
{
	if (this->pHead != nullptr)
	{
		this->bDone = false;
		this->pCurrent = this->pHead;
	}
	else this->privClear();
	return this->pCurrent;
}

DLink* DLink_Iterator::Next()
{
	DLink* pNode = (DLink*)this->pCurrent;
	if (pNode != nullptr) pNode = pNode->pNext;
	this->pCurrent = pNode;

	if (this->pCurrent == nullptr) this->bDone = true;
	else this->bDone = false;

	return this->pCurrent;
}

bool DLink_Iterator::isDone()
{
	return this->bDone;
}


void DLink_Iterator::privClear()
{
	this->pCurrent = nullptr;
	this->pHead = nullptr;
	this->bDone = true;
}
