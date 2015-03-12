#ifndef INCLUDED_WINDOW_HANDLE_HPP
#define INCLUDED_WINDOW_HANDLE_HPP

#ifdef _WIN32
#include <Windows.h>
typedef HWND WindowHandle;
#endif
#ifdef __linux__
typedef unsigned long WindowHandle;
#endif

#endif //~ INCLUDED_WINDOW_HANDLE_HPP
