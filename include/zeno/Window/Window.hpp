#ifndef INCLUDED_ZENO_WINDOW_WINDOW_HPP
#define INCLUDED_ZENO_WINDOW_WINDOW_HPP

#include <zeno/System/Event.hpp>
#include <zeno/System/Vector2.hpp>

#include <zeno/Window/ContextImplementation.hpp>
#include <zeno/Window/WindowHandle.hpp>
#include <zeno/Window/WindowImplementation.hpp>
#include <zeno/Window/WindowStyle.hpp>
#include <zeno/Window/VideoMode.hpp>

#include <vector>

namespace zeno {

//~ TODO Need context settings to set antialiasing/opengl version

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
	//	Default constructor
	//
	////////////////////////////////////////////////////////////
	Window(void);

	////////////////////////////////////////////////////////////
	//
	//	Constructor, effectively calls create with the given
	//	parameters
	//
	////////////////////////////////////////////////////////////
	Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

	////////////////////////////////////////////////////////////
	//
	//	Deconstructor
	//
	////////////////////////////////////////////////////////////
	~Window(void);


	////////////////////////////////////////////////////////////
	//
	//	Creates a window and context implementation
	//
	////////////////////////////////////////////////////////////
	void create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

	////////////////////////////////////////////////////////////
	//
	//	Closes the window, frees the resources associated with
	//	the window and the context
	//
	////////////////////////////////////////////////////////////
	void close(void);

	////////////////////////////////////////////////////////////
	//
	//	Returns whether the window is open and running
	//
	////////////////////////////////////////////////////////////
	bool isOpen(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Gets the position of the window
	//
	////////////////////////////////////////////////////////////
	Vector2i getPosition(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Sets the position of the window
	//
	////////////////////////////////////////////////////////////
	void setPosition(const Vector2i& _position);

	////////////////////////////////////////////////////////////
	//
	//	Gets the size of the window
	//
	////////////////////////////////////////////////////////////
	Vector2u getSize(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Sets the size of the window
	//
	////////////////////////////////////////////////////////////
	void setSize(const Vector2u& _size);

	////////////////////////////////////////////////////////////
	//
	//	Swaps the buffers, displaying the window
	//
	////////////////////////////////////////////////////////////
	void display(void);

	////////////////////////////////////////////////////////////
	//
	//	Returns whether or not there are any unprocessed events
	//	in the queue, if there are it modifies the given event
	//
	////////////////////////////////////////////////////////////
	bool pollEvent(Event& _event);
	////////////////////////////////////////////////////////////
	//
	//	Waits for an event to enter the queue, modifies the 
	//	given event
	//
	////////////////////////////////////////////////////////////
	void waitEvent(Event& _event);

	////////////////////////////////////////////////////////////
	//
	//	Sets whether repeated key input is being used
	//
	////////////////////////////////////////////////////////////
	void setRepeatedKeys(bool _repeat);

	////////////////////////////////////////////////////////////
	//
	//	Returns the system specific window handle
	//
	////////////////////////////////////////////////////////////
	WindowHandle getHandle(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Sets the title of the window
	//
	////////////////////////////////////////////////////////////
	void setTitle(const std::string& _title);

	////////////////////////////////////////////////////////////
	//
	//	Gets the current title of the window
	//
	////////////////////////////////////////////////////////////
	std::string getTitle(void) const;
	
	////////////////////////////////////////////////////////////
	//
	//	Enables/disables vsync with respect to the given value
	//
	////////////////////////////////////////////////////////////
	void setVerticalSync(bool _vsync = true);

	////////////////////////////////////////////////////////////
	//
	//	Returns whether or not vsync is enabled for the window
	//
	////////////////////////////////////////////////////////////
	bool getVerticalSyncState(void);
	

	////////////////////////////////////////////////////////////
	//
	//	Switches the window to fullscreen mode
	//
	////////////////////////////////////////////////////////////
	void switchToFullscreen(const VideoMode& _videoMode);

protected:
	////////////////////////////////////////////////////////////
	//
	//	The currently implemented video mode
	//
	////////////////////////////////////////////////////////////
	VideoMode					m_VideoMode;
	////////////////////////////////////////////////////////////
	//
	//	The title of the window
	//
	////////////////////////////////////////////////////////////
	std::string					m_Title;
	////////////////////////////////////////////////////////////
	//
	//	The style of the window
	//
	////////////////////////////////////////////////////////////
	uint32_t					m_WindowStyle;

	////////////////////////////////////////////////////////////
	//
	//	The system specific window implementation
	//
	////////////////////////////////////////////////////////////
	WindowImplementation		m_WindowImpl;
	////////////////////////////////////////////////////////////
	//
	//	The system specific context implementation
	//
	////////////////////////////////////////////////////////////
	ContextImplementation		m_ContextImpl;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_WINDOW_WINDOW_HPP