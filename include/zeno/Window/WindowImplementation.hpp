#ifndef INCLUDED_ZENO_WINDOW_WINDOW_IMPLEMENTATION_HPP
#define INCLUDED_ZENO_WINDOW_WINDOW_IMPLEMENTATION_HPP

#ifdef _WIN32
#include <zeno/Window/WindowImplementationWin32.hpp>
typedef zeno::WindowImplementationWin32 WindowImplementation;
#endif
#ifdef __linux__
#include <zeno/Window/WindowImplementationUnix.hpp>
typedef zeno::WindowImplementationUnix WindowImplementation;
#endif

#endif //~ INCLUDED_ZENO_WINDOW_WINDOW_IMPLEMENTATION_HPP