#include "ManagerBase.h"
#include "ListBase.h"
#include "DLink_Manager.h"
#include <cassert>
#include <iostream>

ManagerBase::ManagerBase(int _mGrowth)
	:mActive(0), mReserve(0), mGrowth(_mGrowth)
{
	
	this->pActive = new DLink_Manager();
	this->pReserve = new DLink_Manager();
	assert(pActive != nullptr);
	assert(pReserve != nullptr);
}

ManagerBase::~ManagerBase()
{
	delete this->pActive;
	delete this->pReserve;
	this->mGrowth = 0;
	this->mReserve = 0;
	this->mActive = 0;
}


DLink* ManagerBase::baseAddToFront()
{
	Iterator* pIt = this->pReserve->GetIterator();
	if (pIt->First() == nullptr) this->privFillReserve(this->mGrowth);

	this->mReserve--;
	DLink* pNode = this->pReserve->Remove();
	pNode->Wash();
	assert(pNode != nullptr);

	this->mActive++;
	this->pActive->AddToFront(pNode);
	return pNode;
}

DLink* ManagerBase::baseAddToEnd()
{
	Iterator* pIt = this->pReserve->GetIterator();
	if (pIt->First() == nullptr) this->privFillReserve(this->mGrowth);

	this->mReserve--;
	DLink* pNode = this->pReserve->Remove();
	pNode->Wash();
	assert(pNode != nullptr);

	this->mActive++;
	this->pActive->AddToEnd(pNode);
	return pNode;
}

DLink* ManagerBase::baseAttach(const int position)
{

	Iterator* pIt = this->pReserve->GetIterator();
	if (pIt->First() == nullptr) this->privFillReserve(this->mGrowth);

	this->mReserve--;
	DLink* pNode = this->pReserve->Remove();
	pNode->Wash();
	assert(pNode != nullptr);

	this->mActive++;
	this->pActive->Attach(pNode, position);
	return pNode;
}

DLink* ManagerBase::baseAddSpecific(const DLink* pCurrent)
{
	Iterator* pIt = this->pReserve->GetIterator();

	if (pIt->First() == nullptr) this->privFillReserve(this->mGrowth);

	this->mReserve--;
	DLink* pNode = this->pReserve->Remove();
	pNode->Wash();
	assert(pNode != nullptr);

	this->mActive++;
	this->pActive->AddSpecific(pNode, pCurrent);
	return pNode;
}

void ManagerBase::baseRemove(const DLink* pNode)
{
	assert(pNode != nullptr);
	this->pActive->RemoveAt(pNode);
	this->mActive--;
	((DLink*)pNode)->pNext = nullptr;
	((DLink*)pNode)->pPrev = nullptr;
	this->mReserve++;
	this->pReserve->AddToFront(pNode);
}

DLink* ManagerBase::GetActiveHead() const
{
	Iterator* pIterator = this->pActive->GetIterator();
	return pIterator->First();
}

DLink* ManagerBase::GetReserveHead() const
{
	Iterator* pIterator = this->pReserve->GetIterator();
	return pIterator->First();
}

int ManagerBase::GetActiveTotal() const
{
	return this->mActive;
}

int ManagerBase::GetReserveTotal() const
{
	return this->mReserve;
}


void ManagerBase::baseSetReserve(const int reserve, const int growth)
{
	this->mGrowth = growth;
	if (reserve > this->mReserve)
	{
		this->privFillReserve(reserve - this->mReserve);
	}
}

DLink* ManagerBase::baseFind(DLink* _pNode)
{
	Iterator* pIterator = this->pActive->GetIterator();
	assert(pIterator != nullptr);

	DLink* pNode = pIterator->First();
	while(!pIterator->isDone())
	{
		if (pNode->Compare(_pNode)) break;
		pNode = pIterator->Next();
	}
	return pNode;
}


void ManagerBase::ReportData()
{
	std::cout << "----------------------------------------------\n";
	std::cout << "             Growth: %i \n" << mGrowth;
	std::cout << "        Total Nodes: %i \n" << mActive + mReserve;
	std::cout << "       Num Reserved: %i \n" << mReserve;
	std::cout << "         Num Active: %i \n" << mActive;
	std::cout << "----------------------------------------------\n";
}

void ManagerBase::FillReserve(int reserve)
{
	this->privFillReserve(reserve);
}

void ManagerBase::privFillReserve(int reserve)
{
	assert(reserve >= 0);
	this->mReserve += reserve;
	for (int i = 0; i < reserve; i++)
	{
		DLink* pNode = this->derivedCreateNode();
		assert(pNode != nullptr);
		this->pReserve->AddToFront(pNode);
	}

}
