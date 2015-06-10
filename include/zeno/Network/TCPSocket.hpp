#ifndef INCLUDED_ZENO_NETWORK_TCPSOCKET_HPP
#define INCLUDED_ZENO_NETWORK_TCPSOCKET_HPP

#include <zeno/Network/Socket.hpp>

#include <winsock2.h>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

class TCPSocket : public Socket
{
public:

    TCPSocket(void);

    Socket::SocketStatus connect(const std::string& _address, int _port);

    Socket::SocketStatus send(void *_data, std::size_t _dataLength);

    Socket::SocketStatus receive(void *_data, std::size_t _dataLength, std::size_t& _received);

    void shutdown(ShutDownType _type);

    void close(void);

    SOCKET getHandle(void)
    {
        return m_Handle;
    }
private:
    friend class TCPListener;

    SOCKET  m_Handle;               ///<    Windows specific socket handle

    std::string m_RemoteAddress;    ///<    Address of the remote end of the connection

    int         m_RemotePort;       ///<    Port of the remote end of the connection
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_NETWORK_TCPSOCKET_HPP
