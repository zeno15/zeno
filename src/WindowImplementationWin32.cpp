#include <WindowImplementationWin32.hpp>

#include <iostream>

namespace zeno {

WindowImplementationWin32::WindowImplementationWin32(void)
{

}

WindowImplementationWin32::~WindowImplementationWin32(void)
{

}


bool WindowImplementationWin32::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style)
{
	LPCSTR title = _title.c_str();

	WNDCLASS windowClass;
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC)WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = title;

	if (!RegisterClass(&windowClass))
	{
		return false;
	}

	m_Handle = CreateWindowEx(dwExStyle, title, title, WS_OVERLAPPEDWINDOW, 0, 0, _videoMode.width, _videoMode.height, NULL, NULL, hInstance, NULL);

	return true;
}

void WindowImplementationWin32::close(void)
{
	running = false;
}

bool WindowImplementationWin32::isOpen(void) const
{
	return running;
}

Vector2i WindowImplementationWin32::getPosition(void) const
{
	return Vector2i();
}

void WindowImplementationWin32::setPosition(const Vector2i& _position)
{

}

Vector2u WindowImplementationWin32::getSize(void) const
{
	return Vector2u();
}

void WindowImplementationWin32::setSize(const Vector2u& _size)
{

}

void WindowImplementationWin32::display(void)
{
	MSG msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			running = false;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{
		SwapBuffers(GetDC(m_Handle));
	}

}

HWND WindowImplementationWin32::getHandle(void)
{
	return m_Handle;
}

LRESULT CALLBACK WindowImplementationWin32::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::string output;
	char c;
	switch (message)
	{
	case (WM_SIZE) :
		//~ Resize the window etc, glViewPort(). . . .
		break;
	case (WM_KEYDOWN) :
		//~ Deal with keydown events. . . 
		break;
	case (WM_DESTROY) :
		std::cout << "Close Window." << std::endl;
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void WindowImplementationWin32::eventHandle(void)
{
}

} //~ namespace zeno