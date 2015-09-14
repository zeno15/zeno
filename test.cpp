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

    desktop.addToElement<zeno::CheckBox>("CheckBox1");
    desktop.getElement<zeno::CheckBox>("CheckBox1").setPosition(zeno::Vector3f(50.0f, 250.0f, 0.0f));

    desktop.addToElement<zeno::CheckBox>("CheckBox2");
    desktop.getElement<zeno::CheckBox>("CheckBox2").setPosition(zeno::Vector3f(50.0f, 275.0f, 0.0f));

    desktop.addToElement<zeno::CheckBox>("CheckBox3");
    desktop.getElement<zeno::CheckBox>("CheckBox3").setPosition(zeno::Vector3f(50.0f, 300.0f, 0.0f));

    desktop.addToElement<zeno::DropdownMenu>("DropdownMenu");
    desktop.getElement<zeno::DropdownMenu>("DropdownMenu").setPosition(zeno::Vector3f(150.0f, 550.0f, 0.0f));
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
