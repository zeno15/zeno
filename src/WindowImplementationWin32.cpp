#include <WindowImplementationWin32.hpp>

#include <iostream>

#define KEY_REPEAT_BIT 0x40000000 

namespace zeno {

WindowImplementationWin32::WindowImplementationWin32(void) :
m_Handle(NULL),
m_RepeatedKeys(false),
m_ExitSizeChange(true)
{

}

WindowImplementationWin32::~WindowImplementationWin32(void)
{
	close();
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

	SetWindowLongPtr(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	return true;
}

void WindowImplementationWin32::close(void)
{
	running = false;
	DestroyWindow(m_Handle);
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
	if (m_Handle)
	{
		SwapBuffers(GetDC(m_Handle));
	}
}

HWND WindowImplementationWin32::getHandle(void)
{
	return m_Handle;
}

bool WindowImplementationWin32::pollEvent(Event& _event, bool _blocking /*= false*/)
{
	if (m_EventQueue.empty())
	{
		processWaitingEvents();

		if (_blocking)
		{
			while (m_EventQueue.empty())
			{
				Sleep(10);
				processWaitingEvents();
			}
		}
	}

	if (!m_EventQueue.empty())
	{
		_event = m_EventQueue.front();

		m_EventQueue.erase(m_EventQueue.begin());

		return true;
	}

	return false;
}

void WindowImplementationWin32::pushEvent(const Event& _event)
{
	m_EventQueue.push_back(_event);
}

LRESULT CALLBACK WindowImplementationWin32::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WindowImplementationWin32 *thisWindow = reinterpret_cast<WindowImplementationWin32 *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	if (thisWindow)
	{
		thisWindow->processEvent(message, wParam, lParam);

		if (message == WM_CLOSE)
		{
			//~ Handle closing the window how the app chooses
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void WindowImplementationWin32::processEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_Handle == NULL)
	{
		return;
	}

	Event e;

	switch (message)
	{
	case (WM_CLOSE) :
		e.type = Event::EventType::WindowClosed;
		pushEvent(e);
		break;

	case (WM_EXITSIZEMOVE) :
		m_ExitSizeChange = true;
		break;

	case (WM_SIZE) :
		//~ Only want the last size change event
		if (!m_ExitSizeChange)
		{
			return;
		}
		m_ExitSizeChange = false;

		e.type = Event::EventType::WindowSizeChanged;

		m_Size = Vector2u(HIWORD(lParam), LOWORD(lParam));

		e.size.height = LOWORD(lParam);
		e.size.width = HIWORD(lParam);

		if (wParam == SIZE_MAXIMIZED)
		{
			e.size.type = Event::ResizedType::Maximized;
		}
		else if (wParam == SIZE_MINIMIZED)
		{
			e.size.type = Event::ResizedType::Minimized;
		}
		else
		{
			e.size.type = Event::ResizedType::Restored;
		}
		pushEvent(e);
		break;

	case (WM_SETFOCUS) :
		e.type = Event::EventType::GainedFocus;
		pushEvent(e);
		break;

	case (WM_KILLFOCUS) :
		e.type = Event::EventType::LostFocus;
		pushEvent(e);
		break;

	case (WM_KEYDOWN):
		if ((lParam & KEY_REPEAT_BIT) && !m_RepeatedKeys)
		{
			break;
		}
		break;

	case (WM_KEYUP) :
		std::cout << "Key up: " << wParam << std::endl;
		break;
	}
}

void WindowImplementationWin32::processWaitingEvents(void)
{
	MSG msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void WindowImplementationWin32::setRepeatedKeys(bool _repeat)
{
	m_RepeatedKeys = _repeat;
}

} //~ namespace zeno