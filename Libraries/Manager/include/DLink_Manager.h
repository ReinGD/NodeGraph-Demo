/*====================
	MADE BY REINGD
====================*/
#include "ListBase.h"
#include "Iterator.h"
#ifndef DLINK_MANAGER_H
#define DLINK_MANAGER_H

class DLink_Manager : public ListBase 
{
public:
	DLink_Manager();
	virtual ~DLink_Manager();
	DLink_Manager(const DLink_Manager&);
	const DLink_Manager& operator=(const DLink_Manager&);

	virtual void Attach(const DLink* pNode, const int position = 0);
	virtual void AddToFront(const DLink* pNode);
	virtual void AddSpecific(const DLink* pNew, const DLink* pCurrent);
	virtual void AddToEnd(const DLink* pNode);
	virtual void RemoveAt(const DLink* pNode);
	virtual DLink* Remove();
	virtual Iterator* GetIterator();

public:
	DLink* pHead;
	DLink* pLast;
	Iterator* pIterator;

};

#endif // !DLINK_MANAGER_H

