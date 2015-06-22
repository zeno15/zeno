#ifndef ZENO_NETWORK_SSLTCPSOCKET_HPP
#define ZENO_NETWORK_SSLTCPSOCKET_HPP

#include <zeno/Network/TCPSocket.hpp>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>



namespace zeno {

class SSLTCPSocket : public TCPSocket
{
public:
    virtual Socket::SocketStatus connect(const std::string& _address, int _port);

    virtual Socket::SocketStatus send(void *_data, std::size_t _dataLength);

    virtual Socket::SocketStatus receive(void *_data, std::size_t _dataLength, std::size_t& _received);

    virtual void close(void);

private:
    SSL *m_SSLHandle;
    SSL_CTX *m_SSLContext;

};

} //~ namespace zeno

#endif //ZENO_NETWORK_SSLTCPSOCKET_HPP