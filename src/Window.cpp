#include <Window.hpp>

#include <iostream>

namespace zeno {

Window::Window(void)
{
}

Window::~Window(void)
{
}


void Window::create(unsigned int _width, unsigned int _height)
{
	m_Display.createDisplay("");
	
	int x = 0;
	int y = 0;
	unsigned int border_width = 0;
	int depth = CopyFromParent;
	unsigned int windowClass = CopyFromParent;
	unsigned long int parent = DefaultRootWindow(m_Display());
	Visual *visual = CopyFromParent;
	unsigned long valuemask = 0;
	XSetWindowAttributes *attributes = 0;
	
	if (m_Display())
	{
		m_Window = XCreateWindow(m_Display(), parent, x, y, _width, _height, border_width, depth, windowClass, visual, valuemask, attributes);
	}
}

void Window::display(void)
{
	XMapWindow(m_Display(), m_Window);
	XFlush(m_Display());
}

} //~ namespace zeno


