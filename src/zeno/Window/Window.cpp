#include <zeno/Window/Window.hpp>

#include <iostream>

#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace zeno {

Window::GLFWState::GLFWState(void)
{
    std::cout << "Initialising GLFW" << std::endl;
    glfwSetErrorCallback(GLFWState::glfwErrorCallback);
    glfwInit();
}

Window::GLFWState::~GLFWState(void)
{
    std::cout << "Terminating GLFW" << std::endl;
    glfwTerminate();
}


void Window::GLFWState::glfwErrorCallback(int _error, const char *_description)
{
    std::cout << "GFLW error (" << _error << "): " << _description << std::endl;
}

void Window::GLFWState::glfwCloseCallback(GLFWwindow *_window)
{
    Window* window = static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window));

    zeno::Event event;
    event.type = zeno::Event::WindowClosed;

    window->m_Events.push_back(event);

    glfwSetWindowShouldClose(_window, GL_FALSE);
}

void Window::GLFWState::glfwKeyCallback(GLFWwindow *_window, int _key, int _scanCode, int _action, int _modifier)
{
    zeno::Event event;
    switch (_action)
    {
        case (GLFW_PRESS):
            event.type = zeno::Event::KeyDown;
            break;
        case (GLFW_RELEASE):
            event.type = zeno::Event::KeyUp;
            break;
        case (GLFW_REPEAT):
            event.type = zeno::Event::KeyRepeat;
            break;
        default:
            return;
    }

    event.key.key = static_cast<zeno::Keyboard::Key>(_key);
    event.key.shift = (_modifier & GLFW_MOD_SHIFT) == 1;
    event.key.alt = (_modifier & GLFW_MOD_ALT) == 1;
    event.key.control = (_modifier & GLFW_MOD_CONTROL) == 1;
    event.key.system = (_modifier & GLFW_MOD_SUPER) == 1;

    static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))->m_Events.push_back(event);
}
void Window::GLFWState::glfwCharacterCallback(GLFWwindow *_window, unsigned int _character)
{
    zeno::Event event;
    event.type = zeno::Event::TextEntered;

    event.text.character = static_cast<char>(_character);

    static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))->m_Events.push_back(event);
}
void Window::GLFWState::glfwMousePositionCallback(GLFWwindow *_window, double _xPos, double _yPos)
{
    zeno::Event event;
    event.type = zeno::Event::MouseMoved;

    event.position.x = static_cast<int>(_xPos);
    event.position.y = static_cast<int>(_yPos);

    static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))->m_Events.push_back(event);
}
void Window::GLFWState::glfwMouseEnterLeaveCallback(GLFWwindow *_window, int _entered)
{
    zeno::Event event;

    event.type = zeno::Event::MouseEntered;

    event.enter.entered = (_entered == 1);

    static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))->m_Events.push_back(event);
}
void Window::GLFWState::glfwMouseButtonCallback(GLFWwindow *_window, int _button, int _action, int _mods)
{
    zeno::Event event;

    switch (_action)
    {
        case (GLFW_PRESS):
            event.type = zeno::Event::MouseButtonPressed;
            break;
        case (GLFW_RELEASE):
            event.type = zeno::Event::MouseButtonReleased;
            break;
        default:
            return;
    }

    event.mouseButton.button = static_cast<zeno::Mouse::Button>(_button);

    event.mouseButton.x = zeno::Mouse::getPosition(*static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))).x;
    event.mouseButton.y = zeno::Mouse::getPosition(*static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))).y;

    static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))->m_Events.push_back(event);
}
void Window::GLFWState::glfwScrollCallback(GLFWwindow *_window, double _xOffset, double _yOffset)
{
    zeno::Event event;

    event.type = zeno::Event::MouseWheelChanged;

    event.wheel.delta = static_cast<int>(_yOffset);

    event.wheel.x = zeno::Mouse::getPosition(*static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))).x;
    event.wheel.y = zeno::Mouse::getPosition(*static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))).y;

    static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))->m_Events.push_back(event);
}
void Window::GLFWState::glfwWindowSizeCallback(GLFWwindow *_window, int _width, int _height)
{
    zeno::Event event;

    event.type = zeno::Event::WindowSizeChanged;

    event.size.type = zeno::Event::ResizedType::Restored;

    event.size.width = static_cast<unsigned int>(_width);
    event.size.height = static_cast<unsigned int>(_height);

    static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))->m_Events.push_back(event);
}
void Window::GLFWState::glfwWindowIconfifyCallback(GLFWwindow *_window, int _iconified)
{
    zeno::Event event;

    event.type = zeno::Event::WindowSizeChanged;

    event.size.type = (_iconified ? zeno::Event::ResizedType::Minimized : zeno::Event::ResizedType::Restored);

    static_cast<zeno::Window *>(glfwGetWindowUserPointer(_window))->m_Events.push_back(event);
}
void Window::GLFWState::glfwWindowPositionCallback(GLFWwindow *_window, int _x, int _y)
{

}

Window::Window(void) :
m_VideoMode(),
m_Title(""),
m_WindowStyle(WindowStyle::Default),
m_IsOpen(false)
{
    glfwInit();
}

Window::Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/)
{
    glfwInit();
	create(_videoMode, _title, _style);
}

Window::~Window(void)
{
	close();
    glfwTerminate();
}


bool Window::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/)
{
	m_VideoMode = _videoMode;
	m_Title = _title;
	m_WindowStyle = _style;

    GLFWmonitor *monitor = nullptr;
    GLFWwindow *share = nullptr;

    if (_style & WindowStyle::Fullscreen)
    {
        monitor = glfwGetPrimaryMonitor();
    }

    glfwWindowHint(GLFW_RESIZABLE, _style & WindowStyle::Resize);
    glfwWindowHint(GLFW_DECORATED, _style & WindowStyle::Titlebar);

    m_Window = glfwCreateWindow(_videoMode.width, _videoMode.height, _title.c_str(), monitor, share);
    if (m_Window == NULL)
    {
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glewInit failed." << std::endl;
        return false;
    }


    glfwSetWindowUserPointer(m_Window, this);
    glfwSetWindowCloseCallback(m_Window, GLFWState::glfwCloseCallback);
    glfwSetKeyCallback(m_Window, GLFWState::glfwKeyCallback);
    glfwSetCharCallback(m_Window, GLFWState::glfwCharacterCallback);
    glfwSetCursorPosCallback(m_Window, GLFWState::glfwMousePositionCallback);
    glfwSetCursorEnterCallback(m_Window, GLFWState::glfwMouseEnterLeaveCallback);
    glfwSetMouseButtonCallback(m_Window, GLFWState::glfwMouseButtonCallback);
    glfwSetScrollCallback(m_Window, GLFWState::glfwScrollCallback);
    glfwSetWindowSizeCallback(m_Window, GLFWState::glfwWindowSizeCallback);
    glfwSetWindowPosCallback(m_Window, GLFWState::glfwWindowPositionCallback);

    setVerticalSync(true);

    m_IsOpen = true;

    return true;
}

void Window::close(void)
{
    if (m_IsOpen)
    {
        glfwDestroyWindow(m_Window);

        m_IsOpen = false;
    }
}

bool Window::isOpen(void) const
{
    return m_IsOpen;
}

Vector2i Window::getPosition(void) const
{
    int x, y;
    glfwGetWindowPos(m_Window, &x, &y);

    return Vector2i(x, y);
}

void Window::setPosition(const Vector2i& _position)
{
    glfwSetWindowPos(m_Window, _position.x, _position.y);
}

Vector2u Window::getSize(void) const
{
    int x, y;
    glfwGetWindowSize(m_Window, &x, &y);

    return Vector2u(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
}

void Window::setSize(const Vector2u& _size)
{
    glfwSetWindowSize(m_Window, _size.x, _size.y);
}

void Window::display(void)
{
    glfwSwapBuffers(m_Window);
}

bool Window::pollEvent(Event& _event)
{
    glfwPollEvents();

    if (m_Events.empty())
    {
        return false;
    }

    _event = m_Events.back();
    m_Events.pop_back();

    return true;
}
void Window::waitEvent(Event& _event)
{
    std::cout << "NOT IMPLEMENTED YET: Window waitEvent" << std::endl;
}

void Window::setRepeatedKeys(bool _repeat)
{
    std::cout << "NOT IMPLEMENTED YET: Window setRepeatedKeys" << std::endl;
}

void Window::setTitle(const std::string& _title)
{
    glfwSetWindowTitle(m_Window, _title.c_str());
}

std::string Window::getTitle(void) const
{
    std::cout << "NOT IMPLEMENTED YET: Window getTitle" << std::endl;
}

void Window::setVerticalSync(bool _vsync /*= true*/)
{
    glfwSwapInterval((_vsync) ? 1 : 0);
}

bool Window::getVerticalSyncState(void)
{
    std::cout << "NOT IMPLEMENTED YET: Window getVerticalSyncState" << std::endl;
}

void Window::switchToFullscreen(const VideoMode& _videoMode)
{
    std::cout << "NOT IMPLEMENTED YET: Window switchToFullscreen" << std::endl;
}

Vector2d Window::getMousePos(void)
{
    Vector2d pos;
    glfwGetCursorPos(m_Window, &pos.x, &pos.y);

    return pos;
}

} //~ namespace zeno
