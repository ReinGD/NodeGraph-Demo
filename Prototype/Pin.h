/*====================
	MADE BY REINGD
====================*/
#ifndef PIN_H
#define PIN_H

#include "NodeBase.h"
#include <string>

//This class defines the individual pins for a Node
class Pin
{

public:
	/// <summary>
	/// Pins are set to Input or Output depending on the node
	/// </summary>
	enum struct PinType
	{
		INPUT,
		OUTPUT
	};

	/// <summary>
	/// Status is used for when a Pin is used, inactive 
	/// </summary>
	enum struct Status
	{
		Active,
		Inactive
	};
	/// <summary>
	/// DragStatus is used when the pin is currently being dragged
	/// </summary>
	enum struct DragStatus
	{
		Dragging,
		No_Dragging
	};
public:
	Pin() = delete;
	~Pin();
	Pin(const Pin&) = delete;
	Pin& operator = (const Pin&) = delete;

	Pin(NodeBase* node, PinType type, const char* text); 

	void Draw();
	PinType GetType();
	void Activate();
	void Deactivate();

	ImVec2 GetPosition();

	void SetDrag(DragStatus dS);
	std::string GetValue();
	void SetValue(std::string input);
private:
			  ImVec2 position;
	 NodeBase* ownedBy;
	            char pinText[NodeBase::SHADER_NODE_NAME_SIZE];
			 PinType pinType;
			  Status pinStatus;
	      DragStatus pinDragStatus;
		unsigned int ID;
		 std::string value;
};

#endif // !PIN_H
