#ifndef INCLUDED_WINDOW_HPP
#define INCLUDED_WINDOW_HPP

#include <ContextImplementation.hpp>
#include <WindowHandle.hpp>
#include <WindowImplementation.hpp>
#include <WindowStyle.hpp>
#include <Vector2.hpp>
#include <VideoMode.hpp>
#include <Event.hpp>

#include <vector>

namespace zeno {

//~ Need context settings to set antialiasing/opengl version



////////////////////////////////////////////////////////////
//
//	Base class for all platform specific windows to
//	inherate from.
//
////////////////////////////////////////////////////////////
class Window
{
public:
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	Window(void);

	Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

	~Window(void);


	void create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

	void close(void);

	bool isOpen(void) const;

	Vector2i getPosition(void) const;

	void setPosition(const Vector2i& _position);

	Vector2u getSize(void) const;

	void setSize(const Vector2u& _size);

	void display(void);

	bool pollEvent(Event& _event);
	void waitEvent(Event& _event);

	void setRepeatedKeys(bool _repeat);

	WindowHandle getHandle(void) const;

protected:
	VideoMode					m_VideoMode;
	std::string					m_Title;
	uint32_t					m_WindowStyle;

	WindowImplementation		m_WindowImpl;
	ContextImplementation		m_ContextImpl;
};

} //~ namespace zeno

#endif //~ INCLUDED_WINDOW_HPP