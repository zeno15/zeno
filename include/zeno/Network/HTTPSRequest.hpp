#ifndef INCLUDED_ZENO_NETWORK_HTTPSREQUEST_HPP
#define INCLUDED_ZENO_NETWORK_HTTPSREQUEST_HPP

#include <zeno/Network/TCPSocket.hpp>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <string>
#include <vector>

namespace zeno {

class HTTPSRequest
{
public:
    HTTPSRequest(void);

    void connectTCP(const std::string& _address, int _port);

    void connectSSL(void);

    void get(const std::string& _target);

    std::string getResponse(void)
    {
        return m_Response;
    }

    void closeConnection(void);

private:
    void write(const std::string& _data);

    std::string read(void);



    std::string parseHeader(const std::vector<std::string>& _headerTokens);

    std::vector<std::string> tokenise(const std::string& _data, const std::string& _delimeter);

private:
    TCPSocket m_Socket;
    SSL *m_SSLHandle;
    SSL_CTX *m_SSLContext;

    std::string m_Host;

    bool    m_Chunked;

    std::string m_Response;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_NETWORK_HTTPSREQUEST_HPP

////////////////////////////////////////////////////////////
///
/// \class zeno::HTTPSRequest
/// \ingroup Network
///
/// Explanation of how this works
///
/// \code
/// #define SSL_PORT 443
/// #define SERVER "www.fanfiction.net"
///
/// zeno::WSASession::getInstance();
///
///
/// zeno::HTTPSRequest https;
///
/// https.connectTCP(SERVER, SSL_PORT);
/// https.connectSSL();
///
/// https.get("/s/9399635/1/Measure-Each-Step-to-Infinity/");
///
/// std::cout << "Chapter 1 ##############################################" << std::endl;
/// std::cout << https.getResponse() << std::endl;
///
/// https.get("/s/9399635/2/Measure-Each-Step-to-Infinity/");
///
/// std::cout << "Chapter 2 ##############################################" << std::endl;
/// std::cout << https.getResponse() << std::endl;
///
/// https.closeConnection();
///
/// \endcode
///
////////////////////////////////////////////////////////////