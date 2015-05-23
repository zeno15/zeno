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

    int glVersion[2] = { -1, -1 };
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

    std::cout << "OpenGL " << glVersion[0] << "." << glVersion[1] << std::endl;

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading langauge version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    zeno::GuiDesktop desktop;
    desktop.setResolution(window.getSize());

    desktop.addPane("Pane");

    desktop.addToPane("Pane", new zeno::Button("Button"));
    desktop.getElementFromPane<zeno::Button>("Pane", "Button")->registerCallback([](void){ std::cout << "Button was pressed!" << std::endl;});

    desktop.addToPane("Pane", new zeno::Slider("Slider"));
    desktop.getElementFromPane<zeno::Slider>("Pane", "Slider")->registerCallback([](float _arg){std::cout << "Slider updated to: " << _arg * 100.0f << std::endl;});
	
#ifdef _WIN32
    desktop.loadGUIFont("C:/Windows/Fonts/segoeui.ttf", 16);
#else
    desktop.loadGUIFont("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-B.ttf", 16);
#endif

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
