#include <Window.hpp>

namespace zeno {

Window::Window(void) :
m_VideoMode(),
m_Title(std::string()),
m_WindowStyle(WindowStyle::Default)
{
}

Window::Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/) :
m_VideoMode(_videoMode),
m_Title(_title),
m_WindowStyle(_style)
{
	create(m_VideoMode, m_Title, m_WindowStyle);
}

Window::~Window(void)
{
	close();
}


void Window::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/)
{
	m_WindowImpl.create(_videoMode, _title, _style);
	m_ContextImpl.create(m_WindowImpl.getHandle());
}

void Window::close(void)
{
	m_WindowImpl.close();
}

bool Window::isOpen(void) const
{
	return m_WindowImpl.isOpen();
}

Vector2i Window::getPosition(void) const
{
	return m_WindowImpl.getPosition();
}

void Window::setPosition(const Vector2i& _position)
{
	m_WindowImpl.setPosition(_position);
}

Vector2u Window::getSize(void) const
{
	return m_WindowImpl.getSize();
}

void Window::setSize(const Vector2u& _size)
{
	m_WindowImpl.setSize(_size);
}

void Window::display(void)
{
	m_WindowImpl.display();
}

} //~ namespace zeno