#include <Window.hpp>

#include <iostream>

namespace zeno {

Window::Window(void)
{
	std::cout << "Window Constructor." << std::endl;
}

Window::~Window(void)
{
	std::cout << "Window Destructor." << std::endl;
}

void Window::display(void)
{
	std::cout << "Window: Display." << std::endl;
}

} //~ namespace zeno


