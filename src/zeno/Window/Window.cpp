#include <zeno/Window/Window.hpp>

namespace zeno {

Window::Window(void) :
m_VideoMode(),
m_Title(std::string()),
m_WindowStyle(WindowStyle::Default)
{
}

Window::Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/)
{
	create(_videoMode, _title, _style);
}

Window::~Window(void)
{
	close();
}


void Window::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/)
{
	m_VideoMode = _videoMode;
	m_Title = _title;
	m_WindowStyle = _style;

	m_WindowImpl.create(_videoMode, _title, _style);
	
	#ifdef _WIN32
	m_ContextImpl.create(m_WindowImpl.getHandle());
	#endif
	#ifdef __linux__
	m_ContextImpl.create(m_WindowImpl.getDisplayHandle(), m_WindowImpl.getHandle());
	#endif 
	setVerticalSync(true);
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

bool Window::pollEvent(Event& _event)
{
	return m_WindowImpl.pollEvent(_event, false);
}
void Window::waitEvent(Event& _event)
{
	m_WindowImpl.pollEvent(_event, true);
}

void Window::setRepeatedKeys(bool _repeat)
{
	m_WindowImpl.setRepeatedKeys(_repeat);
}

WindowHandle Window::getHandle(void) const
{
	return m_WindowImpl.getHandle();
}

void Window::setTitle(const std::string& _title)
{
	m_WindowImpl.setTitle(_title);
}

std::string Window::getTitle(void) const
{
	return m_WindowImpl.getTitle();
}

void Window::setVerticalSync(bool _vsync /*= true*/)
{
	m_ContextImpl.setVerticalSync(_vsync);
}

bool Window::getVerticalSyncState(void)
{
	return m_ContextImpl.getVerticalSyncState();
}

} //~ namespace zeno
