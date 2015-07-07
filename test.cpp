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
    zeno::Epub epub;

    std::string c1Data = "<h1>Chapter 1 title</h1><p>Chapter 1 data content</p>";
    std::string c2Data = "<h1>Chapter 2 title</h1><p>Chapter 2 data content</p>";
    std::string c3Data = "<h1>Chapter 3 title</h1><p>Chapter 3 data content</p>";

    epub.addChapterContent(c1Data, "Chapter 1 Chapter Name");
    epub.addChapterContent(c2Data, "Chapter 2 Chapter Name");
    epub.addChapterContent(c3Data, "Chapter 3 Chapter Name");

    epub.setEpubTitle("Mark misc title");
    epub.setEpubAuthor("Mark Davison");

    epub.writeToFile("C:/Users/Mark/Desktop/Example.epub");

    return EXIT_SUCCESS;
    /*zeno::XML xml = zeno::XML();

    if (!xml.loadFromFile("C:/Users/Mark/Desktop/simple.xml"))
    {
        return EXIT_FAILURE;
    }

    std::cout << "Pre modifications." << std::endl;
    std::cout << xml.writeToString() << std::endl;
    std::cout << "Post modifications." << std::endl;

    if (!xml.addComment("Commentything", "/root/breakfast_menu/food/", {0, 0, 1}))
    {
        std::cout << "Failed to add comment" << std::endl;
        return EXIT_FAILURE;
    }
    if (!xml.addContent("Miscellaneous content.", "/root/breakfast_menu/food/", {0, 0, 3}))
    {
        std::cout << "Failed to add content" << std::endl;
        return EXIT_FAILURE;
    }
    if (!xml.addDeclaration("DECLARATION THING"))
    {
        std::cout << "Failed to add declaration" << std::endl;
        return EXIT_FAILURE;
    }
    if (!xml.addElement("New_Tag", {{"Attribute1", "Value1"}, {"Attribute2", "Value2"}, {"Attribute3", "Value3"}}, "/root/breakfast_menu/food/", {0, 0, 2}))
    {
        std::cout << "Failed to add element" << std::endl;
        return EXIT_FAILURE;
    }
    if (!xml.addContent("New_Tag content.", "/root/breakfast_menu/food/New_Tag/", {0, 0, 2, 0}))
    {
        std::cout << "Failed to add content" << std::endl;
        return EXIT_FAILURE;
    }
    if (!xml.addClosedElement("New_Tag_Closed", {{"CAttribute1", "CValue1"}, {"CAttribute2", "CValue2"}, {"CAttribute3", "CValue3"}}, "/root/breakfast_menu/food/", {0, 0, 2}))
    {
        std::cout << "Failed to add closed element" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << xml.writeToString() << std::endl;

    xml.writeToFile("C:/Users/Mark/Desktop/zeno.xml");

    return EXIT_SUCCESS;
    zeno::Zip zip;

    if (!zip.addFile("C:/Users/Mark/Desktop/File.txt", "Text/"))
    {
        std::cout << "Failed to add file File.txt" << std::endl;
        return EXIT_FAILURE;
    }
    if (!zip.addFile("C:/Users/Mark/Desktop/TextDocument.txt", "Text/"))
    {
        std::cout << "Failed to add file TextDocument.txt" << std::endl;
        return EXIT_FAILURE;
    }
    if (!zip.addFile("C:/Users/Mark/Desktop/Longer.txt", "Text/"))
    {
        std::cout << "Failed to add file Longer.txt" << std::endl;
        return EXIT_FAILURE;
    }
    if (!zip.addFile("C:/Users/Mark/Desktop/Dolphin.png", "Pictures/"))
    {
        std::cout << "Failed to add file Dolphin.png" << std::endl;
        return EXIT_FAILURE;
    }
    if (!zip.addFile("C:/Users/Mark/Desktop/Voyage.epub", "Epubs/"))
    {
        std::cout << "Failed to add file Voyage.epub" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<unsigned char> data = {'H', 'e', 'l', 'l', 'o'};
    zip.addFileFromMemory(data, "MemoryFile.txt", "Text/");



    if (!zip.saveToFile("C:/Users/Mark/Desktop/Output.zip"))
    {
        std::cout << "Zip file failed to save" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

    zeno::HTTPProtocol http = zeno::HTTPProtocol();

    http.setHost(SERVER);

    zeno::HTTPProtocol::Request request;

    request.setURI("/s/9399635/1/");

    zeno::HTTPProtocol::Response response = http.makeRequest(request);

    std::cout << "Response code: " << response.getStatus() << std::endl;

    for (const std::pair<std::string, std::string>& pair : response.getFields())
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << response.getBody() << std::endl;

    return 0;*/

    zeno::Window window = zeno::Window();

    window.create(zeno::VideoMode(1280, 720), "Window", zeno::WindowStyle::Default);

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
    desktop.getElementFromPane<zeno::Button>("Pane", "Button")->setPosition(zeno::Vector3f(0.0f, 50.0f, 0.0f));

    desktop.addToPane("Pane", new zeno::Slider("Slider"));
    desktop.getElementFromPane<zeno::Slider>("Pane", "Slider")->registerCallback([](float _arg){std::cout << "Slider updated to: " << _arg * 100.0f << std::endl;});
	
    desktop.addToPane("Pane", new zeno::TextBox("TextBox", desktop.getGUIFont()));
    desktop.getElementFromPane<zeno::TextBox>("Pane", "TextBox")->setPosition(zeno::Vector3f(640.0f, 0.0f, 0.0f));
    desktop.getElementFromPane<zeno::TextBox>("Pane", "TextBox")->setText("Text!");

    desktop.addToPane("Pane", new zeno::Label("Label", desktop.getGUIFont()));
    desktop.getElementFromPane<zeno::Label>("Pane", "Label")->setLabel("Hello");

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
