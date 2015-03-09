#include <Mouse.hpp>

#ifdef _WIN32
#include <InputImplementationWindows.hpp>
#else
#include <InputImplementationUnix.hpp>
#endif //~ _WIN32

#include <Window.hpp>

namespace zeno {

bool Mouse::isButtonDown(Button _button)
{
	return InputImplementation::isMouseButtonDown(_button);
}

Vector2i Mouse::getPosition(void)
{
	return InputImplementation::getMousePosition();
}
Vector2i Mouse::getPosition(const Window& _relative)
{
	return InputImplementation::getMousePosition(_relative);
}

void Mouse::setPosition(const Vector2<int>& _position)
{
	InputImplementation::setMousePosition(_position);
}
void Mouse::setPosition(const Vector2<int>& _position, const Window& _window)
{
	InputImplementation::setMousePosition(_position, _window);
}

} //~ namespace zeno