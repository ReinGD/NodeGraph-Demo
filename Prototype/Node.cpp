#include "Node.h"

Node::Node(NodeBase::Nodes type)
	:pAttachedNode(nullptr)
{
	this->_type = type;
}

Node::~Node()
{
	this->_type = NodeBase::Nodes::Null;
	delete this->pAttachedNode;
}

void Node::SetNode(NodeBase* pNode) 
{
	this->pAttachedNode = pNode;
}
void Node::Execute()
{
	if (isValid())
		this->pAttachedNode->Execute();
}
void Node::Draw()
{
	if (isValid())
		this->pAttachedNode->Draw();
}
void Node::Set(const char* const _name, unsigned int id, float xPosition, float yPosition)
{
	if (isValid())
		this->pAttachedNode->Set(_name, id, xPosition, yPosition);
}
void Node::SetType(NodeBase::Nodes type) 
{
	this->_type = type;
}
bool Node::Compare(DLink* pTarget)
{
	bool result = false;
	if (isValid())
		result = this->pAttachedNode->Compare(pTarget);

	return result;
}

void Node::Print()
{
	if(isValid())
		this->pAttachedNode->Print();
}

void Node::Wash()
{
	if (isValid())
		this->pAttachedNode->Wash();
}

bool Node::isValid()
{
	return this->pAttachedNode != nullptr;
}

NodeBase* Node::GetNode() 
{
	return this->pAttachedNode;
}