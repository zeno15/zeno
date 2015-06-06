#include <zeno/Network/Socket.hpp>

namespace zeno {

Socket::Socket(SocketType _socketType) :
m_SocketType(_socketType),
m_LocalPort(-1),
m_IsBlocking(true)
{
}


int Socket::getLocalPort(void)
{
    return m_LocalPort;
}

bool Socket::isBlocking(void)
{
    return m_IsBlocking;
}

void Socket::setBlocking(bool _blocking)
{
    m_IsBlocking = _blocking;
}

} //~ namespace zeno