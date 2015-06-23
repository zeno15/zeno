#ifndef INCLUDED_ZENO_NETWORK_TCPSOCKET_HPP
#define INCLUDED_ZENO_NETWORK_TCPSOCKET_HPP

#include <zeno/Network/Socket.hpp>


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
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Default constructor
    ///
    /// Creates the socket to be used
    ///
    ////////////////////////////////////////////////////////////
    TCPSocket(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Connects the socket to the remote destination
    ///
    /// \param  _address    The address of the desired connection
    ///
    /// \param  _port       The port of the desired connection
    ///
    /// \return SocketStatus representing if the method was
    ///         successful or not
    ///
    ////////////////////////////////////////////////////////////
    virtual Socket::SocketStatus connect(const std::string& _address, int _port);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sends data to the connected host
    ///
    /// \param  _data   Pointer to the data to send
    ///
    /// \param  _dataLength Length of data to send
    ///
    /// \return SocketStatus representing if the method was
    ///         successful or not
    ///
    ////////////////////////////////////////////////////////////
    virtual Socket::SocketStatus send(void *_data, std::size_t _dataLength);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Receive data from the connected host
    ///
    /// \param  _data   Pointer to the buffer to store data in
    ///
    /// \param  _dataLength Maximum length of data to receive
    ///
    /// \param  _received   Reference variable to store how much
    ///                     data was actually received
    ///
    /// \return SocketStatus representing if the method was
    ///         successful or not
    ///
    ////////////////////////////////////////////////////////////
    virtual Socket::SocketStatus receive(void *_data, std::size_t _dataLength, std::size_t& _received);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Shuts the socket down without closing it
    ///
    /// \param  _type   The type of shutdown to perform
    ///
    ////////////////////////////////////////////////////////////
    void shutdown(ShutDownType _type);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Closes the socket
    ///
    /// Shuts it down (send and receive) before closing
    ///
    ////////////////////////////////////////////////////////////
    virtual void close(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the system specific handle to the socket
    ///
    /// \return System specific handle to the socket
    ///
    ////////////////////////////////////////////////////////////
    SocketHandle getHandle(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the remote address of the connected host
    ///
    /// \return std::string containing the remote host address
    ///
    ////////////////////////////////////////////////////////////
    std::string getRemoteAddress(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the remote port of the connected host
    ///
    /// \return int containing the remote host port
    ///
    ////////////////////////////////////////////////////////////
    int getRemotePort(void);

protected:
    friend class TCPListener;               ///<    Allows TCPListener to directly modify remote components

    SocketHandle    m_Handle;               ///<    Windows specific socket handle

    std::string     m_RemoteAddress;        ///<    Address of the remote end of the connection

    int             m_RemotePort;           ///<    Port of the remote end of the connection
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_NETWORK_TCPSOCKET_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::TCPSocket
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