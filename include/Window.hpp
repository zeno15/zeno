#ifndef INCLUDED_WINDOW_HPP
#define INCLUDED_WINDOW_HPP

#include <WindowDisplay.hpp>

//~ http://xcb.freedesktop.org/opengl/
//~ https://gist.github.com/je-so/903479
//~ http://www.tldp.org/LDP/LG/issue78/tougher.html
//~ http://content.gpwiki.org/index.php/OpenGL:Tutorials:Setting_up_OpenGL_on_X11

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Currently Unix only window implementation
//
////////////////////////////////////////////////////////////
class Window
{
public:

	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	Window(void);
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	~Window(void);

	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	void create(unsigned int _width, unsigned int _height);
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	void display(void);

protected:
	WindowDisplay		m_Display;
	unsigned long int	m_Window;
};

} //~ namespace zeno

#endif //~ INCLUDED_WINDOW_HPP
