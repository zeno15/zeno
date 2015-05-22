#include <zeno/Window/ContextUnix.hpp>

#include <GL/glx.h>
#include <GL/glu.h>

namespace zeno {
	
ContextUnix::ContextUnix(void)
{
}

ContextUnix::~ContextUnix(void)
{
}

bool ContextUnix::create(::Display *displayHandle, WindowHandle _handle)
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	
	XVisualInfo *vi = glXChooseVisual(displayHandle, 0, att);
	
	glXMakeCurrent(displayHandle, _handle, glXCreateContext(displayHandle, vi, NULL, GL_TRUE));
	return true;
}

void ContextUnix::setVerticalSync(bool _vsync /*= true*/)
{
	//~ TODO implement
}

bool ContextUnix::getVerticalSyncState(void)
{
	//~ TODO implement
	return false;
}
	
} //~ namespace zeno
