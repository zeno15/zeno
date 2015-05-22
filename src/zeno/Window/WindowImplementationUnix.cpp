#include <zeno/Window/WindowImplementationUnix.hpp>

#include <zeno/Window/VideoMode.hpp>
#include <GL/glx.h>
#include <GL/glu.h>

namespace zeno {
	
WindowImplementationUnix::WindowImplementationUnix(void) :
m_Handle(NULL)
{
}

WindowImplementationUnix::~WindowImplementationUnix(void)
{
	if (m_Handle != NULL)
	{
		XCloseDisplay(m_Handle);
	}
}


bool WindowImplementationUnix::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style)
{
	m_Handle = XOpenDisplay(NULL);
	if (m_Handle == NULL)
	{
		return false;
	}
	
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	
	XVisualInfo *vi = glXChooseVisual(m_Handle, 0, att);
	
	Colormap cmap = XCreateColormap(m_Handle, DefaultRootWindow(m_Handle), vi->visual, AllocNone);
	
	XSetWindowAttributes    swa;
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
	
	m_Window = XCreateWindow(		m_Handle, 
									DefaultRootWindow(m_Handle),
									0,
									0,
									_videoMode.width,
									_videoMode.height,
									0,
									vi->depth,
									InputOutput,
									vi->visual,
									CWColormap | CWEventMask,
									&swa);
	
	
	XMapWindow(m_Handle, m_Window);
	XStoreName(m_Handle, m_Window, _title.c_str());
	
	return true;
}

void WindowImplementationUnix::close(void)
{
}

bool WindowImplementationUnix::isOpen(void) const
{
	return m_Running;
}

Vector2i WindowImplementationUnix::getPosition(void) const
{
	return m_Position;
}

void WindowImplementationUnix::setPosition(const Vector2i& _position)
{
}

Vector2u WindowImplementationUnix::getSize(void) const
{
	return m_Size;
}

void WindowImplementationUnix::setSize(const Vector2u& _size)
{
}

void WindowImplementationUnix::display(void)
{
	XFlush(m_Handle);
	glXSwapBuffers(m_Handle, m_Window);
}

WindowHandle WindowImplementationUnix::getHandle(void) const
{
	return m_Window;
}

::Display *WindowImplementationUnix::getDisplayHandle(void) const
{
	return m_Handle;
}

bool WindowImplementationUnix::pollEvent(Event& _event, bool _blocking /*= false*/)
{
	return false;
}

void WindowImplementationUnix::pushEvent(const Event& _event)
{
}

void WindowImplementationUnix::setRepeatedKeys(bool _repeat)
{
}

void WindowImplementationUnix::setTitle(const std::string& _title)
{
}

std::string WindowImplementationUnix::getTitle(void) const
{
	return m_Title;
}

void WindowImplementationUnix::processEvent()
{
}

void WindowImplementationUnix::processWaitingEvents(void)
{
}

void WindowImplementationUnix::switchToFullscreen(const VideoMode& _videoMode)
{
    //~ TODO implement
}

} //~ namespace zeno
