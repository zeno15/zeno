#ifndef INCLUDED_CONTEXT_WIN32_HPP
#define INCLUDED_CONTEXT_WIN32_HPP

#include <Windows.h>

//#include <WindowImplementation.hpp>

namespace zeno {

class ContextWin32
{
public:
	ContextWin32(void);

	~ContextWin32(void);

	bool create(HWND _handle);

private:
	//~ Rendering context
	HGLRC hrc;

	//~ Device context
	HDC hdc;

	//~ Window handle
	HWND hwnd;
};

}

#endif //~ INCLUDED_CONTEXT_WIN32_HPP