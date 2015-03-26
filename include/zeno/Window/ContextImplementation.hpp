#ifndef INCLUDED_ZENO_WINDOW_CONTEXT_IMPLEMENTATION_HPP
#define INCLUDED_ZENO_WINDOW_CONTEXT_IMPLEMENTATION_HPP

#ifdef _WIN32
	#include <zeno/Window/ContextWin32.hpp>
	typedef zeno::ContextWin32 ContextImplementation;
#endif
#ifdef __linux__
	#include <zeno/Window/ContextUnix.hpp>
	typedef zeno::ContextUnix ContextImplementation;
#endif 

#endif //~ INCLUDED_ZENO_WINDOW_CONTEXT_IMPLEMENTATION_HPP