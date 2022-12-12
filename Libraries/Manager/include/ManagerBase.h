#ifndef MANAGER_BASE_H
#define MANAGER_BASE_H

class ListBase;
#include "Iterator.h"

class ManagerBase 
{
public:
	ManagerBase() = delete;
	ManagerBase(int _mGrowth = 0);
	virtual ~ManagerBase();
	ManagerBase(const ManagerBase&) = delete;
	const ManagerBase& operator=(const ManagerBase&) = delete;

	DLink* baseAddToFront();
	DLink* baseAddToEnd();
	DLink* baseAttach(const int position);
	DLink* baseAddSpecific(const DLink* pCurrent);
	void baseRemove(const DLink* pNode);

	DLink* GetActiveHead() const;
	DLink* GetReserveHead() const;
	int GetActiveTotal() const;
	int GetReserveTotal() const;

protected:
	void baseSetReserve(const int reserve, const int growth);
	DLink* baseFind(DLink* pNode);
	DLink* baseFindMD5(DLink* pNode);

	virtual DLink* derivedCreateNode() = 0;
	virtual void ReportData();
	virtual void FillReserve(int reserve);
private:
	void privFillReserve(int reserve);
//Data
protected:
	ListBase* pActive;
	ListBase* pReserve;
private:
	int mActive;
	int mReserve;
	int mGrowth;

};
#endif // !MANAGER_BASE_H
