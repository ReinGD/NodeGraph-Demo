#include "NodeGraph.h"
#include "ListBase.h"
#include "AllNodes.h"

const ImVec2 NodeGraph::DEFAULT_WINDOW_SIZE = ImVec2(200.0f, 200.0f);
ImVec2 NodeGraph::DEFAULT_SCREEN_SIZE = ImVec2(0.0f, 0.0f);
unsigned int NodeGraph::pinID = 0;
unsigned int NodeGraph::linkID = 0;
NodeGraph* NodeGraph::pInstance = nullptr;

void NodeGraph::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

NodeGraph* NodeGraph::privGetInstance()
{
	return pInstance;
}

NodeGraph::NodeGraph(int reserveNum, int reserveGrow)
	: ManagerBase(reserveGrow)
{
	// Preload the reserve
	this->FillReserve(reserveNum);

	// initialize derived data here
	this->pNodeCompare = new Node(NodeBase::Nodes::Null);
	this->NODEID = 0000;

	this->pinA = nullptr;
	this->pinB = nullptr;

	this->transactionGenerated = false;

	nodeMap.emplace("Endpoint", Endpoint::CreateNode);
	nodeMap.emplace("Contract", Contract::CreateNode);
	nodeMap.emplace("Connector", Connector::CreateNode);

}




NodeGraph::~NodeGraph()
{
	delete this->pNodeCompare;
	this->pNodeCompare = nullptr;

	// iterate through the list and delete
	Iterator* pIt1 = this->pActive->GetIterator();

	DLink* pNode = pIt1->First();

	// Walk through the nodes
	while (!pIt1->isDone())
	{
		auto pDeleteMe = (Node*)pIt1->Current();
		pNode = pIt1->Next();
		delete pDeleteMe;
	}
	delete pIt1;

	Iterator* pIt2 = this->pReserve->GetIterator();

	pNode = pIt2->First();

	// Walk through the nodes
	while (!pIt2->isDone())
	{
		auto pDeleteMe = (Node*)pIt2->Current();
		pNode = pIt2->Next();
		delete pDeleteMe;
	}
	delete pIt2;


	std::vector<Link*>().swap(usedLinks);
}

void NodeGraph::Create(int reserveNum, int reserveGrow)
{
	assert(reserveNum >= 0);
	assert(reserveGrow > 0);

	assert(pInstance == nullptr);

	pInstance = new NodeGraph(reserveNum, reserveGrow);
	pInstance->DEFAULT_SCREEN_SIZE = ImVec2(2500, 1400);
	//initialize the output node, this is required as this shows the output of the shader graph
	OutputNode::CreateNode("Output", 400.0f, 100.0f);
}

void NodeGraph::Destroy()
{
	auto pMan = NodeGraph::privGetInstance();
	delete pMan;
}

void NodeGraph::Update()
{
	auto instance = NodeGraph::privGetInstance();


	DrawCanvas();

	if (ImGui::IsMouseClicked(1))
		ImGui::OpenPopup("AddNode");

	if (ImGui::BeginPopup("AddNode"))
	{
		static ImGuiTextFilter filter;
		ImGui::Text("Search Node");
		ImGui::SetNextItemWidth(NodeGraph::DEFAULT_WINDOW_SIZE.x);
		filter.Draw();

		for (auto it = instance->nodeMap.begin(); it != instance->nodeMap.end(); it++)
		{
			if (filter.PassFilter(it->first.c_str()))
			{
				if (ImGui::Button(it->first.c_str(), ImVec2(120.0f, 40.0f)))
				{
					ImVec2 mousePos = ImGui::GetMousePos();

					//Call the create function for the selected Node Type
					it->second(it->first.c_str(), mousePos.x, mousePos.y);
				}
			}
		}
		
		ImGui::EndPopup();
	}

	auto pIterator = instance->pActive->GetIterator();
	//Execute all the nodes 
	Node* pNode = (Node*)pIterator->First();
	while (!pIterator->isDone())
	{
		pNode->Execute();
		pNode = (Node*)pIterator->Next();
	}


}

Node* NodeGraph::Add(NodeBase* pCreatedNode, NodeBase::Nodes type, const char* const name, float xPosition, float yPosition)
{
	auto pMan = NodeGraph::privGetInstance();


	Node* pNode = (Node*)pMan->baseAddToFront();
	pNode->SetNode(pCreatedNode);
	pNode->SetType(type);
	pNode->Set(name, pMan->NODEID, xPosition, yPosition);
	
	assert(pNode);
	pMan->NODEID++;
	return pNode;
}

Node* NodeGraph::Find(unsigned int id)
{
	auto pMan = NodeGraph::privGetInstance();
	pMan->pNodeCompare->GetNode()->controlID = id;
	Node* pNode = (Node*)pMan->baseFind(pMan->pNodeCompare);

	return pNode;
}

void NodeGraph::Remove(Node* pNode)
{
	assert(pNode != nullptr);

	NodeGraph* pMan = NodeGraph::privGetInstance();
	assert(pMan != nullptr);

	pMan->baseRemove(pNode);

}

void NodeGraph::Print()
{
	NodeGraph* pMan = NodeGraph::privGetInstance();
	assert(pMan != nullptr);

	pMan->ReportData();

	Iterator* pIt = pMan->pActive->GetIterator();
	Node* pNode = (Node*)pIt->First();
	while (!pIt->isDone())
	{
		pNode->Print();
		pNode = (Node*)pIt->Next();
	}
}

void NodeGraph::DragPin(Pin* pin)
{
	// Input < - > Output == Valid
	//Output < - > Input  == Valid

	//Need to implement these validations next
	
	// Input < - > Input  == Invalid
	//Output < - > Output == Invalid

	

	auto pMan = NodeGraph::privGetInstance();
	auto &sideA = pMan->pinA;
	auto &sideB = pMan->pinB;



	if (pin->GetType() == Pin::PinType::INPUT && sideA == nullptr)
	{
		sideA = pin;
	}

	if (pin->GetType() == Pin::PinType::OUTPUT && sideB == nullptr)
	{
		sideB = pin;
	}

	if (sideA && sideB) EstablishLink(sideA, sideB);


}

void NodeGraph::ResetPins() 
{
	auto pMan = NodeGraph::privGetInstance();

	if (pMan->pinA != nullptr) pMan->pinA->SetDrag(Pin::DragStatus::No_Dragging);
	if (pMan->pinB != nullptr) pMan->pinB->SetDrag(Pin::DragStatus::No_Dragging);

	pMan->pinA = nullptr;
	pMan->pinB = nullptr;

}
void NodeGraph::EstablishLink(Pin* sideA, Pin* sideB)
{
	//check this eventually
	Link* tryLink = new Link();
	if (tryLink->EstablishConnection(sideA, sideB))
	{
		sideA->Activate();
		sideB->Activate();
		auto pMan = NodeGraph::privGetInstance();
		bool found = false;
		//check that link does not already exists
		for (Link* var : pMan->usedLinks)
		{
			if (*var == *tryLink)
			{
				found = true;
				delete tryLink;
				break;
			}
		}

		
		if (!found)
		{
			tryLink->SetID(++NodeGraph::linkID);
			pMan->usedLinks.push_back(tryLink);
		}
	}
	else delete tryLink;
	ResetPins();
}

DLink* NodeGraph::derivedCreateNode()
{
	return new Node(NodeBase::Nodes::Null);
}

void NodeGraph::DrawCanvas()
{
	static ImVector<ImVec2> points;
	static ImVec2 scrolling(0.0f, 0.0f);
	auto instance = NodeGraph::privGetInstance();
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize			  | ImGuiWindowFlags_NoNavFocus  
								 | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse;
	
	ImGui::Begin("NodeGraph", 0, windowFlags);

	ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
	ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
	

	ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

	// Draw border and background color
	ImGuiIO& io = ImGui::GetIO();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(2, 20, 32, 255));
	draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(69, 75, 79, 255));

	ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const ImVec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
	const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);
	// Draw grid + all lines in the canvas
	draw_list->PushClipRect(canvas_p0, canvas_p1, true);

	const float GRID_STEP = 64.0f;
	for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
		draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
	for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
		draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
	

	for (Link* var : instance->usedLinks)
	{
		var->DrawLink();
	}

	ImGui::End();
}

void NodeGraph::Draw()
{
	auto instance = privGetInstance();
	auto pIterator = instance->pActive->GetIterator();
	//Execute all the nodes 
	Node* pNode = (Node*)pIterator->First();
	while (!pIterator->isDone())
	{
		pNode->Draw();
		pNode = (Node*)pIterator->Next();
	}

}
