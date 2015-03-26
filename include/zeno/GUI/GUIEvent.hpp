#ifndef INCLUDED_ZENO_GUI_GUI_EVENT_HPP
#define INCLUDED_ZENO_GUI_GUI_EVENT_HPP

#include <zeno/System/Mouse.hpp>
#include <zeno/System/Keyboard.hpp>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Event type for gui system
//
////////////////////////////////////////////////////////////
class GUIEvent
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Enumeration of event types
	//
	////////////////////////////////////////////////////////////
	enum EventType {
		LeftClick,
		LeftRelease
	};
	
	////////////////////////////////////////////////////////////
	//
	//	Struct representing data of a mouse button event
	//
	////////////////////////////////////////////////////////////
	struct MouseButtonEvent {
		Mouse::Button	button;
		int				x;
		int				y;
	};

public:
	////////////////////////////////////////////////////////////
	//
	//	Event type
	//
	////////////////////////////////////////////////////////////
	EventType			type;
	
	////////////////////////////////////////////////////////////
	//
	//	Union containing all types of events possible
	//
	////////////////////////////////////////////////////////////
	union {
		MouseButtonEvent	mouseButton;
	};
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_GUI_EVENT_HPP