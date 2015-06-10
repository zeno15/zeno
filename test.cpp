#include <cstdlib>
#include <iostream>

#include <zeno/Window/Window.hpp>
#include <zeno/Network.hpp>
#include <zeno/GUI.hpp>

#include <GL/glew.h>

#include <fstream>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <zeno/Network/Socket.hpp>
#include <io.h>

#define SSL_PORT 443
#define SERVER "www.fanfiction.net"

typedef struct {
    SOCKET socket;
    SSL *sslHandle;
    SSL_CTX *sslContext;
} connection;

SOCKET tcpConnect(void)
{
    int error;
    SOCKET handle;

    struct hostent *host;
    struct sockaddr_in server;

    host = gethostbyname (SERVER);
    handle = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (handle == -1)
    {
        std::cout << "Error creating socket" << std::endl;
        handle = 0;
    }
    else
    {
        server.sin_family = AF_INET;
        server.sin_port = htons (SSL_PORT);
        server.sin_addr = *((struct in_addr *) host->h_addr);


        error = connect (handle, (struct sockaddr *) &server,
                         sizeof (struct sockaddr));
        if (error == -1)
        {
            std::cout << "Error connecting" << std::endl;
            handle = 0;
        }
    }

    return handle;
}

char *sslRead (connection *c)
{
    const int readSize = 1024;
    char *rc = NULL;
    int received, count = 0;
    char buffer[1024];

    if (c)
    {
        while (1)
        {
            if (!rc)
                rc = (char*)malloc (readSize * sizeof (char) + 1);
            else
                rc = (char*)realloc (rc, (count + 1) *
                                  readSize * sizeof (char) + 1);

            received = SSL_read (c->sslHandle, buffer, readSize);
            buffer[received] = '\0';

            if (received > 0)
                strcat (rc, buffer);

            if (received < readSize)
                break;
            count++;
        }
    }

    return rc;
}

// Write text to the connection
void sslWrite (connection *c, char *text)
{
    if (c)
        SSL_write (c->sslHandle, text, strlen (text));
}

void sslDisconnect (connection *c)
{
    if (c->socket)
        closesocket(c->socket);
    if (c->sslHandle)
    {
        SSL_shutdown (c->sslHandle);
        SSL_free (c->sslHandle);
    }
    if (c->sslContext)
        SSL_CTX_free (c->sslContext);

    free (c);
}

connection *sslConnect(void)
{
    connection *c = nullptr;

    c = (connection *)malloc(sizeof(connection));

    c->sslHandle = nullptr;
    c->sslContext = nullptr;

    c->socket = tcpConnect();

    if (c->socket != 0)
    {
        SSL_load_error_strings();
        SSL_library_init();

        c->sslContext = SSL_CTX_new (SSLv23_client_method ());
        if (c->sslContext == NULL)
        {
            std::cout << "Error creating SSL context" << std::endl;
            return nullptr;
        }

        c->sslHandle = SSL_new (c->sslContext);
        if (c->sslHandle == NULL)
        {
            std::cout << "Error creating SSL handle" << std::endl;
            return nullptr;
        }

        if (!SSL_set_fd(c->sslHandle, c->socket))
        {
            std::cout << "Error connecting ssl to our socket connection" << std::endl;
            return nullptr;
        }

        if (SSL_connect(c->sslHandle) != 1)
        {
            std::cout << "Error SSL_connect" << std::endl;
            return nullptr;
        }
    }
    else
    {
        std::cout << "tcpConnect failed." << std::endl;
        return nullptr;
    }

    std::cout << "sslConnect success" << std::endl;
    return c;
}

int main(int _argc, char **_argv)
{
    zeno::WSASession::getInstance();


    connection *c = sslConnect();
    if (c == nullptr)
    {
        std::cout << "sslConnect failed." << std::endl;
        return 1;
    }

    sslWrite(c, "GET /s/9399635/1/Measure-Each-Step-to-Infinity/ HTTP/1.1\r\n" \
                "host: www.fanfiction.net\r\n\r\n");

    char *response = sslRead(c);

    std::cout << response << std::endl;

    std::cout << "Reading again" << std::endl;
    //http://www.jmarshall.com/easy/http/#http1.1c2

    response = sslRead(c);

    std::cout << response << std::endl;

    sslDisconnect(c);

    std::cout << "Success" << std::endl;
    return 0;

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
