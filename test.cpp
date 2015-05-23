#include <cstdlib>
#include <iostream>

#include <zeno/Window/Window.hpp>

#include <zeno/GUI.hpp>

#include <GL/glew.h>

int main(int _argc, char **_argv)
{
    zeno::Window window = zeno::Window();

    window.create(zeno::VideoMode(1280, 720), "Window", zeno::WindowStyle::Titlebar);

    window.setVerticalSync(true);

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading langauge version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    zeno::GuiDesktop desktop;
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

    desktop.addPane("Pane");

    desktop.addToPane("Pane", new zeno::Button("Button"));
    desktop.getElementFromPane<zeno::Button>("Pane", "Button")->registerCallback([](void){ std::cout << "Button was pressed!" << std::endl;});

    desktop.addToPane("Pane", new zeno::Slider("Slider"));
    desktop.getElementFromPane<zeno::Slider>("Pane", "Slider")->registerCallback([](float _arg){std::cout << "Slider updated to: " << _arg * 100.0f << std::endl;});
	
    desktop.addToPane("Pane", new zeno::TextBox("TextBox", desktop.getGUIFont()));
    desktop.getElementFromPane<zeno::TextBox>("Pane", "TextBox")->setPosition(zeno::Vector3f(640.0f, 0.0f, 0.0f));
    desktop.getElementFromPane<zeno::TextBox>("Pane", "TextBox")->setText("Text!");

    glClearColor(100.0f / 255.0f, 149.0f / 255.0f, 247.0f / 255.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
