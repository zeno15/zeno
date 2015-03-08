#ifndef INCLUDED_MOUSE_HPP
#define INCLUDED_MOUSE_HPP

#include <Vector2.hpp>

namespace zeno {

class Window;

class Mouse
{
public:
	enum Button {	Left,
					Right,
					Middle,
					Extra1,
					Extra2,
					NUM_BUTTONS};

	static bool isButtonDown(Button _button);

	static Vector2i getPosition(void);
	static Vector2i getPosition(const Window& _relative);
};
	
} //~ namespace zeno

#endif //~ INCLUDED_MOUSE_HPP
