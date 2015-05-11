#ifndef INCLUDED_ZENO_WINDOW_WINDOW_STYLE_HPP
#define INCLUDED_ZENO_WINDOW_WINDOW_STYLE_HPP

namespace zeno {
	
namespace WindowStyle {

////////////////////////////////////////////////////////////
//
//	Enumerated description of window style
//	Note if using fullscreen with a resolution not matching
//	the monitor, the window behaves unexpectedly
//
////////////////////////////////////////////////////////////
enum 
{
	NoStyle		= 0,
	Titlebar	= 1 << 0,
	Resize		= 1 << 1,
	Close		= 1 << 2,
	Fullscreen	= 1 << 3,

	Default		= Titlebar | Resize | Close
};

} //~ namespace WindowStyle

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_WINDOW_WINDOW_STYLE_HPP
