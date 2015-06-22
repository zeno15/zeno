#ifndef INCLUDED_ZENO_NETWORK_SOCKET_HPP
#define INCLUDED_ZENO_NETWORK_SOCKET_HPP

#include <string>
#include <system_error>

#include <zeno/Network/SocketHandle.hpp>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief Base class for TCP and UDP sockets to build upon
///
////////////////////////////////////////////////////////////
class Socket
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief Enumeration of possible Socket types
    ///
    ////////////////////////////////////////////////////////////
    enum SocketType {
        UDP,        ///<    UDP Socket, no connection setup required
        TCP         ///<    TCP Socket, requires connection setup
    };

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Enumeration of states sockets can be in, also
    ///         used as return types
    ///
    ////////////////////////////////////////////////////////////
    //~ TODO -  Make these proper
    enum SocketStatus {
        GOOD_SOCKET,
        ERROR_SCOKET,
        SOCKET_DONE
    };
    enum ShutDownType {
        RECEIVE,        ///<    The socket will not receive any more data
        SEND,           ///<    The socket will not send any more data
        BOTH            ///<    The socket will not send or receive any more data
    };

	////////////////////////////////////////////////////////////
	///
    /// \brief  Constructor, requires a given SocketType
    ///
    /// \param  _socketType The protocol this socket is using
	///
	////////////////////////////////////////////////////////////
	Socket(SocketType _socketType);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Get the local port this socket is bound to
    ///
    /// \return Local port number
    ///
    ////////////////////////////////////////////////////////////
    int getLocalPort(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the blocking status of the Socket
    ///
    /// \return True if Socket is blocking, False otherwise
    ///
    ////////////////////////////////////////////////////////////
    bool isBlocking(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the blocking state of the Socket
    ///
    /// \param  _blocking   Boolean value to set Sockets blocking state
    ///
    ////////////////////////////////////////////////////////////
    void setBlocking(bool _blocking);

protected:
    SocketType          m_SocketType;       ///<    The type of the Socket (TCP/UDP)

    int                 m_LocalPort;        ///<    Port Number

    bool                m_IsBlocking;       ///<    Blocking state of the socket
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_NETWORK_SOCKET_HPP