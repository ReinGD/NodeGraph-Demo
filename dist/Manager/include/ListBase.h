/*====================
	MADE BY REINGD
====================*/
#include "Iterator.h"

#ifndef LIST_BASE_H
#define LIST_BASE_H
class ListBase 
{
public:
	ListBase() = default;
	virtual ~ListBase() = default;
	ListBase(const ListBase&) = delete;
	ListBase& operator=(const ListBase&) = delete;

	virtual void Attach(const DLink*, const int) = 0;
	virtual void AddToFront(const DLink*) = 0;
	virtual void AddSpecific(const DLink*, const DLink*) = 0;
	virtual void AddToEnd(const DLink*) = 0;
	virtual void RemoveAt(const DLink*) = 0;
	virtual DLink* Remove() = 0;
	virtual Iterator* GetIterator() = 0;
};
#endif // !LIST_BASE_H
