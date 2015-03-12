#ifndef INCLUDED_WINDOW_STYLE_HPP
#define INCLUDED_WINDOW_STYLE_HPP

namespace zeno {
	
namespace WindowStyle {

////////////////////////////////////////////////////////////
//
//	Enumerated description of window style
//
////////////////////////////////////////////////////////////
enum 
{
	NoStyle = 0,
	Titlebar = 1 << 0,
	Resize = 1 << 1,
	Close = 1 << 2,
	Fullscreen = 1 << 3,

	Default = Titlebar | Resize | Close
};

} //~ namespace WindowStyle

} //~ namespace zeno

#endif //~ INCLUDED_WINDOW_STYLE_HPP
