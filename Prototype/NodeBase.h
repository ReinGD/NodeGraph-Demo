#ifndef NODE_BASE_H
#define NODE_BASE_H

#include "imgui.h"
#include "DLink.h"

class Pin;

class NodeBase : public DLink
{
public:
	static const unsigned int SHADER_NODE_NAME_SIZE = 32;
	enum struct Nodes
	{
		Null,
		ChooseBank,
		SpecificBank,
		Transaction,
		Connector,
		Output
	};

public:
	NodeBase();
	~NodeBase();
	NodeBase(const NodeBase&) = delete;
	NodeBase& operator=(const NodeBase&) = delete;

	void Set(const char* const _name, unsigned int id, float xPosition, float yPosition);
	virtual void Execute();
	virtual void Draw();

	virtual bool Compare(DLink* pTarget);
	virtual void Print() override;
	virtual void Wash() override;

	static void CreateNode(const char* const _name, float xPosition, float yPosition);
	virtual void NodeFunction();


public:
	char name[SHADER_NODE_NAME_SIZE];
	unsigned int controlID;

	//position variable
	float x;
	float y;
	bool hasViewport;

	ImGuiWindowFlags windowFlags;

private:

};


#endif // !NODE_BASE_H
