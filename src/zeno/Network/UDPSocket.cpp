#include <zeno/Network/UDPSocket.hpp>

#include <iostream>
#include <unistd.h>

namespace zeno {

UDPSocket::UDPSocket(void) :
Socket(Socket::SocketType::UDP)
{
    m_Handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (m_Handle == INVALID_SOCKET)
    {
        std::cout << "UDP Socket failed to construct correctly." << std::endl;
    }
}


Socket::SocketStatus UDPSocket::bind(int _port)
{
    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(_port);

    m_LocalPort = _port;

    if (::bind(m_Handle, (sockaddr *)(&addr), sizeof(addr)) != 0)
    {
        return SocketStatus::ERROR_SCOKET;
    }
    else
    {
        return SocketStatus::GOOD_SOCKET;
    }
}

void UDPSocket::unbind(void)
{
    close();
}

Socket::SocketStatus UDPSocket::send(void * _data, std::size_t _dataLength, const std::string& _address, int _port)
{
    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(_address.c_str());
    addr.sin_port = htons(_port);

    int ret = sendto(m_Handle, (char *)_data, _dataLength, 0, (sockaddr *)(&addr), sizeof(addr));



    if (ret == SOCKET_ERROR)
    {
        return SocketStatus::ERROR_SCOKET;
    }

    return SocketStatus::GOOD_SOCKET;
}

Socket::SocketStatus UDPSocket::receive(void *_data, std::size_t _maxDataLength, std::size_t& _lengthReceived)
{
    _lengthReceived = (std::size_t)recv(m_Handle, (char *)_data, _maxDataLength, 0);

    return SocketStatus::GOOD_SOCKET;
}

Socket::SocketStatus UDPSocket::receive(void *_data, std::size_t _maxDataLength, std::size_t& _lengthReceived, std::string& _remoteAddress, int& _remotePort)
{
    sockaddr_in  source;
    unsigned int sourceSize = sizeof(source);

    _lengthReceived = (std::size_t)recvfrom(m_Handle, (char *)_data, _maxDataLength, 0, (sockaddr *)(&source), &sourceSize);

    _remoteAddress = inet_ntoa(source.sin_addr);

    _remotePort = ntohs(source.sin_port);

    return SocketStatus::GOOD_SOCKET;
}

void UDPSocket::close(void)
{

    #ifdef _WIN32
    ::closesocket(m_Handle);
    #endif //~ _WIN32
    #ifdef __linux__
    ::close(m_Handle);
    #endif //~ __linux

    m_LocalPort = -1;
}

} //~ namespace zeno