#include <cstdlib>
#include <iostream>

#include <zeno/System/Clock.hpp>
#include <zeno/Network.hpp>
#include <zeno/Window/Window.hpp>
#include <zeno/Graphics/Rectangle.hpp>
#include <zeno/Graphics/Circle.hpp>
#include <zeno/GUI.hpp>

#include <GL/glew.h>

#include <ctime>

#include <zeno/Utility/Epub.hpp>
#include <zeno/Utility/XML.hpp>
#include <zeno/Utility/Zip.hpp>

#define SERVER "https://www.fanfiction.net"



int main(int _argc, char **_argv)
{
    zeno::Window window = zeno::Window();

    window.create(zeno::VideoMode(1280, 720), "Window", zeno::WindowStyle::Default);

    window.setVerticalSync(true);

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading langauge version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    zeno::Desktop desktop;
    desktop.setResolution(window.getSize());

#ifdef _WIN32
    if (!desktop.loadGUIFont("C:/Windows/Fonts/segoeui.ttf", 32))
    {
        std::cout << "Failed to load font." << std::endl;
    }
#else
    if (!desktop.loadGUIFont("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-B.ttf", 32))
    {
        std::cout << "Failed to load font." << std::endl;
    }
#endif

    glClearColor(100.0f / 255.0f, 149.0f / 255.0f, 247.0f / 255.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bool running = true;
    bool paneVisible = true;

    zeno::Rectangle r(zeno::Vector2f(100.0f, 100.0f), zeno::Vector2f(250.0f, 50.0f));
    r.setInternalColour(zeno::Colour::Magenta);

    zeno::Circle c(64.0f, 6);
    c.setPosition(zeno::Vector2f(96.0f, 96.0f));

    zeno::RenderData data;

    while (running)
    {
        zeno::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == zeno::Event::EventType::WindowClosed)
            {
                running = false;
            }
            else if (event.type == zeno::Event::EventType::WindowSizeChanged)
            {
                glViewport(0, 0, event.size.width, event.size.height);
                desktop.setResolution(zeno::Vector2u(event.size.width, event.size.height));
            }
            else if (event.type == zeno::Event::EventType::KeyDown)
            {
                if (event.key.key == zeno::Keyboard::Space)
                {

                }
            }

            desktop.processEvent(event);
        }
        desktop.processThrown();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        data.transform = zeno::Mat4x4::Orthographic2D(0.0f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y), 0.0f);

        r.render(data.transform);
        c.render(data.transform);

        desktop.render();

        window.display();
    }

    window.close();

    return EXIT_SUCCESS;
}
