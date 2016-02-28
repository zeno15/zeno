#include <zeno/Game/Core/Game.hpp>

#include <GL/glew.h>
#include <iostream>

namespace zeno {


Game::Game(const std::string _title, unsigned int _width, unsigned int _height) :
m_Running(false),
m_DesiredFPS(60),
m_DesiredUPS(60),
m_ClearColour(zeno::Colour::Blue),
m_SceneTime(zeno::Time::seconds(1.0f))
{
    if (!m_Window.create(zeno::VideoMode(_width, _height), _title))
    {
        throw std::runtime_error("Failed to create window");
    }
}

void Game::start(void)
{
    m_Running = true;

    while (m_Running)
    {
        zeno::Event event;
        while (m_Window.pollEvent(event))
        {
            if (event.type == zeno::Event::EventType::WindowClosed)
            {
                if (m_OnCloseButton)
                {
                    m_Running = !m_OnCloseButton();
                }
                else
                {
                    m_Running = false;
                }
            }
            else if (event.type == zeno::Event::EventType::WindowSizeChanged)
            {
                glViewport(0, 0, event.size.width, event.size.height);
                if (m_OnWindowResize) m_OnWindowResize(event.size.width, event.size.height);
            }
        }

        update(1.0f / 60.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render();

        m_Window.display();
    }

    exit();
}

void Game::stop(void)
{
    m_Running = false;
}

void Game::setDesiredFPS(unsigned int _FPS)
{
    m_DesiredFPS = _FPS;
}
unsigned int Game::getDesiredFPS(void) const
{
    return m_DesiredFPS;
}
void Game::setDesiredUPS(unsigned int _UPS)
{
    m_DesiredUPS = _UPS;
}
unsigned int Game::getDesiredUPS(void) const
{
    return m_DesiredUPS;
}

void Game::setClearColour(const zeno::Colour& _colour)
{
    if (m_ClearColour != _colour)
    {
        m_ClearColour = _colour;
        glClearColor(m_ClearColour.r, m_ClearColour.g, m_ClearColour.b, m_ClearColour.a);
    }
}
zeno::Colour Game::getClearColour(void) const
{
    return m_ClearColour;
}


void Game::setResizeMethod(std::function<void(unsigned int, unsigned int)> _resizeMethod)
{
    m_OnWindowResize = _resizeMethod;
}
void Game::setOnCloseButtonMethod(std::function<bool(void)> _closeMethod)
{
    m_OnCloseButton = _closeMethod;
}


void Game::update(float _delta)
{
    m_SceneTime += zeno::Time::seconds(_delta);
}

void Game::render(void) const
{

}

void Game::exit(void)
{
    m_Window.close();
}


} //~ namespace zeno