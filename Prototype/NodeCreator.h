#ifndef NODE_CREATOR_H
#define NODE_CREATOR_H
#include "NodeGraph.h"
#include "imgui.h"
#include "ImGuiGD.h"

class NodeCreator
{
public:
	NodeCreator() = delete;
	NodeCreator(NodeBase* node);
	~NodeCreator();

	NodeCreator(const NodeCreator&) = delete;
	NodeCreator& operator= (const NodeCreator&) = delete;

	/// <summary>
	/// Add nullptr if you do not need a specific Pin, for now supports 2 Inputs and 2 Outputs
	/// </summary>
	/// <param name="inputA">A</param>
	/// <param name="inputB">B</param>
	/// <param name="outputA">C</param>
	/// <param name="outputB">D</param>
	void PrepareNode(Pin* inputA = nullptr, Pin* inputB = nullptr, Pin* outputA = nullptr, Pin* outputB = nullptr);

private:
	unsigned int controlID;

};

#endif // !NODE_CREATOR_H
