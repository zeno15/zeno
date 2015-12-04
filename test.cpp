#include <cstdlib>
#include <iostream>

#include <zeno/System/Clock.hpp>
#include <zeno/Network.hpp>
#include <zeno/Window/Window.hpp>
#include <zeno/Graphics/Rectangle.hpp>
#include <zeno/Graphics/Texture.hpp>
#include <zeno/Graphics/Sprite.hpp>
#include <zeno/Graphics/Circle.hpp>
#include <zeno/Graphics/Polygon.hpp>
#include <zeno/GUI.hpp>

#include <GL/glew.h>
#include <ctime>

#include <zeno/Utility/Epub.hpp>
#include <zeno/Utility/XML.hpp>
#include <zeno/Utility/Zip.hpp>

#include <zeno/Game/Game.hpp>

int main(int _argc, char **_argv)
{
    /*zeno::VideoMode mode;

    mode.width = 1280;
    mode.height = 720;

    zeno::Window window2;
    if (!window2.create(mode, "Window", zeno::WindowStyle::Titlebar))
    {
        std::cout << "Window failed to create" << std::endl;
        return EXIT_FAILURE;
    }

    bool running2 = true;

    zeno::Clock clock;

    while (running2)
    {
        zeno::Event event;
        while (window2.pollEvent(event))
        {
            if (event.type == zeno::Event::EventType::WindowClosed)
            {
                running2 = false;
            }
            else if (event.type == zeno::Event::MouseEntered)
            {
                std::cout << "zeno: Mouse " << (event.enter.entered ? "entered" : "left") << " the window." << std::endl;
            }
            else if (event.type == zeno::Event::MouseButtonPressed)
            {
                std::cout << "zeno: Mouse " << event.mouseButton.button << " pressed at x: " << event.mouseButton.x << ", y: " << event.mouseButton.y << std::endl;
            }
            else if (event.type == zeno::Event::KeyDown)
            {
                std::cout << "zeno: Key down: " << event.key.key << std::endl;
            }
            else if (event.type == zeno::Event::KeyRepeat)
            {
                std::cout << "zeno: Key repeat: " << event.key.key << std::endl;
            }
        }

        //std::cout << "FPS: " << 1.0f / clock.getElapsedTime().asSeconds() << std::endl;
        clock.restart();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window2.display();
    }

    window2.close();

    return EXIT_SUCCESS;*/

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

    desktop.addToElement<zeno::CheckBox>("CheckBox1");
    desktop.getElement<zeno::CheckBox>("CheckBox1").setPosition(zeno::Vector3f(50.0f, 250.0f, 0.0f));

    desktop.addToElement<zeno::CheckBox>("CheckBox2");
    desktop.getElement<zeno::CheckBox>("CheckBox2").setPosition(zeno::Vector3f(50.0f, 275.0f, 0.0f));

    desktop.addToElement<zeno::CheckBox>("CheckBox3");
    desktop.getElement<zeno::CheckBox>("CheckBox3").setPosition(zeno::Vector3f(50.0f, 300.0f, 0.0f));

    desktop.addToElement<zeno::DropdownMenu>("DropdownMenu");
    desktop.getElement<zeno::DropdownMenu>("DropdownMenu").setPosition(zeno::Vector3f(150.0f, 500.0f, 0.0f));
    desktop.getElement<zeno::DropdownMenu>("DropdownMenu").setSize(zeno::Vector2f(450.0f, 40.0f));
    desktop.getElement<zeno::DropdownMenu>("DropdownMenu").addChoice("Heeeeeeeellllo");
    desktop.getElement<zeno::DropdownMenu>("DropdownMenu").addChoice("Option 2");
    desktop.getElement<zeno::DropdownMenu>("DropdownMenu").addChoice("Option 3");

    desktop.addToElement<zeno::RadioButtonGroup>("RadioGroup");

    desktop.getElement<zeno::RadioButtonGroup>("RadioGroup").addRadioButton("RB1");
    desktop.getElement<zeno::RadioButton>("RB1").setPosition(zeno::Vector3f(150.0f, 275.0f, 0.0f));
    desktop.getElement<zeno::RadioButtonGroup>("RadioGroup").addRadioButton("RB2");
    desktop.getElement<zeno::RadioButton>("RB2").setPosition(zeno::Vector3f(150.0f, 255.0f, 0.0f));
    desktop.getElement<zeno::RadioButtonGroup>("RadioGroup").addRadioButton("RB3");
    desktop.getElement<zeno::RadioButton>("RB3").setPosition(zeno::Vector3f(150.0f, 235.0f, 0.0f));

    desktop.addToElement<zeno::Button>("Button");
    desktop.getElement<zeno::Button>("Button").setSize(zeno::Vector2f(50.0f, 50.0f));
    desktop.getElement<zeno::Button>("Button").setOutlineThickness(2.0f);
    desktop.getElement<zeno::Button>("Button").setBackgroundDefaultColour(zeno::Colour::White);
    desktop.getElement<zeno::Button>("Button").setBackgroundDepressedColour(zeno::Colour(0.8f, 0.8f, 0.8f));
    desktop.getElement<zeno::Button>("Button").setForegroundDefaultColour(zeno::Colour::Black);
    desktop.getElement<zeno::Button>("Button").setForegroundHoverColour(zeno::Colour(0.6f, 0.6f, 0.4f));
    desktop.getElement<zeno::Button>("Button").setPosition(zeno::Vector3f(200.0f, 200.0f, 0.0f));
    desktop.getElement<zeno::Button>("Button").registerCallback([](){ std::cout << "Button press." << std::endl;});

    desktop.addToElement<zeno::Pane>("TestPane");
    desktop.getElement<zeno::Pane>("TestPane").setColour(zeno::Colour::Cyan);
    desktop.getElement<zeno::Pane>("TestPane").setBounds(zeno::FloatRect(680.0f, 80.0f, 560.0f, 560.0f));

    desktop.addToElement<zeno::Label>("TestPaneLabel", "TestPane");
    desktop.getElement<zeno::Label>("TestPaneLabel").setFont(desktop.getGUIFont());
    desktop.getElement<zeno::Label>("TestPaneLabel").setLabel("I'm a label!");
    desktop.getElement<zeno::Label>("TestPaneLabel").setPosition(zeno::Vector3f(700.0f, 100.0f, 0.1f));
    desktop.getElement<zeno::Label>("TestPaneLabel").setLabelColour(zeno::Colour::Black);

    desktop.addToElement<zeno::Button>("Left");
    desktop.getElement<zeno::Button>("Left").setPosition(zeno::Vector3f(680.0f, 20.0f, 0.0f));
    desktop.getElement<zeno::Button>("Left").setSize(zeno::Vector2f(60.0f, 40.0f));
    desktop.getElement<zeno::Button>("Left").registerCallback([&](){desktop.getElement<zeno::Pane>("TestPane").scroll(zeno::Vector2f(-5.0f, 0.0f));});


    desktop.addToElement<zeno::Button>("Right");
    desktop.getElement<zeno::Button>("Right").setPosition(zeno::Vector3f(1180.0f, 20.0f, 0.0f));
    desktop.getElement<zeno::Button>("Right").setSize(zeno::Vector2f(60.0f, 40.0f));
    desktop.getElement<zeno::Button>("Right").registerCallback([&](){desktop.getElement<zeno::Pane>("TestPane").scroll(zeno::Vector2f(+5.0f, 0.0f));});


    desktop.addToElement<zeno::Button>("Up");
    desktop.getElement<zeno::Button>("Up").setPosition(zeno::Vector3f(620.0f, 580.0f, 0.0f));
    desktop.getElement<zeno::Button>("Up").setSize(zeno::Vector2f(40.0f, 60.0f));
    desktop.getElement<zeno::Button>("Up").registerCallback([&](){desktop.getElement<zeno::Pane>("TestPane").scroll(zeno::Vector2f(0.0f, +5.0f));});


    desktop.addToElement<zeno::Button>("Down");
    desktop.getElement<zeno::Button>("Down").setPosition(zeno::Vector3f(620.0f, 80.0f, 0.0f));
    desktop.getElement<zeno::Button>("Down").setSize(zeno::Vector2f(40.0f, 60.0f));
    desktop.getElement<zeno::Button>("Down").registerCallback([&](){desktop.getElement<zeno::Pane>("TestPane").scroll(zeno::Vector2f(0.0f, -5.0f));});

    zeno::Game game = zeno::Game();

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
                    std::cout << "Current combo box choice: '" << desktop.getElement<zeno::DropdownMenu>("DropdownMenu").getCurrentChoice() << "'" << std::endl;
                    std::cout << "Current radio button choice: " << desktop.getElement<zeno::RadioButtonGroup>("RadioGroup").getActiveOption() << std::endl;
                }
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
