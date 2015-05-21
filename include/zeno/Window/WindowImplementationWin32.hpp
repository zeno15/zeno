#ifndef INCLUDED_ZENO_WINDOW_WINDOW_IMPLEMENTATION_WIN32_HPP
#define INCLUDED_ZENO_WINDOW_WINDOW_IMPLEMENTATION_WIN32_HPP

#include <zeno/System/Event.hpp>
#include <zeno/System/Vector2.hpp>
#include <zeno/Window/VideoMode.hpp>
#include <zeno/Window/WindowHandle.hpp>

#include <vector>
#ifndef NOMINMAX
#define NOMINMAX
#endif //~ NOMINMAX
#include <Windows.h>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Windows specific window implementation
//
////////////////////////////////////////////////////////////
class WindowImplementationWin32
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Constructor
	//
	////////////////////////////////////////////////////////////
	WindowImplementationWin32(void);

	////////////////////////////////////////////////////////////
	//
	//	Deconstructor
	//
	////////////////////////////////////////////////////////////
	~WindowImplementationWin32(void);


	////////////////////////////////////////////////////////////
	//
	//	Creates the window with the given parameters
	//
	////////////////////////////////////////////////////////////
	bool create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style);

	////////////////////////////////////////////////////////////
	//
	//	Closes the window and frees the resources associated
	//
	////////////////////////////////////////////////////////////
	void close(void);

	////////////////////////////////////////////////////////////
	//
	//	Returns whether the window is open or not
	//
	////////////////////////////////////////////////////////////
	bool isOpen(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Gets the position of the window in desktop coordinates
	//
	////////////////////////////////////////////////////////////
	Vector2i getPosition(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Sets the position of the window in desktop coordinates
	//
	////////////////////////////////////////////////////////////
	void setPosition(const Vector2i& _position);

	////////////////////////////////////////////////////////////
	//
	//	Returns the size of the window
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
	//	Swaps the buffers, displaying the windows contents
	//
	////////////////////////////////////////////////////////////
	void display(void);

	////////////////////////////////////////////////////////////
	//
	//	Gets the system handle to the window
	//
	////////////////////////////////////////////////////////////
	WindowHandle getHandle(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Returns whether or not there is an event in the queue,
	//	if so the event parameter will be populated
	//
	////////////////////////////////////////////////////////////
	bool pollEvent(Event& _event, bool _blocking = false);

	////////////////////////////////////////////////////////////
	//
	//	Pushes an event onto the queue
	//
	////////////////////////////////////////////////////////////
	void pushEvent(const Event& _event);

	////////////////////////////////////////////////////////////
	//
	//	Sets whether repeated key input is used
	//
	////////////////////////////////////////////////////////////
	void setRepeatedKeys(bool _repeat);

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
	//	Switches the window to fullscreen mode
	//
	////////////////////////////////////////////////////////////
	void switchToFullscreen(const VideoMode& _videoMode);

private:
	////////////////////////////////////////////////////////////
	//
	//	Callback function that is used as the system event handler
	//
	////////////////////////////////////////////////////////////
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	////////////////////////////////////////////////////////////
	//
	//	Custom function used to handle all system events
	//
	////////////////////////////////////////////////////////////
	void processEvent(UINT, WPARAM, LPARAM);

	////////////////////////////////////////////////////////////
	//
	//	Checks for incoming events
	//
	////////////////////////////////////////////////////////////
	void processWaitingEvents(void);

private:
	////////////////////////////////////////////////////////////
	//
	//	Describes whether the window is open and running
	//
	////////////////////////////////////////////////////////////
	bool	running;
	////////////////////////////////////////////////////////////
	//
	//	Describes whether repeated key input is being used
	//
	////////////////////////////////////////////////////////////
	bool	m_RepeatedKeys;

	////////////////////////////////////////////////////////////
	//
	//	System handle
	//
	////////////////////////////////////////////////////////////
	HWND	m_Handle;

	////////////////////////////////////////////////////////////
	//
	//	Queue of unprocessed events
	//
	////////////////////////////////////////////////////////////
	std::vector<Event>			m_EventQueue;

	////////////////////////////////////////////////////////////
	//
	//	Position of the window
	//
	////////////////////////////////////////////////////////////
	Vector2i					m_Position;
	////////////////////////////////////////////////////////////
	//
	//	Size of the window
	//
	////////////////////////////////////////////////////////////
	Vector2i					m_Size;

	////////////////////////////////////////////////////////////
	//
	//	Allows window resize events to be thrown only when 
	//	resizing is finished
	//
	////////////////////////////////////////////////////////////
	bool						m_ExitSizeChange;

	////////////////////////////////////////////////////////////
	//
	//	Title of the window
	//
	////////////////////////////////////////////////////////////
	std::string					m_Title;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_WINDOW_WINDOW_IMPLEMENTATION_WIN32_HPP