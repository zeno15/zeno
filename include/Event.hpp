#ifndef INCLUDED_EVENT_HPP
#define INCLUDED_EVENT_HPP

#include <Keyboard.hpp>

namespace zeno {

class Event
{
public:
	enum EventType {
		WindowClosed,
		GainedFocus,
		LostFocus,
		WindowSizeChanged
	};

	enum ResizedType {
		Maximized,
		Minimized,
		Restored
	};

	struct KeyEvent {
		Keyboard::Key	key;
		bool			alt;
		bool			control;
		bool			shift;
		bool			system;
	};

	struct SizeEvent {
		unsigned int	width;
		unsigned int	height;
		ResizedType		type;
	};

public:
	EventType		type;

	union {
		KeyEvent	key;
		SizeEvent	size;
	};
};

} //~ namespace zeno

#endif //~ INCLUDED_EVENT_HPP