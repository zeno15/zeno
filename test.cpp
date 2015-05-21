#include <cstdlib>
#include <iostream>

#include <zeno/Window/Window.hpp>

#include <zeno/GUI.hpp>

#include <GL/glew.h>

int main(int _argc, char **_argv)
{
    zeno::Window window = zeno::Window();

    zeno::VideoMode m;

    m.bitsPerPixel = 32;
    m.width = 1280;
    m.height = 720;

    window.create(m, "zeno::Window Test", zeno::WindowStyle::Default);

    window.setVerticalSync(true);

    zeno::GuiDesktop desktop;
    desktop.setResolution(window.getSize());

    desktop.addPane("Pane");

    desktop.addToPane("Pane", new zeno::Slider("Slider"));

    desktop.getElementFromPane<zeno::Slider>("Pane", "Slider")->registerCallback([](float _arg){std::cout << "Slider updated to: " << _arg * 100.0f << std::endl;});

    desktop.loadGUIFont("C:/Windows/Fonts/segoeui.ttf", 16);

    glClearColor(100.0f / 255.0f, 149.0f / 255.0f, 247.0f / 255.0f, 1.0f);

    bool running = true;

    while (running)
    {
        zeno::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == zeno::Event::EventType::WindowClosed)
            {
                running = false;
            }

            desktop.processEvent(event);
        }
        desktop.processThrown();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        desktop.render();

        window.display();
    }

    window.close();

    return EXIT_SUCCESS;
}