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

} //~ namespace zeno