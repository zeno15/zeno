#ifndef INCLUDED_WINDOW_IMPLEMENTATION_HPP
#define INCLUDED_WINDOW_IMPLEMENTATION_HPP


#ifdef _WIN32
	#include <Windows.h>
	#include <WindowImplementationWin32.hpp>
	typedef zeno::WindowImplementationWin32 WindowImplementation;
#endif
#ifdef __linux__
	#include <WindowImplementationUnix.hpp>
	typedef zeno::WindowImplementationUnix WindowImplementation;
#endif 

#endif //~ INCLUDED_WINDOW_IMPLEMENTATION_HPP