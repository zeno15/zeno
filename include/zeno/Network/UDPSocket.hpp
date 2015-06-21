#ifndef INCLUDEDD_ZENO_NETWORK_UDPSOCKET_HPP
#define INCLUDEDD_ZENO_NETWORK_UDPSOCKET_HPP

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
/// \brief  Socket which implements the UDP protocol
///
////////////////////////////////////////////////////////////
class UDPSocket : public Socket
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Constructor
    ///
    /// Initialises socket, to receive must bind it to a port
    ///
    ////////////////////////////////////////////////////////////
    UDPSocket(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Binds the port so it can receive data
    ///
    /// \param  _port   Port number to listen on for data
    ///
    ////////////////////////////////////////////////////////////
    Socket::SocketStatus bind(int _port);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief Unbinds the socket, listening wont ever receive data
    ///
    ////////////////////////////////////////////////////////////
    void unbind(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Send data over the socket
    ///
    /// \param  _data   Pointer to the start of the data to send
    ///
    /// \param  _dataLenth  Size of the data to send in bytes
    ///
    /// \param  _address    Address to send data to
    ///
    /// \param  _port   Port number to send data to
    ///
    /// \return Socket::Socket status representing if the data
    ///          was sent
    ///
    ////////////////////////////////////////////////////////////
    Socket::SocketStatus send(void * _data, std::size_t _dataLength, const std::string& _address, int _port);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Receive data from the socket
    ///
    /// \param  _data   Pointer to the data buffer
    ///
    /// \param  _maxDataLength  Size in bytes that the buffer can hold
    ///
    /// \param  _lengthReceived Size in bytes of the data received
    ///
    /// \return Socket::Socket status representing if the data
    ///         was received correctly
    ///
    ////////////////////////////////////////////////////////////
    Socket::SocketStatus receive(void *_data, std::size_t _maxDataLength, std::size_t& _lengthReceived);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Receive data from the socket
    ///
    /// \param  _data   Pointer to the data buffer
    ///
    /// \param  _maxDataLength  Size in bytes that the buffer can hold
    ///
    /// \param  _lengthReceived Size in bytes of the data received
    ///
    /// \param  _remoteAddress  Address of the source of the data
    ///
    /// \param  _remotePort     Port number of the source of the data
    ///
    /// \return Socket::Socket status representing if the data
    ///         was received correctly
    ///
    ////////////////////////////////////////////////////////////
    Socket::SocketStatus receive(void *_data, std::size_t _maxDataLength, std::size_t& _lengthReceived, std::string& _remoteAddress, int& _remotePort);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Closes the socket properly
    ///
    ////////////////////////////////////////////////////////////
    void close(void);

private:
    SOCKET  m_Handle;       ///<    Windows specific socket handle

};

} //~ namespace zeno

#endif //~ INCLUDEDD_ZENO_NETWORK_UDPSOCKET_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::UDPSocket
///	\ingroup Network
///
///	Explanation of how this all works
///
///	\code
///
/// zeno::UDPSocket receiver;
/// receiver.bind(5555);
///
/// zeno::UDPSocket sender;
/// sender.send((void *)"Hello", 5, "127.0.0.1", 5555);
///
/// char buffer[1024];
/// std::size_t received;
///
/// receiver.receive((void *)buffer, 1024, received);
///
///	\endcode
///
////////////////////////////////////////////////////////////