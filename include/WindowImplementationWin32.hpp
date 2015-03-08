#ifndef INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP
#define INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP

#include <Windows.h>
#include <Vector2.hpp>
#include <VideoMode.hpp>
#include <Event.hpp>

#include <vector>


namespace zeno {

////////////////////////////////////////////////////////////
//
//	
//
////////////////////////////////////////////////////////////
class WindowImplementationWin32
{
public:
	WindowImplementationWin32(void);

	~WindowImplementationWin32(void);

	bool create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style);

	void close(void);

	bool isOpen(void) const;

	Vector2i getPosition(void) const;

	void setPosition(const Vector2i& _position);

	Vector2u getSize(void) const;

	void setSize(const Vector2u& _size);

	void display(void);

	HWND getHandle(void) const;

	bool pollEvent(Event& _event, bool _blocking = false);

	void pushEvent(const Event& _event);

	void setRepeatedKeys(bool _repeat);

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	void processEvent(UINT, WPARAM, LPARAM);

	void processWaitingEvents(void);

private:
	bool	running;
	bool	m_RepeatedKeys;

	HWND	m_Handle;

	std::vector<Event>			m_EventQueue;


	//~ Event specific internals
	Vector2u					m_Size;

	bool						m_ExitSizeChange;
};

} //~ namespace zeno

#endif //~ INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP