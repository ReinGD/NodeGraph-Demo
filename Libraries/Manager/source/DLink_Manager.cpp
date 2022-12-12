#include "DLink_Manager.h"
#include "DLink_Iterator.h"
#include "ListBase.h"
#include <cassert>

DLink_Manager::DLink_Manager()
	:pHead(nullptr), pLast(nullptr), pIterator(nullptr)
{

}

DLink_Manager::~DLink_Manager()
{
	this->pHead = nullptr;
	this->pLast = nullptr;
	//delete this->pIterator;
}

DLink_Manager::DLink_Manager(const DLink_Manager& in)
	:pHead(in.pHead), pLast(in.pLast)
{
}

const DLink_Manager& DLink_Manager::operator=(const DLink_Manager& in)
{
	this->pHead = in.pHead;
	this->pLast = in.pLast;
	return *this;
}

void DLink_Manager::Attach(const DLink* pNode, const int _position)
{
	//Comparing the position of the given node 
	//with the position of the current nodes

	assert(pNode != nullptr);
	assert(_position >= 0);

	if (this->pHead == nullptr) this->AddToFront(pNode);
	else 
	{
		DLink* pTmp = this->pHead;
		while (pTmp != nullptr)
		{
			if (pTmp->position > _position)
			{
				this->AddSpecific(pNode, pTmp);
				break;
			}
			pTmp = pTmp->pNext;
		}

		if (pTmp == nullptr) this->AddToEnd(pNode);

	}
	
}

void DLink_Manager::AddToFront(const DLink* pNode)
{
	assert(pNode != nullptr);

	DLink* pTmp = (DLink*)pNode;
	if (this->pHead == nullptr)
	{
		this->pHead = pTmp;
		this->pLast = this->pHead;
	}
	else 
	{
		pTmp->pPrev = nullptr;
		pTmp->pNext = this->pHead;
		
		this->pHead->pPrev = pTmp;
		this->pHead = pTmp;
	}
}

void DLink_Manager::AddSpecific(const DLink* pNew, const DLink* pCurrent)
{
	assert(pNew != nullptr);
	assert(pCurrent != nullptr);
	assert(pHead != nullptr);

	DLink* pNodeCurrent = (DLink*)pCurrent;
	DLink* pNodeNew = (DLink*)pNew;

	//Ordering is important, we are adding to the front once we get a value higher than ours
	if (pNodeCurrent->pNext == nullptr && pNodeCurrent->pPrev == nullptr)
	{
		//only one element
		this->pHead = pNodeNew;
		this->pHead->pNext = pNodeCurrent;
		pNodeCurrent->pPrev = this->pHead;
		this->pLast = pNodeCurrent;

		//for adding to the back
		/*this->pHead->pNext = pNodeNew;
		pNodeNew->pPrev = this->pHead;
		this->pLast = pNodeNew;*/

	}
	else if (pNodeCurrent->pPrev != nullptr && pNodeCurrent->pNext == nullptr)
	{
		//Last element
		pNodeNew->pNext = pNodeCurrent;
		pNodeNew->pPrev = pNodeCurrent->pPrev;
		pNodeNew->pPrev->pNext = pNodeNew;
		pNodeCurrent->pPrev = pNodeNew;
		this->pLast = pNodeCurrent;

		//for adding to the back
		/*pNodeCurrent->pNext = pNodeNew;
		pNodeNew->pPrev = pNodeCurrent;
		this->pLast = pNodeNew;*/

	}
	else if (pNodeCurrent->pPrev == nullptr && pNodeCurrent->pNext != nullptr)
	{
		//First but it has more elements
		pNodeNew->pNext = this->pHead;
		this->pHead->pPrev = pNodeNew;
		this->pHead = pNodeNew;
		this->pHead->pPrev = nullptr;

		//for adding to the back
		/*pNodeNew->pNext = this->pHead->pNext;
		this->pHead->pNext->pPrev = pNodeNew;
		pNodeNew->pPrev = this->pHead;
		this->pHead->pNext = pNodeNew;*/


	}
	else
	{
		//Middle Node
		pNodeNew->pNext = pNodeCurrent;
		pNodeNew->pPrev = pNodeCurrent->pPrev;
		pNodeNew->pPrev->pNext = pNodeNew;
		pNodeCurrent->pPrev = pNodeNew;

		//for adding to the back
		/*pNodeNew->pNext = pNodeCurrent->pNext;
		pNodeCurrent->pNext->pPrev = pNodeNew;
		pNodeNew->pPrev = pNodeCurrent;
		pNodeCurrent->pNext = pNodeNew;*/
	}
}

void DLink_Manager::AddToEnd(const DLink* pNode)
{
	assert(&pNode != nullptr);

	DLink* pTmp = (DLink*)pNode;
	if (this->pHead == nullptr)
	{
		this->pHead = pTmp;
		pTmp->pNext = nullptr;
		pTmp->pPrev = nullptr;
	}
	else
	{
		this->pLast->pNext = pTmp;
		pTmp->pPrev = this->pLast;
	}

	this->pLast = pTmp;
}

void DLink_Manager::RemoveAt(const DLink* pNode)
{
	assert(pHead != nullptr);
	assert(pNode != nullptr);
	DLink* pTmp = (DLink*)pNode;
	if (pTmp->pNext == nullptr && pTmp->pPrev == nullptr)
	{
		//Only one element
		this->pHead = nullptr;
		this->pLast = this->pHead;
	}
	else if (pTmp->pNext != nullptr && pTmp->pPrev == nullptr)
	{
		//First element with more
		this->pHead = pTmp->pNext;
		this->pHead->pPrev = pTmp->pPrev;
	}
	else if (pTmp->pNext == nullptr && pTmp->pPrev != nullptr)
	{
		//Last one
		this->pLast = pTmp->pPrev;
		this->pLast->pNext = pTmp->pNext;
	}
	else
	{
		//Middle node
		pTmp->pPrev->pNext = pTmp->pNext;
		pTmp->pNext->pPrev = pTmp->pPrev;
	}
}

DLink* DLink_Manager::Remove()
{
	assert(pHead != nullptr);
	DLink* pNode = (DLink*)this->pHead;
	this->pHead = this->pHead->pNext;
	if (this->pHead != nullptr) this->pHead->pPrev = nullptr;
	pNode->Clear();
	return *&pNode;
}

Iterator* DLink_Manager::GetIterator()
{
	if (this->pIterator == nullptr) this->pIterator = new DLink_Iterator();
	this->pIterator->Reset(this->pHead);
	return this->pIterator;
}
