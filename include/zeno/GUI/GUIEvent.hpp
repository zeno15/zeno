#ifndef INCLUDED_ZENO_GUI_GUI_EVENT_HPP
#define INCLUDED_ZENO_GUI_GUI_EVENT_HPP

#include <zeno/System/Mouse.hpp>
#include <zeno/System/Keyboard.hpp>

#include <cstdint>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief	Event for the GUI system
///
////////////////////////////////////////////////////////////
class GUIEvent
{
public:
    GUIEvent()
    {

    }
    GUIEvent(const GUIEvent& _event)
    {
        type = _event.type;
    }
    ~GUIEvent()
    {

    }
	////////////////////////////////////////////////////////////
	///
	///	\brief  Enumeration of event types
	///
	////////////////////////////////////////////////////////////
	enum EventType {
		LeftClick,      ///<    Left mouse button clicked   (data in event.mouseButton)
		LeftRelease,    ///<    Left mouse button released  (data in event.mouseButton)
		MouseMove,      ///<    Mouse cursor has moved      (data in event.mouseMove)
		ProgressUpdate, ///<    Progress bar needs updating (data in event.progress)
		TextEntered,    ///<    Text has been entered       (data in event.text)
		KeyDown,        ///<    Key has been pressed        (data in event.key)
		KeyUp           ///<    Key has been released       (data in event.key)
	};
	
	////////////////////////////////////////////////////////////
	///
	/// \brief  Struct containing data of a mouse button event
	///
	////////////////////////////////////////////////////////////
	struct MouseButtonEvent {
        Mouse::Button	button;		///<	Button associated with event
        int				x;			///<	x position of mouse
        int				y;			///<	y position of mouse
	};

	////////////////////////////////////////////////////////////
	///
	/// \brief	Struct containing data for a new mouse position event
	///
	////////////////////////////////////////////////////////////
	struct MouseMoveEvent {
		unsigned int x;     ///<    New x position of mouse cursor
		unsigned int y;     ///<    New y position of mouse cursor
	};

	////////////////////////////////////////////////////////////
	///
	/// \brief  Struct containing data for a text entered event
	///
	////////////////////////////////////////////////////////////
	struct TextEnteredEvent {
		uint32_t	character;      ///<    The character entered
	};

	////////////////////////////////////////////////////////////
	///
	/// \brief	Struct containing data of a key event
	///
	////////////////////////////////////////////////////////////
	struct KeyEvent {
        Keyboard::Key	key;		///<	Keyboard key that has been pressed/released
        bool			alt;		///<	Whether the alt key is down
        bool			control;	///<	Whether the control key is down
        bool			shift;		///<	Whether the shift key is down
        bool			system;		///<	Whether the system key is down
	};

public:
	EventType			type;       ///< The Event type that this event is representing

    ////////////////////////////////////////////////////////////
    ///
    ///	\brief	Union containing all possible events
    ///
    ////////////////////////////////////////////////////////////
	union {
		MouseButtonEvent		mouseButton;        ///<    Data about mouse button events
		MouseMoveEvent			mouseMove;          ///<    Data about mouse moved events
		TextEnteredEvent		text;               ///<    Data about text entered events
		KeyEvent				key;                ///<    Data about key events
	};
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_GUI_EVENT_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::GUIEvent
///	\ingroup GUI
///
///	Explanation of how this all works
///
///	\code
///	\endcode
///
////////////////////////////////////////////////////////////