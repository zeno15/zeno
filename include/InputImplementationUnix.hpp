#ifndef INCLUDED_INPUT_IMPLEMENTATION_UNIX_HPP
#define INCLUDED_INPUT_IMPLEMENTATION_UNIX_HPP

#include <Vector2.hpp>
#include <Keyboard.hpp>
#include <Mouse.hpp>

namespace zeno {
	
class Window;

} //~ namespace zeno

namespace zeno {
	
////////////////////////////////////////////////////////////
//
//	
//
////////////////////////////////////////////////////////////
class InputImplementation
{
public:
		
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	static bool isKeyPressed(Keyboard::Key _key);
	
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	static bool isMouseButtonPressed(Mouse::Button _button);
	
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	static Vector2<int> getMousePosition(void);
	
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	static Vector2<int> getMousePosition(const Window& _window);
	
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	static void setMousePosition(const Vector2<int>& _position);
	
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	static void setMousePosition(const Vector2<int>& _position, const Window& _window);
};
	
} //~ namespace zeno

#endif //~ INCLUDED_INPUT_IMPLEMENTATION_UNIX_HPP
