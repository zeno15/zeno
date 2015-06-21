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

////////////////////////////////////////////////////////////
///
/// \brief  Socket which implements the TCP protocol
///
////////////////////////////////////////////////////////////
class TCPSocket : public Socket
{
public:

    TCPSocket(void);

    virtual Socket::SocketStatus connect(const std::string& _address, int _port);

    virtual Socket::SocketStatus send(void *_data, std::size_t _dataLength);

    virtual Socket::SocketStatus receive(void *_data, std::size_t _dataLength, std::size_t& _received);

    void shutdown(ShutDownType _type);

    virtual void close(void);

    SOCKET getHandle(void)
    {
        return m_Handle;
    }
protected:
    friend class TCPListener;

    SOCKET  m_Handle;               ///<    Windows specific socket handle

    std::string m_RemoteAddress;    ///<    Address of the remote end of the connection

    int         m_RemotePort;       ///<    Port of the remote end of the connection
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_NETWORK_TCPSOCKET_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::UDPSocket
///	\ingroup Network
///
///	Explanation of how this all works
///
///	\code
///
/// zeno::TCPSocket socket;
///
/// socket.connect("www.google.co.nz", 80);
///
/// socket.send((void *)"GET / HTTP/1.0\r\n", 16);
///
/// char buffer[1024];
/// std::size_t received;
///
/// socket.receive((void *)buffer, 1024, received);
///
/// socket.close();
///
///	\endcode
///
////////////////////////////////////////////////////////////