/*====================
	MADE BY REINGD
====================*/
#ifndef DLINK_H
#define DLINK_H


class DLink
{
protected:
	DLink();
	virtual ~DLink() = default;
	DLink(const DLink&);
	const DLink& operator=(const DLink&);


private:
	void privClear();
public:
	virtual void Wash() = 0;
	virtual void Print();
	void Clear();
	virtual char* GetName()
	{
		return nullptr;
	}
	virtual bool Compare(DLink* pTargetNode) = 0;

public:
	DLink* pNext;
	DLink* pPrev;
	int position;
};
#endif // !DLINK_H
