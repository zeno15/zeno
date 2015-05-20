#ifndef INCLUDED_ZENO_SYSTEM_EVENT_HPP
#define INCLUDED_ZENO_SYSTEM_EVENT_HPP

#include <zeno/System/Keyboard.hpp>
#include <zeno/System/Mouse.hpp>

#include <cstdint>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief	Class defining a system event and associated data
///
////////////////////////////////////////////////////////////
class Event
{
public:
	////////////////////////////////////////////////////////////
	///
	///	\brief	Enumeration of the different events that are
	///			handled
	///
	////////////////////////////////////////////////////////////
	enum EventType {
		WindowClosed,			///<	Window has requested to be close (no associated data)
		GainedFocus,			///<	Window has gained focus (no associated data)
		LostFocus,				///<	Window has lost focus (no associated data)
		WindowSizeChanged,		///<	Windows size has changed (data in event.size)
		KeyDown,				///<	Key has been pressed (data in event.key)
		KeyUp,					///<	Key has been released (data in event.key)
		TextEntered,			///<	Text has been entered (data in event.text)
		MouseWheelChanged,		///<	Mouse wheel has been scrolled (data in event.wheel)
		MouseButtonPressed,		///<	Mouse button has been pressed (data in event.mouseButton)
		MouseButtonReleased,	///<	Mouse button has been released (data in event.mouseButton)
		MouseMoved				///<	Mouse has been moved (data in event.position)
	};

	////////////////////////////////////////////////////////////
	///
	///	\brief	Enumeration of the different ways a window can
	///			be resized
	///
	////////////////////////////////////////////////////////////
	enum ResizedType {
		Maximized,				///<	Window has been maximised to fill the screen
		Minimized,				///<	Window has been minismised
		Restored				///<	Window has been restored to its previous size
	};

	////////////////////////////////////////////////////////////
	///
	///	\brief	Struct containing all data for an event about 
	///			key presses
	///
	////////////////////////////////////////////////////////////
	struct KeyEvent {
		Keyboard::Key	key;		///<	Keyboard key that has been pressed/released
		bool			alt;		///<	Whether the alt key is down
		bool			control;	///<	Whether the control key is down
		bool			shift;		///<	Whether the shift key is down
		bool			system;		///<	Whether the system key is down
	};

	////////////////////////////////////////////////////////////
	///
	///	\brief	Struct containing all data for an event about 
	///			window sizes
	///
	////////////////////////////////////////////////////////////
	struct SizeEvent {
		unsigned int	width;		///<	Window width associated with event
		unsigned int	height;		///<	Window height associated with event
		ResizedType		type;		///<	What type of window size event this is
	};

	////////////////////////////////////////////////////////////
	///
	///	\brief	Struct containing all data for an event about
	///			Mouse wheel changes
	///
	////////////////////////////////////////////////////////////
	struct MouseWheelEvent {
		int				delta;		///<	Mouse wheels offset
		int				x;			///<	x position of mouse
		int				y;			///<	y position of mouse
	};

	////////////////////////////////////////////////////////////
	///
	///	\brief	Struct representing all data for an event about
	///			Mouse button clicks
	///
	////////////////////////////////////////////////////////////
	struct MouseButtonEvent {
		Mouse::Button	button;		///<	Button associated with event
		int				x;			///<	x position of mouse
		int				y;			///<	y position of mouse
	};

	////////////////////////////////////////////////////////////
	///
	///	\brief	Struct representing all data for an event about
	///			positions
	///
	////////////////////////////////////////////////////////////
	struct PositionEvent {
		int				x;			///<	Associated x position
		int				y;			///<	Associated y position
	};

	////////////////////////////////////////////////////////////
	///
	///	\brief	Struct representing all data for an event about
	///			entering text
	///
	////////////////////////////////////////////////////////////
	struct TextEnteredEvent {
		uint32_t		character;	///<	Character that was entered
	};

public:
	EventType		type;			///< The Event type that this event is representing

	////////////////////////////////////////////////////////////
	///
	///	\brief	Union containing all possible events
	///
	////////////////////////////////////////////////////////////
	union {
		KeyEvent			key;			///<	Data about key events
		SizeEvent			size;			///<	Data about size events
		MouseWheelEvent		wheel;			///<	Data about mouse wheel events
		MouseButtonEvent	mouseButton;	///<	Data about mouse button events
		PositionEvent		position;		///<	Data about position events
		TextEnteredEvent	text;			///<	Data about text entered events
	};
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_EVENT_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Event
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code 
///	zeno::Event event;
///	event.type = zeno::Event::EventType::WindowClosed;
///	\endcode
///
////////////////////////////////////////////////////////////