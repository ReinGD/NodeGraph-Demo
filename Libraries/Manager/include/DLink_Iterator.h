/*====================
	MADE BY REINGD
====================*/
#include "Iterator.h"

#ifndef DLINK_ITERATOR_H
#define DLINK_ITERATOR_H
class DLink_Iterator : public Iterator
{
public:
	DLink_Iterator();
	virtual ~DLink_Iterator() = default;
	DLink_Iterator(const DLink_Iterator&) = delete;
	const DLink_Iterator& operator=(const DLink_Iterator&) = delete;
	void Reset(DLink*);

public:
	virtual DLink* Current();
	virtual DLink* First();
	virtual DLink* Next();
	bool isDone();
private:
	void privClear();

//data
public:
	DLink* pCurrent;
	DLink* pHead;
	bool bDone;
};
#endif // !DLINK_ITERATOR_H
