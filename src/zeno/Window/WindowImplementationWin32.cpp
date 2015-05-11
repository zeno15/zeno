#include <zeno/Window/WindowImplementationWin32.hpp>

#include <zeno/System/InputImplementationWindows.hpp>

#include <iostream>

#define KEY_REPEAT_BIT 0x40000000 

namespace zeno {

WindowImplementationWin32::WindowImplementationWin32(void) :
m_Handle(NULL),
m_RepeatedKeys(false),
m_ExitSizeChange(true),
m_Title("UNTITLED")
{

}

WindowImplementationWin32::~WindowImplementationWin32(void)
{
	close();
}

bool WindowImplementationWin32::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style)
{
	m_Title = _title;
	LPCSTR title = m_Title.c_str();

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
	RECT rect;

	GetWindowRect(m_Handle, &rect);

	return Vector2i(rect.left, rect.top);
}

void WindowImplementationWin32::setPosition(const Vector2i& _position)
{
	if (SetWindowPos(m_Handle, m_Handle, _position.x, _position.y, -1, -1, SWP_NOSIZE | SWP_NOZORDER))
	{
		m_Position = _position;
	}
}

Vector2u WindowImplementationWin32::getSize(void) const
{
	RECT rect;

	GetClientRect(m_Handle, &rect);
	unsigned int width = rect.right - rect.left;
	unsigned int height = rect.bottom - rect.top;

	return Vector2u(width, height);
}

void WindowImplementationWin32::setSize(const Vector2u& _size)
{
	if (SetWindowPos(m_Handle, m_Handle, -1, -1, _size.x, _size.y, SWP_NOMOVE | SWP_NOZORDER))
	{
		m_Size = _size;
	}
}

void WindowImplementationWin32::display(void)
{
	if (m_Handle)
	{
		SwapBuffers(GetDC(m_Handle));
	}
}

WindowHandle WindowImplementationWin32::getHandle(void) const
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

		e.size.height = HIWORD(lParam);
		e.size.width = LOWORD(lParam);

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
		e.type = Event::EventType::KeyDown;
		e.key.key = InputImplementation::systemToZeno(wParam);
		e.key.shift =	(InputImplementation::isKeyDown(Keyboard::LShift)	|| InputImplementation::isKeyDown(Keyboard::RShift));
		e.key.alt =		(InputImplementation::isKeyDown(Keyboard::LAlt)		|| InputImplementation::isKeyDown(Keyboard::RAlt));
		e.key.control = (InputImplementation::isKeyDown(Keyboard::LControl) || InputImplementation::isKeyDown(Keyboard::RControl));
		e.key.system =	(InputImplementation::isKeyDown(Keyboard::LSystem)	|| InputImplementation::isKeyDown(Keyboard::RSystem));
		pushEvent(e);
		break;

	case (WM_KEYUP) :
		e.type = Event::EventType::KeyUp;
		e.key.key =		 InputImplementation::systemToZeno(wParam);
		e.key.shift =	(InputImplementation::isKeyDown(Keyboard::LShift)	|| InputImplementation::isKeyDown(Keyboard::RShift));
		e.key.alt =		(InputImplementation::isKeyDown(Keyboard::LAlt)		|| InputImplementation::isKeyDown(Keyboard::RAlt));
		e.key.control = (InputImplementation::isKeyDown(Keyboard::LControl) || InputImplementation::isKeyDown(Keyboard::RControl));
		e.key.system =	(InputImplementation::isKeyDown(Keyboard::LSystem)	|| InputImplementation::isKeyDown(Keyboard::RSystem));
		pushEvent(e);
		break;

	case (WM_CHAR):
	{
		uint32_t c = static_cast<uint32_t>(wParam);

		e.type = Event::EventType::TextEntered;
		e.text.character = c;
		pushEvent(e);
	}
		break;

	case (WM_MOUSEWHEEL):
		e.type = Event::EventType::MouseWheelChanged;
		e.wheel.delta = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		e.wheel.x = LOWORD(lParam);
		e.wheel.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_LBUTTONDOWN):
		e.type = Event::EventType::MouseButtonPressed;
		e.mouseButton.button = Mouse::Button::Left;
		e.mouseButton.x = LOWORD(lParam);
		e.mouseButton.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_LBUTTONUP):
		e.type = Event::EventType::MouseButtonReleased;
		e.mouseButton.button = Mouse::Button::Left;
		e.mouseButton.x = LOWORD(lParam);
		e.mouseButton.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_RBUTTONDOWN) :
		e.type = Event::EventType::MouseButtonPressed;
		e.mouseButton.button = Mouse::Button::Right;
		e.mouseButton.x = LOWORD(lParam);
		e.mouseButton.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_RBUTTONUP) :
		e.type = Event::EventType::MouseButtonReleased;
		e.mouseButton.button = Mouse::Button::Right;
		e.mouseButton.x = LOWORD(lParam);
		e.mouseButton.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_MBUTTONDOWN) :
		e.type = Event::EventType::MouseButtonPressed;
		e.mouseButton.button = Mouse::Button::Middle;
		e.mouseButton.x = LOWORD(lParam);
		e.mouseButton.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_MBUTTONUP) :
		e.type = Event::EventType::MouseButtonReleased;
		e.mouseButton.button = Mouse::Button::Middle;
		e.mouseButton.x = LOWORD(lParam);
		e.mouseButton.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_XBUTTONDOWN) :
		e.type = Event::EventType::MouseButtonPressed;
		e.mouseButton.button = (HIWORD(wParam) == XBUTTON1) ? Mouse::Button::Extra1 : Mouse::Button::Extra2;
		e.mouseButton.x = LOWORD(lParam);
		e.mouseButton.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_XBUTTONUP) :
		e.type = Event::EventType::MouseButtonReleased;
		e.mouseButton.button = (HIWORD(wParam) == XBUTTON1) ? Mouse::Button::Extra1 : Mouse::Button::Extra2;
		e.mouseButton.x = LOWORD(lParam);
		e.mouseButton.y = HIWORD(lParam);
		pushEvent(e);
		break;

	case (WM_MOUSEMOVE):
		e.type = Event::EventType::MouseMoved;
		e.position.x = LOWORD(lParam);
		e.position.y = HIWORD(lParam);
		pushEvent(e);
		break;

	default:
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

void WindowImplementationWin32::setTitle(const std::string& _title)
{
	if (SetWindowText(m_Handle, _title.c_str()))
	{
		m_Title = _title;
	}
}

std::string WindowImplementationWin32::getTitle(void) const
{
	return m_Title;
}

} //~ namespace zeno