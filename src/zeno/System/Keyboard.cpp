#include <zeno/System/Keyboard.hpp>

#include <zeno/Window/Window.hpp>

#include <GLFW/glfw3.h>

namespace zeno {

bool Keyboard::isKeyDown(Key _key, const Window& _window)
{
    return (GLFW_PRESS == glfwGetKey(_window.m_Window, _key));
}

} //~ namespace zeno