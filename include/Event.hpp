#ifndef INCLUDED_EVENT_HPP
#define INCLUDED_EVENT_HPP

#include <Keyboard.hpp>
#include <Mouse.hpp>

namespace zeno {

class Event
{
public:
	enum EventType {
		WindowClosed,
		GainedFocus,
		LostFocus,
		WindowSizeChanged,
		KeyDown,
		KeyUp,
		TextEntered,
		MouseWheelChanged,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseEnterWindow,
		MouseLeaveWindow
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

	struct MouseWheelEvent {
		int				delta;
		int				x;
		int				y;
	};

	struct MouseButtonEvent {
		Mouse::Button	button;
		int				x;
		int				y;
	};

	struct PositionEvent {
		int				x;
		int				y;
	};

public:
	EventType		type;

	union {
		KeyEvent			key;
		SizeEvent			size;
		MouseWheelEvent		wheel;
		MouseButtonEvent	mouseButton;
		PositionEvent		position;
	};
};

} //~ namespace zeno

#endif //~ INCLUDED_EVENT_HPP