#ifndef ZENO_NETWORK_SSLTCPSOCKET_HPP
#define ZENO_NETWORK_SSLTCPSOCKET_HPP

#include <zeno/Network/TCPSocket.hpp>

//~ Forward declarations so the OpenSSL headers arent included here
typedef struct ssl_ctx_st SSL_CTX;
typedef struct ssl_st SSL;

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief  TCPSocket secured using OpenSSL (TLS v1.0+)
///
////////////////////////////////////////////////////////////
class SSLTCPSocket : public TCPSocket
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Connects the socket to the remote destination
    ///
    /// \param  _address    The address of the desired connection
    ///
    /// \param  _port       The port of the desired connection
    ///                     Defaults to 443
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
    /// \brief  Closes the socket
    ///
    /// Shuts it down (send and receive) before closing
    ///
    ////////////////////////////////////////////////////////////
    virtual void close(void);

private:
    SSL *m_SSLHandle;           ///<    Pointer to the OpenSSL ssl handle
    SSL_CTX *m_SSLContext;      ///<    Pointer to the OpenSSL ssl context

};

} //~ namespace zeno

#endif //ZENO_NETWORK_SSLTCPSOCKET_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::SSLTCPSocket
///	\ingroup Network
///
///	Explanation of how this all works
///
///	\code
///
/// zeno::SSLTCPSocket socket;
///
/// socket.connect("www.google.co.nz", 443);
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