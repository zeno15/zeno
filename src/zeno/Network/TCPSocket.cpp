#include <zeno/Network/TCPSocket.hpp>

#include <iostream>
#ifndef _MSC_VER 
#include <unistd.h>
#endif 

namespace zeno {

TCPSocket::TCPSocket(void) :
Socket(SocketType::TCP),
m_RemotePort(-1)
{
    m_Handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_Handle == INVALID_SOCKET)
    {
        std::cout << "TCP Socket failed to construct correctly." << std::endl;
    }
}


Socket::SocketStatus TCPSocket::connect(const std::string& _address, int _port)
{

    if (m_Handle == INVALID_SOCKET)
    {
        m_Handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    struct hostent *host;

    host = gethostbyname(_address.c_str());
    std::string ip = std::string(inet_ntoa (*((struct in_addr *) host->h_addr_list[0])));
    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(_port);

    if (::connect(m_Handle, (sockaddr *)(&addr), sizeof(addr)) != 0)
    {
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    return Socket::SocketStatus::GOOD_SOCKET;
}

Socket::SocketStatus TCPSocket::send(void *_data, std::size_t _dataLength)
{
    if (::send(m_Handle, (char *)_data, _dataLength, 0) == SOCKET_ERROR)
    {
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    return Socket::SocketStatus::GOOD_SOCKET;
}

Socket::SocketStatus TCPSocket::receive(void *_data, std::size_t _dataLength, std::size_t& _received)
{
    _received = static_cast<std::size_t>(::recv(m_Handle, (char *)_data, (int)_dataLength, 0));

    if (_received == 0)
    {
        return Socket::SocketStatus::SOCKET_DONE;
    }
    else if (_received < 0)
    {
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    return Socket::SocketStatus::GOOD_SOCKET;
}

void TCPSocket::shutdown(ShutDownType _type)
{
    ::shutdown(m_Handle, _type);
}

void TCPSocket::close(void)
{
    shutdown(Socket::ShutDownType::BOTH);

    #ifdef _WIN32
    ::closesocket(m_Handle);
    #endif //~ _WIN32
    #ifdef __linux__
    ::close(m_Handle);
    #endif //~ __linux

    m_Handle = INVALID_SOCKET;
}

SocketHandle TCPSocket::getHandle(void)
{
    return m_Handle;
}

std::string TCPSocket::getRemoteAddress(void)
{
    return m_RemoteAddress;
}

int TCPSocket::getRemotePort(void)
{
    return m_RemotePort;
}

} //~ namespace zeno