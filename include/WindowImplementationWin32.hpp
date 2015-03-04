#ifndef INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP
#define INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP

#include <Vector2.hpp>

#include <Windows.h>

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


	void create();

	void close(void);

	bool isOpen(void) const;

	Vector2i getPosition(void) const;

	void setPosition(const Vector2i& _position);

	Vector2u getSize(void) const;

	void setSize(const Vector2u& _size);

	void display(void);

private:
	//~ Rendering context
	HGLRC hrc;

	//~ Device context
	HDC hdc;

	//~ Window handle
	HWND hwnd;

};

} //~ namespace zeno

#endif //~ INCLUDED_WINDOW_IMPLEMENTATION_WIN32_HPP