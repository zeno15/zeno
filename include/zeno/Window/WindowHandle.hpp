#ifndef INCLUDED_ZENO_WINDOW_WINDOW_HANDLE_HPP
#define INCLUDED_ZENO_WINDOW_WINDOW_HANDLE_HPP

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif //~ NOMINMAX
#include <Windows.h>
typedef HWND WindowHandle;
#endif
#ifdef __linux__
typedef unsigned long WindowHandle;
#endif

#endif //~ INCLUDED_ZENO_WINDOW_WINDOW_HANDLE_HPP
