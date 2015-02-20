#include <WindowDisplay.hpp>


namespace zeno {

WindowDisplay::WindowDisplay(void) :
m_Display(0)
{
}
WindowDisplay::WindowDisplay(const std::string& _name)
{
	createDisplay(_name);
}

WindowDisplay::~WindowDisplay(void)
{
	if (m_Display)
	{
		XCloseDisplay(m_Display);
		m_Display = 0;
	}
}


bool WindowDisplay::createDisplay(const std::string& _name)
{
	m_Display = XOpenDisplay(_name.c_str());
}

} //~ namespace zeno
