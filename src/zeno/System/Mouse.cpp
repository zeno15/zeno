#include <zeno/System/Mouse.hpp>

#include <zeno/Window/Window.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

namespace zeno {

bool Mouse::isButtonDown(Button _button, const Window& _window)
{
    return (GLFW_PRESS == glfwGetMouseButton(_window.m_Window, _button));
}

Vector2i Mouse::getPosition(const Window& _window)
{
    double x = 0.0;
    double y = 0.0;

    glfwGetCursorPos(_window.m_Window, &x, &y);

    return zeno::Vector2i(static_cast<int>(x), static_cast<int>(y));
}

void Mouse::setPosition(const Vector2i& _position, const Window& _window)
{
    glfwSetCursorPos(_window.m_Window, _position.x, _position.y);
}

} //~ namespace zeno