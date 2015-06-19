#include <zeno/Network/HTTPProtocol.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <zeno/Network/SSLTCPSocket.hpp>
#include <limits>

#define HTTP_PORT 80
#define HTTPS_PORT 443

namespace zeno {

HTTPProtocol::Request::Request(RequestType _type /*= RequestType::GET*/) :
m_Type(_type),
m_MajorVersionNumber(1),
m_MinorVersionNumber(1),
m_URI("/")
{

}

std::string HTTPProtocol::Request::getRequestType(void) const
{
    const char *types[3] = {"GET", "HEAD", "POST"};

    return types[m_Type];
}

unsigned int HTTPProtocol::Request::getMajorVersion(void)
{
    return  m_MajorVersionNumber;
}
unsigned int HTTPProtocol::Request::getMinorVersion(void)
{
    return m_MinorVersionNumber;
}

void HTTPProtocol::Request::addField(const std::string& _field, const std::string& _value)
{
    for (std::pair<std::string, std::string>& pair : m_Fields)
    {
        if (pair.first == _field)
        {
            pair.second = _value;
            return;
        }
    }

    std::string field(_field);
    std::string value(_value);

    std::transform(field.begin(), field.end(), field.begin(), ::tolower);
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);

    m_Fields.push_back(std::pair<std::string, std::string>(_field, _value));
}

bool HTTPProtocol::Request::hasField(const std::string& _field) const
{
    for (const std::pair<std::string, std::string>& pair : m_Fields)
    {
        if (pair.first == _field)
        {
            return true;
        }
    }

    return false;
}

std::string HTTPProtocol::Request::getFieldValue(const std::string& _field) const
{
    for (const std::pair<std::string, std::string>& pair : m_Fields)
    {
        if (pair.first == _field)
        {
            return pair.second;
        }
    }

    //~ TODO change to use custom error stream
    std::cout << "Field '" << _field << "' does not exist." << std::endl;

    return "";
}

const std::vector<std::pair<std::string, std::string>>& HTTPProtocol::Request::getFields(void) const
{
    return m_Fields;
}

void HTTPProtocol::Request::setURI(const std::string& _uri)
{
    m_URI = _uri;
}

std::string HTTPProtocol::Request::getURI(void)
{
    return m_URI;
}



void HTTPProtocol::Response::setBody(const std::string& _str)
{
    m_Body = _str;
}
void HTTPProtocol::Response::appendBody(const std::string& _str)
{
    m_Body.append(_str);
}

const std::vector<std::pair<std::string, std::string>>& HTTPProtocol::Response::getFields(void) const
{
    return m_Fields;
}

bool HTTPProtocol::Response::hasField(const std::string& _field) const
{
    for (const std::pair<std::string, std::string>& pair : m_Fields)
    {
        if (pair.first == _field)
        {
            return true;
        }
    }

    return false;
}

std::string HTTPProtocol::Response::getFieldValue(const std::string& _field) const
{
    for (const std::pair<std::string, std::string>& pair : m_Fields)
    {
        if (pair.first == _field)
        {
            return pair.second;
        }
    }

    //~ TODO change to use custom error stream
    std::cout << "Field '" << _field << "' does not exist." << std::endl;

    return "";
}

void HTTPProtocol::Response::parseResponseString(const std::string& _responseString)
{
    std::stringstream resp(_responseString);

    std::string http;

    resp >> http;

    if (http.size() >= std::string("HTTP/x.x").size() &&
        "HTTP/" == http.substr(0, std::string("HTTP/").size()) &&
        isdigit(http.at(5)) && isdigit(http.at(7)))
    {
        m_MajorVersionNumber = static_cast<unsigned int>(http.at(5) - '0');
        m_MinorVersionNumber = static_cast<unsigned int>(http.at(7) - '0');
    }
    else
    {
        std::cout << "Bad http response." << std::endl;
        return;
    }

    resp >> m_StatusCode;

    resp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;

    while (std::getline(resp, line))
    {
        if (line.size() <= 2)
        {
            break;
        }

        std::size_t loc = line.find(": ");

        std::string field = line.substr(0, loc);
        std::string value = line.substr(loc + 2, std::string::npos);

        while (value.at(value.size() - 1) == '\r' ||
               value.at(value.size() - 1) == '\n')
        {
            value.pop_back();
        }

        std::transform(field.begin(), field.end(), field.begin(), ::tolower);
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);

        m_Fields.push_back(std::pair<std::string, std::string>(field, value));
    }

    if (!hasField("transfer-encoding") || getFieldValue("transfer-encoding") != "chunked")
    {
        if (hasField("content-length"))
        {
            int length = std::strtol(getFieldValue("content-length").c_str(), nullptr, 10);

            m_Body.clear();

            std::istreambuf_iterator<char> iter(resp);
            for (int i = 0; i < length; i += 1)
            {
                m_Body.push_back(*iter);
                iter++;
            }
        }
        else
        {
            std::istreambuf_iterator<char> start(resp);
            for (std::istreambuf_iterator<char> iter = start; iter != std::istreambuf_iterator<char>(); iter ++)
            {
                m_Body.push_back(*iter);
            }
        }
        return;
    }
    else
    {
        int size;

        resp >> std::hex >> size;

        m_Body.clear();

        while (1)
        {
            resp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::istreambuf_iterator<char> iter(resp);
            for (int i = 0; i < size; i += 1)
            {
                m_Body.push_back(*iter);
                iter++;
            }

            if (!(resp >> std::hex >> size))
            {
                break;
            }
        }
    }
}

std::string HTTPProtocol::Response::getBody(void)
{
    return m_Body;
}

unsigned int HTTPProtocol::Response::getMajorVersion(void)
{
    return m_MajorVersionNumber;
}
unsigned int HTTPProtocol::Response::getMinorVersion(void)
{
    return m_MinorVersionNumber;
}



HTTPProtocol::HTTPProtocol(void) :
m_HTTPS(false)
{

}

HTTPProtocol::~HTTPProtocol(void)
{

}


void HTTPProtocol::setHost(const std::string& _host, unsigned int _port /*= 0*/)
{
    if (_host.size() > 7 && _host.substr(0, 7) == "http://")
    {
        m_HTTPS = false;

        if (_port == 0)
        {
            _port = HTTP_PORT;
        }

        m_Port = _port;
        m_Host = _host.substr(7);
    }
    else if (_host.size() > 8 && _host.substr(0, 8) == "https://")
    {
        m_HTTPS = true;

        if (_port == 0)
        {
            _port = HTTPS_PORT;
        }

        m_Port = _port;
        m_Host = _host.substr(8);
    }
    else
    {
        std::cout << "Unknown protocol: " << _host << std::endl;
    }
}

HTTPProtocol::Response HTTPProtocol::makeRequest(const HTTPProtocol::Request& _request)
{
    Request req(_request);

    //~ Check for compulsory fields
    if (!req.hasField("Host"))
    {
        req.addField("Host", m_Host);
    }

    if (!req.hasField("Connection"))
    {
        req.addField("Connection", "close");
    }

    if (!req.hasField("User-Agent"))
    {
        req.addField("User-Agent", "zeno-network/0.1");
    }

    if (!req.hasField("Content-Type"))
    {
        req.addField("Content-Type", "text/html");
    }

    std::stringstream s;

    s << req.getRequestType() << " " << req.getURI();
    s << " HTTP/" << req.getMajorVersion() << "." << req.getMinorVersion() << "\r\n";

    for (const std::pair<std::string, std::string>& pair : req.getFields())
    {
        s << pair.first << ": " << pair.second << "\r\n";
    }

    s << "\r\n";



    Response response = Response();

    TCPSocket *socket = nullptr;

    if (m_HTTPS)
    {
        socket = new SSLTCPSocket();
    }
    else
    {
        socket = new TCPSocket();
    }

    if (socket->connect(m_Host, m_Port) == Socket::SocketStatus::ERROR_SCOKET)
    {
        std::cout << "Socket failed to connect" << std::endl;
        return response;
    }

    if (socket->send((void *)s.str().c_str(), s.str().size()) == Socket::SocketStatus::ERROR_SCOKET)
    {
        std::cout << "Socket failed to send request" << std::endl;
        return response;
    }


    Socket::SocketStatus stat = Socket::SocketStatus::GOOD_SOCKET;
    char buffer[1024];
    const int r_Size = 1024;
    std::size_t received = 1;

    std::string receivedMessage;


    while (received != 0)
    {
        stat = socket->receive((void *)buffer, r_Size, received);

        buffer[received] = '\0';

        receivedMessage.append(buffer);
    }

    response.parseResponseString(receivedMessage);

    socket->close();

    delete socket;

    return response;
}

unsigned int HTTPProtocol::Response::getStatus(void)
{
    return m_StatusCode;
}

} //~ namespace zeno