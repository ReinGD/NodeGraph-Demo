#ifndef NODE_H
#define NODE_H

#include "DLink.h"
#include "NodeBase.h"

class Node : public DLink
{
public:

	Node(NodeBase::Nodes type);
	Node() = delete;
	Node(const Node&) = delete;
	Node& operator= (const Node&) = delete;
	virtual	~Node();
	void Set(const char* const _name, unsigned int id, float xPosition, float yPosition);
	void SetNode(NodeBase* node);
	void SetType(NodeBase::Nodes type);
	virtual void Execute();
	virtual void Draw();
	virtual bool Compare(DLink* pTarget);
	virtual void Print() override;
	virtual void Wash() override;

	NodeBase* GetNode();
private:
	bool isValid();


private:
	NodeBase::Nodes _type;
	NodeBase* pAttachedNode;

};
#endif // !NODE_H
