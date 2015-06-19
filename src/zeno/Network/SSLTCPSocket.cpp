#include <zeno/Network/SSLTCPSocket.hpp>

#include <iostream>

namespace zeno {

Socket::SocketStatus SSLTCPSocket::connect(const std::string& _address, int _port)
{
    TCPSocket::connect(_address, 443);

    if (getHandle() == INVALID_SOCKET)
    {
        std::cout << "Error connecting ssl, tcp socket invalid" << std::endl;
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    SSL_load_error_strings();
    SSL_library_init();

    m_SSLContext = SSL_CTX_new(SSLv23_client_method());
    if (m_SSLContext == nullptr)
    {
        std::cout << "Error initialising SSL context" << std::endl;
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    m_SSLHandle = SSL_new(m_SSLContext);
    if (m_SSLHandle == nullptr)
    {
        std::cout << "Error creating SSL handle" << std::endl;
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    if (!SSL_set_fd(m_SSLHandle, getHandle()))
    {
        std::cout << "Error connecting SSL to tcp socket" << std::endl;
        return Socket::SocketStatus::ERROR_SCOKET;
    }

    if (SSL_connect(m_SSLHandle) != 1)
    {
        std::cout << "Error connecting SSL" << std::endl;
        return Socket::SocketStatus::ERROR_SCOKET;
    }

}

Socket::SocketStatus SSLTCPSocket::send(void *_data, std::size_t _dataLength)
{
    SSL_write(m_SSLHandle, _data, _dataLength);

    return Socket::SocketStatus::GOOD_SOCKET;
}

Socket::SocketStatus SSLTCPSocket::receive(void *_data, std::size_t _dataLength, std::size_t& _received)
{
    _received = static_cast<std::size_t>(SSL_read(m_SSLHandle, _data, _dataLength));

    if (_received == 0)
    {
        return Socket::SocketStatus::SOCKET_DONE;
    }

    return Socket::SocketStatus::GOOD_SOCKET;
}

void SSLTCPSocket::close(void)
{
    TCPSocket::close();

    SSL_shutdown(m_SSLHandle);
    SSL_free(m_SSLHandle);

    SSL_CTX_free(m_SSLContext);
}

} //~ namespace zeno