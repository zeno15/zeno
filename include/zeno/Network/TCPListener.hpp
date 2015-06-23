#ifndef INCLUDED_ZENO_NETWORK_TCPLISTENER_HPP
#define INCLUDED_ZENO_NETWORK_TCPLISTENER_HPP

#include <zeno/Network/TCPSocket.hpp>


////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief  Socket that listens from incoming connections
///         and then modifies a socket to use on the new
///         connection
///
////////////////////////////////////////////////////////////
class TCPListener : public Socket
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Default constructor
    ///
    /// Creates the socket to be used by the listener
    ///
    ////////////////////////////////////////////////////////////
    TCPListener(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Binds the socket to the given port and gets it
    ///         to listen for incoming connections on the given
    ///         port
    ///
    /// \param  _port   Port number to listen on
    ///
    /// \return SocketStatus representing if the method was
    ///         successful or not
    ///
    ////////////////////////////////////////////////////////////
    Socket::SocketStatus listen(int _port);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Accepts an incoming connection and modifies a
    ///         given socket to create the connection
    ///
    /// \param  _socket TCPSocket to be used for the connection
    ///
    /// \return SocketStatus representing if the method was
    ///         successful or not
    ///
    ////////////////////////////////////////////////////////////
    Socket::SocketStatus accept(TCPSocket& _socket);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Closes the socket so it will no longer listen
    ///         for connections
    ///
    ////////////////////////////////////////////////////////////
    void close(void);

private:
    SocketHandle    m_Handle;               ///<    Windows specific socket handle
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_NETWORK_TCPLISTENER_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::TCPListener
///	\ingroup Network
///
///	Explanation of how this all works
///
///	\code
///
/// zeno::TCPListener listener;
/// listener.listen(5555);
///
/// zeno::TCPSocket socket;
///
/// listener.accept(socket);
///
/// socket.send("Hello", 5);
///
/// socket.close();
///
/// listener.close();
///
///	\endcode
///
////////////////////////////////////////////////////////////
