#ifndef INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP
#define INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP


#include <Windows.h>

#include <Vector2.hpp>
#include <VideoMode.hpp>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	
//
////////////////////////////////////////////////////////////
class WindowImplementationWin32
{
public:
	bool create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style);

	void close(void);

	bool isOpen(void) const;

	Vector2i getPosition(void) const;

	void setPosition(const Vector2i& _position);

	Vector2u getSize(void) const;

	void setSize(const Vector2u& _size);

	void display(void);

	HWND getHandle(void);

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	void eventHandle(void);

private:
	bool	running;

	HWND	m_Handle;
};

} //~ namespace zeno

#endif //~ INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP