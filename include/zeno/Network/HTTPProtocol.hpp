#ifndef ZENO_NETWORK_HTTPPROTOCOL_HPP
#define ZENO_NETWORK_HTTPPROTOCOL_HPP

#include <string>
#include <vector>

namespace zeno {

class HTTPProtocol
{
public:
    class Request
    {
    public:
        enum RequestType {
            GET,
            HEAD,
            POST
        };

        Request(RequestType _type = RequestType::GET);

        std::string getRequestType(void) const;

        unsigned int getMajorVersion(void);
        unsigned int getMinorVersion(void);

        void addField(const std::string& _field, const std::string& _value);

        bool hasField(const std::string& _field) const;

        std::string getFieldValue(const std::string& _field) const;

        const std::vector<std::pair<std::string, std::string>>& getFields(void) const;

        void setURI(const std::string& _uri);

        std::string getURI(void);

    private:
        RequestType         m_Type;

        std::string         m_URI;

        std::vector<std::pair<std::string, std::string>>        m_Fields;

        unsigned int            m_MajorVersionNumber;
        unsigned int            m_MinorVersionNumber;
    };

    class Response
    {
    public:
        void setBody(const std::string& _str);
        void appendBody(const std::string& _str);

        const std::vector<std::pair<std::string, std::string>>& getFields(void) const;

        bool hasField(const std::string& _field) const;

        std::string getFieldValue(const std::string& _field) const;

        void parseResponseString(const std::string& _responseString);

        std::string getBody(void);

        unsigned int getMajorVersion(void);
        unsigned int getMinorVersion(void);

        unsigned int getStatus(void);
    private:
        std::vector<std::pair<std::string, std::string>>        m_Fields;

        unsigned int            m_MajorVersionNumber;
        unsigned int            m_MinorVersionNumber;

        unsigned int            m_StatusCode;

        std::string m_Body;
    };



    HTTPProtocol(void);

    ~HTTPProtocol(void);

    
    void setHost(const std::string& _host, unsigned int _port = 0);

    HTTPProtocol::Response makeRequest(const HTTPProtocol::Request& _request);

private:
    unsigned int            m_Port;

    std::string             m_Host;

    bool                    m_HTTPS;
};

} //~ namespace zeno

#endif //ZENO_NETWORK_HTTPSPROTOCOL_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::HTTPProtocol
///	\ingroup Network
///
///	Explanation of how this all works
///
///	\code
///
/// zeno::HTTPProtocol http;
///
/// http.setHost("https://www.fanfiction.net");
///
/// zeno::HTTPProtocol::Request request;
///
/// request.setURI("/s/9399635/");
///
/// zeno::HTTPProtocol::Response response = http.makeRequest(request);
///
/// std::cout << "Response code: " << response.getStatus() << std::endl;
///
/// std::cout << response.getBody() << std::endl;
///
///	\endcode
///
////////////////////////////////////////////////////////////