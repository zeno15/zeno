#include <ContextWin32.hpp>

#include <iostream>

#include <GL/glew.h>
#include <GL/wglew.h>

namespace zeno {

ContextWin32::ContextWin32(void)
{
}

ContextWin32::~ContextWin32(void)
{
	//~ Check if the window has been created etc before
	wglMakeCurrent(hdc, 0);
	wglDeleteContext(hrc);

	ReleaseDC(hwnd, hdc);
}


bool ContextWin32::create(HWND _handle)
{
	hwnd = _handle;
	ShowWindow(hwnd, SW_HIDE);
	hdc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(hdc, &pfd);

	if (nPixelFormat == 0)
	{
		return false;
	}

	bool bResult = SetPixelFormat(hdc, nPixelFormat, &pfd) != 0;

	if (!bResult)
	{
		return false;
	}

	HGLRC tempOpenGLContext = wglCreateContext(hdc);
	wglMakeCurrent(hdc, tempOpenGLContext);

	if (glewInit() != GLEW_OK)
	{
		return false;
	}
	

	int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 4,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		hrc = wglCreateContextAttribsARB(hdc, NULL, attributes);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempOpenGLContext);
		wglMakeCurrent(hdc, hrc);
	}
	else
	{
		hrc = tempOpenGLContext;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return true;
}

}