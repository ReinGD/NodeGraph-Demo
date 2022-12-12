#include "DLink.h"
#ifndef ITERATOR_H
#define ITERATOR_H
class Iterator 
{
public:
	virtual DLink* First() = 0;
	virtual DLink* Next() = 0;
	virtual bool isDone() = 0;
	virtual DLink* Current() = 0;
	virtual void Reset(DLink* head) = 0;



	virtual ~Iterator() = default;
};
#endif // !ITERATOR_H
