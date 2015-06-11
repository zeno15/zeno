#include <zeno/Network/HTTPSRequest.hpp>

#include <zeno/Network/TCPSocket.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

namespace zeno {

HTTPSRequest::HTTPSRequest(void) :
        m_Chunked(false)
{

}


void HTTPSRequest::connectTCP(const std::string& _address, int _port)
{
    Socket::SocketStatus stat = m_Socket.connect(_address, _port);

    if (stat == Socket::SocketStatus::ERROR_SCOKET)
    {
        std::cout << "Error connecting tcp socket for https request" << std::endl;
    }

    m_Host = _address;
}

void HTTPSRequest::connectSSL(void)
{
    if (m_Socket.getHandle() == INVALID_SOCKET)
    {
        std::cout << "Error connecting ssl, tcp socket invalid" << std::endl;
        return;
    }

    SSL_load_error_strings();
    SSL_library_init();

    m_SSLContext = SSL_CTX_new(SSLv23_client_method());
    if (m_SSLContext == nullptr)
    {
        std::cout << "Error initialising SSL context" << std::endl;
        return;
    }

    m_SSLHandle = SSL_new(m_SSLContext);
    if (m_SSLHandle == nullptr)
    {
        std::cout << "Error creating SSL handle" << std::endl;
        return;
    }

    if (!SSL_set_fd(m_SSLHandle, m_Socket.getHandle()))
    {
        std::cout << "Error connecting SSL to tcp socket" << std::endl;
        return;
    }

    if (SSL_connect(m_SSLHandle) != 1)
    {
        std::cout << "Error connecting SSL" << std::endl;
        return;
    }
}

void HTTPSRequest::write(const std::string& _data)
{
    SSL_write(m_SSLHandle, _data.c_str(), _data.size());
}

std::string HTTPSRequest::read(void)
{
    const int readSize = 1024;
    char buffer[1024];

    int received = SSL_read(m_SSLHandle, buffer, readSize);

    buffer[received] = '\0';


    std::string out(buffer);

    return out;
}

void HTTPSRequest::closeConnection(void)
{
    m_Socket.close();

    SSL_shutdown(m_SSLHandle);
    SSL_free(m_SSLHandle);

    SSL_CTX_free(m_SSLContext);
}

void HTTPSRequest::get(const std::string& _target)
{
    m_Response = std::string();

    std::string request("GET " + _target + " HTTP/1.1\r\nhost: " + m_Host + "\r\n\r\n");

    write(request);

    std::string response = read();

    std::vector<std::string> tokenisedResponse = tokenise(response, "\r\n");

    std::string chunkSizeString = parseHeader(tokenisedResponse);

    if (!m_Chunked)
    {
        //~ TODO non chunked transfer encoding, need to find a website that doesnt do it
        std::cout << "Non chunked transfer encoding not handled yet" << std::endl;
        return;
    }

    int chunkSize = std::strtol(chunkSizeString.c_str(), nullptr, 16);

    int received = 0;

    std::string accumulatedResponse;

    response = std::string();

    bool waitingForNextChunkSize = false;

    int i = 0;

    while (i += 1)
    {
        std::string newResponse = read();

        received += newResponse.size();

        if (waitingForNextChunkSize)
        {

            if (newResponse.find("\r\n") == 0)
            {
                if (newResponse.size() == 2)
                {
                    continue;
                }
            }
            //std::cout << "Trying to find chunk size from: " << newResponse << std::endl;

            std::size_t crlfLocation = newResponse.find("\r\n");

            if (crlfLocation == std::string::npos)
            {
                std::cout << "Weird fuckery" << std::endl;
                getchar();
            }

            std::string chunksizesubstr = newResponse.substr(0, crlfLocation);
            std::string crlfsubstr = newResponse.substr(crlfLocation, 2);

            //std::cout << "crlfLocation: " << crlfLocation << ", r: '" << newResponse << "'" << std::endl;

            //std::cout << "chunk size substr: '" << chunksizesubstr << "'" << std::endl;
            //std::cout << "crlf substr: '" << crlfsubstr << "'" << std::endl;

           // std::cout << "response size: " << newResponse.size() << ", possible after data start: " << crlfLocation + 2 << std::endl;

            chunkSize = std::strtol(chunksizesubstr.c_str(), nullptr, 16);

            if (chunkSize == 0)
            {
                //std::cout << "STOP!!!!!!!!!!!" << std::endl;
                return;
            }
            received = 0;

            if (crlfLocation + 2 == newResponse.size())
            {
                //std::cout << "New chunk data starts next read, good" << std::endl;
            }
            else
            {

                newResponse = newResponse.substr(crlfLocation + 2);
                received = newResponse.size();
            }

            //std::cout << "New Response: '" << newResponse << "'" << std::endl;

            waitingForNextChunkSize = false;

        }

        if (!waitingForNextChunkSize)
        {

            //std::cout << "ChunkSize: " << chunkSize << ", received: " << received << std::endl;

            if (received <= chunkSize)
            {
                m_Response += newResponse;
            }

            if (received == chunkSize)
            {
                waitingForNextChunkSize = true;
            }
            else if (received > chunkSize)
            {
                //std::cout << "Received > ChunkSize, rec: " << received << ", chunksize: " << chunkSize << std::endl;

                //std::cout << "after (" << chunkSize << "): '" << newResponse.substr(chunkSize, std::string::npos) << "'" << std::endl;

                m_Response += newResponse.substr(0, chunkSize);

                if (newResponse.substr(chunkSize, std::string::npos) == "\r\n0\r\n\r\n")
                {
                    //std::cout << "WWWWWOOOOOO!" << std::endl;
                    return;
                }

                waitingForNextChunkSize = true;
            }
        }
    }
}

std::string HTTPSRequest::parseHeader(const std::vector<std::string>& _headerTokens)
{
    std::vector<std::string> responseCode = tokenise(_headerTokens[0], " ");

    if (responseCode.at(0).substr(0, 5) != "HTTP/")
    {
        std::cout << "Invalid http version." << std::endl;

        return "-1";
    }
    if (atol(responseCode.at(1).substr(0, 1).c_str()) != 2)
    {
        std::cout << "Non 2XX return code." << std::endl;

        std::cout << "Code: " << responseCode.at(1) << ", Comment: " << responseCode.at(2) << std::endl;

        return "-1";
    }

    for (unsigned int i = 1; i < _headerTokens.size(); i += 1)
    {
        responseCode = tokenise(_headerTokens[i], " ");

        if (responseCode.size() == 0)
        {
            break;
        }

        if (responseCode[0] == "Transfer-Encoding:")
        {
            if (responseCode[1] == "chunked")
            {
                m_Chunked = true;
            }
            else
            {
                std::cout << "Not Chunked Transfer-Encoding" << std::endl;
                m_Chunked = false;
                return "-1";
            }
        }
    }

    responseCode = tokenise(_headerTokens[_headerTokens.size() - 1], " ");

    return responseCode[0];
}

std::vector<std::string> HTTPSRequest::tokenise(const std::string& _data, const std::string& _delimeter)
{
    std::string data = _data;
    std::vector<std::string> tokens;

    size_t pos = 0;
    std::string token;


    while ((pos = data.find(_delimeter)) != std::string::npos)
    {
        token = data.substr(0, pos);
        data.erase(0, pos + _delimeter.length());

        tokens.push_back(token);
    }

    if (data.size() != 0)
    {
        tokens.push_back(data);
    }

    return tokens;
}

} //~ namespace zeno