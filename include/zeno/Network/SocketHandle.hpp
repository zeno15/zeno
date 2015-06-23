#ifndef ZENO_NETWORK_SOCKET_HANDLE_HPP
#define ZENO_NETWORK_SOCKET_HANDLE_HPP

#ifdef _WIN32

#include <winsock2.h>

////////////////////////////////////////////////////////////
///
/// \brief  Utility class to ensure sockets work on Windows
///
/// Essentially just calls WSAStartup the first time a socket
/// is made, and calls WSACleanup when the program ends
///
////////////////////////////////////////////////////////////
class WSASession
{
public:
    static WSASession& getInstance(void)
    {
        //~ Ensures that a valid WSA Session is running
        static WSASession wsa = WSASession();

        return wsa;
    }
private:
    WSASession(void)
    {
        if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        {
            throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");
        }
    }

    ~WSASession(void)
    {
        WSACleanup();
    }

    WSADATA data;
};

typedef SOCKET SocketHandle;

#endif
#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef int SocketHandle;

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

#endif //ZENO_NETWORK_SOCKET_HANDLE_HPP
