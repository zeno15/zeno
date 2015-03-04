#ifndef INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP
#define INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP

#include <Windows.h>

#include <Vector2.hpp>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	
//
////////////////////////////////////////////////////////////
class WindowImplementationWin32
{
public:
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	WindowImplementationWin32(void);

	~WindowImplementationWin32(void);


	void create(void);

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
	bool running;

	HWND	m_Handle;
};

} //~ namespace zeno

#endif //~ INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP