#include <zeno/System/Mouse.hpp>

#ifdef _WIN32
#include <zeno/System/InputImplementationWindows.hpp>
#else
#include <zeno/System/InputImplementationUnix.hpp>
#endif //~ _WIN32

#include <zeno/Window/Window.hpp>

namespace zeno {

bool Mouse::isButtonDown(Button _button)
{
	return InputImplementation::isMouseButtonDown(_button);
}

Vector2i Mouse::getPosition(void)
{
	return InputImplementation::getMousePosition();
}
Vector2i Mouse::getPosition(const Window& _window)
{
	return InputImplementation::getMousePosition(_window);
}

void Mouse::setPosition(const Vector2i& _position)
{
	InputImplementation::setMousePosition(_position);
}
void Mouse::setPosition(const Vector2i& _position, const Window& _window)
{
	InputImplementation::setMousePosition(_position, _window);
}

} //~ namespace zeno