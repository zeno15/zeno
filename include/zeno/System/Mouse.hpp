#ifndef INCLUDED_MOUSE_HPP
#define INCLUDED_MOUSE_HPP

#include <zeno/System/Vector2.hpp>

namespace zeno {

class Window;

////////////////////////////////////////////////////////////
//
//	Class to give simple real time access to mouse position
//	and state
//
////////////////////////////////////////////////////////////
class Mouse
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Enumeration of mouse buttons
	//
	////////////////////////////////////////////////////////////
	enum Button {	Left,
					Right,
					Middle,
					Extra1,
					Extra2,
					NUM_BUTTONS};

	////////////////////////////////////////////////////////////
	//
	//	Returns whether or not a given mouse button is down
	//
	////////////////////////////////////////////////////////////
	static bool isButtonDown(Button _button);

	////////////////////////////////////////////////////////////
	//
	//	Gets the position of the mouse cursor in desktop
	//	coordinates
	//
	////////////////////////////////////////////////////////////
	static Vector2i getPosition(void);
	////////////////////////////////////////////////////////////
	//
	//	Gets the position of the mouse cursor relative to the 
	//	given window
	//
	////////////////////////////////////////////////////////////
	static Vector2i getPosition(const Window& _relative);
	
	////////////////////////////////////////////////////////////
	//
	//	Sets the mouses position in desktop coordinates
	//
	////////////////////////////////////////////////////////////
	static void setPosition(const Vector2<int>& _position);

	////////////////////////////////////////////////////////////
	//
	//	Sets the mouses position relative to the given window
	//
	////////////////////////////////////////////////////////////
	static void setPosition(const Vector2<int>& _position, const Window& _window);
};
	
} //~ namespace zeno

#endif //~ INCLUDED_MOUSE_HPP