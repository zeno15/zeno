#include <zeno/Network/TCPListener.hpp>

#include <iostream>
#include <winsock2.h>

namespace zeno {

TCPListener::TCPListener(void) :
Socket(SocketType::TCP),
m_RemotePort(-1)
{
    WSASession::getInstance();

    m_Handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_Handle == INVALID_SOCKET)
    {
        std::cout << "Failed to init TCPListener socket." << std::endl;
    }
}

Socket::SocketStatus TCPListener::listen(int _port)
{
    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    addr.sin_port = htons(_port);

    if (::bind(m_Handle, (sockaddr *)(&addr), sizeof(addr)) != 0)
    {
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    if (::listen(m_Handle, 10) != 0)
    {
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    return Socket::SocketStatus::GOOD_SOCKET;
}

Socket::SocketStatus TCPListener::accept(TCPSocket& _socket)
{
    sockaddr_in remoteAddress;
    int remoteAddressLength;

    SOCKET remoteHandle = ::accept(m_Handle, (sockaddr *)(&remoteAddress), &remoteAddressLength);

    if (remoteHandle == INVALID_SOCKET)
    {
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    _socket.m_Handle = remoteHandle;

    _socket.m_RemoteAddress = inet_ntoa(remoteAddress.sin_addr);
    _socket.m_RemotePort = ntohs(remoteAddress.sin_port);

    return Socket::SocketStatus::GOOD_SOCKET;
}

void TCPListener::shutdown(Socket::ShutDownType _type)
{
    ::shutdown(m_Handle, _type);
}

void TCPListener::close(void)
{
    shutdown(Socket::ShutDownType::BOTH);
    ::closesocket(m_Handle);
}

} //~ namespace zeno