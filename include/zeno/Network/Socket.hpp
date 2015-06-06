#ifndef INCLUDED_ZENO_NETWORK_SOCKET_HPP
#define INCLUDED_ZENO_NETWORK_SOCKET_HPP

#include <string>

#include <winsock2.h>
#include <system_error>

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
        ERROR_SCOKET
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

class WSASession
{
public:
    static WSASession& getInstance(void)
    {
        //~ Ensures that a valid WSA Session is running
        static WSASession wsa = WSASession();

        return wsa;
    }
private:
    WSASession(void)
    {
        if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        {
            throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");
        }
    }

    ~WSASession(void)
    {
        WSACleanup();
    }

    WSADATA data;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_NETWORK_SOCKET_HPP