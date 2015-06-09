#ifndef INCLUDED_ZENO_NETWORK_TCPLISTENER_HPP
#define INCLUDED_ZENO_NETWORK_TCPLISTENER_HPP

#include <zeno/Network/Socket.hpp>
#include <zeno/Network/TCPSocket.hpp>

#include <winsock2.h>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief
///
////////////////////////////////////////////////////////////
class TCPListener : public Socket
{
public:
    TCPListener(void);

    Socket::SocketStatus listen(int _port);

    Socket::SocketStatus accept(TCPSocket& _socket);

    void shutdown(Socket::ShutDownType _type);

    void close(void);

private:
    SOCKET  m_Handle;               ///<    Windows specific socket handle

    std::string m_RemoteAddress;    ///<    Address of the remote end of the connection

    int         m_RemotePort;       ///<    Port of the remote end of the connection
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_NETWORK_TCPLISTENER_HPP
