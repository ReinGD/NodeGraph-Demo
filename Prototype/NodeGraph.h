#ifndef NODE_GRAPH_H
#define NODE_GRAPH_H

#include "ManagerBase.h"
#include "NodeBase.h"
#include "Node.h"
#include "Link.h"
#include <map>
#include <vector>

typedef void (*CreateFunction) (const char* const _name, float xPosition, float yPosition);
typedef std::map<std::string, CreateFunction> NodeMap;

class NodeGraph : public ManagerBase
{

public:
	static const ImVec2 DEFAULT_WINDOW_SIZE;
	static ImVec2 DEFAULT_SCREEN_SIZE;

	static unsigned int pinID;
	static unsigned int linkID;

public:
	static void Create(int reserveNum = 0, int reserveGrow = 1);
	static void Destroy();

	static void Update();

	static Node* Add(NodeBase* pCreatedNode, NodeBase::Nodes type, const char* const name, float xPosition, float yPosition);
	static Node* Find(unsigned int id);

	static void Remove(Node* pNode);
	static void Print();

	static void DrawCanvas();
	static void Draw();

	static void DragPin(Pin* pin);
	static void ResetPins();

	static void EstablishLink(Pin* sideA, Pin* sideB);
	static void HelpMarker(const char* desc);

private:
	static NodeGraph* privGetInstance();
	
	NodeGraph() = delete;
	NodeGraph(const NodeGraph&) = delete;
	NodeGraph& operator=(const NodeGraph&) = delete;

	NodeGraph(int reserveNum, int reserveGlow);
	~NodeGraph();

protected:
	DLink* derivedCreateNode() override;
private:
	Node* pNodeCompare;
	unsigned int NODEID;
	static NodeGraph* pInstance;
	NodeMap nodeMap;
	std::vector<Link*> usedLinks;

	Pin* pinA;
	Pin* pinB;

public:
	bool transactionGenerated;

};

#endif // !NODE_GRAPH_H
