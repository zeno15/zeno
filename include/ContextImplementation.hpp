#ifndef INCLUDED_CONTEXT_IMPLEMENTATION_HPP
#define INCLUDED_CONTEXT_IMPLEMENTATION_HPP

#ifdef _WIN32
	#include <ContextWin32.hpp>
	typedef zeno::ContextWin32 ContextImplementation;
#endif
#ifdef __linux__
	#include <ContextUnix.hpp>
	typedef zeno::ContextUnix ContextImplementation;
#endif 

#endif //~ INCLUDED_CONTEXT_IMPLEMENTATION_HPP