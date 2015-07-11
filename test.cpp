#include <cstdlib>
#include <iostream>

#include <zeno/System/Clock.hpp>
#include <zeno/Network.hpp>
#include <zeno/Window/Window.hpp>
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

    auto dp = &desktop;

    //~ Button 1
    desktop.addToElement<zeno::Button>("New Button Id");

    desktop.getElement<zeno::Button>("New Button Id").registerCallback([](void){ std::cout << "Button was pressed!" << std::endl;});
    desktop.getElement<zeno::Button>("New Button Id").setPosition(zeno::Vector3f(50.0f, 50.0f, 0.0f));

    //~ Button 2
    desktop.addToElement<zeno::Button>("New Button Id2");

    desktop.getElement<zeno::Button>("New Button Id2").registerCallback([](void){ std::cout << "Button 2 was pressed!" << std::endl;});
    desktop.getElement<zeno::Button>("New Button Id2").setPosition(zeno::Vector3f(200.0f, 50.0f, 0.0f));

    //~ Slider
    desktop.addToElement<zeno::Slider>("Slider");

    desktop.getElement<zeno::Slider>("Slider").registerCallback([&](float _arg){dp->getElement<zeno::ProgressBar>("ProgressBar").setPercentage(_arg);});
    desktop.getElement<zeno::Slider>("Slider").setPosition(zeno::Vector3f(350.0f, 50.0f, 0.0f));

    //~ ProgressBar
    desktop.addToElement<zeno::ProgressBar>("ProgressBar");

    desktop.getElement<zeno::ProgressBar>("ProgressBar").setPosition(zeno::Vector2f(350.0f, 100.0f));
    desktop.getElement<zeno::ProgressBar>("ProgressBar").setSize(zeno::Vector2f(100.0f, 25.0f));

    //~ Label
    desktop.addToElement<zeno::Label>("Label");

    desktop.getElement<zeno::Label>("Label").setFont(desktop.getGUIFont());
    desktop.getElement<zeno::Label>("Label").setLabelColour(zeno::Colour::Magenta);
    desktop.getElement<zeno::Label>("Label").setLabel("GUI Demo");
    desktop.getElement<zeno::Label>("Label").setPosition(zeno::Vector3f(350.0f, 150.0f, 0.0f));

    //~ Text Box
    desktop.addToElement<zeno::TextBox>("TextBox");

    desktop.getElement<zeno::TextBox>("TextBox").setFont(desktop.getGUIFont());
    desktop.getElement<zeno::TextBox>("TextBox").setSize(zeno::Vector2f(200.0f, 50.0f));
    desktop.getElement<zeno::TextBox>("TextBox").setText("TextBox");
    desktop.getElement<zeno::TextBox>("TextBox").setPosition(zeno::Vector3f(350.0f, 200.0f, 0.0f));

    //desktop.addToPane("Pane", new zeno::TextBox("TextBox", desktop.getGUIFont()));
    //desktop.getElementFromPane<zeno::TextBox>("Pane", "TextBox")->setPosition(zeno::Vector3f(640.0f, 0.0f, 0.0f));
    //desktop.getElementFromPane<zeno::TextBox>("Pane", "TextBox")->setText("Text!");



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
