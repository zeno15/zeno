#include <WindowImplementationWin32.hpp>

#include <GL/glew.h>
#include <GL/wglew.h>

namespace zeno {

WindowImplementationWin32::WindowImplementationWin32(void)
{

}

WindowImplementationWin32::~WindowImplementationWin32(void)
{

}


void WindowImplementationWin32::create()
{

}

void WindowImplementationWin32::close(void)
{

}

bool WindowImplementationWin32::isOpen(void) const
{
	return false;
}

Vector2i WindowImplementationWin32::getPosition(void) const
{
	return Vector2i();
}

void WindowImplementationWin32::setPosition(const Vector2i& _position)
{

}

Vector2u WindowImplementationWin32::getSize(void) const
{
	return Vector2u();
}

void WindowImplementationWin32::setSize(const Vector2u& _size)
{

}

void WindowImplementationWin32::display(void)
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

} //~ namespace zeno