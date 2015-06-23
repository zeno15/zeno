#ifndef ZENO_NETWORK_HTTPPROTOCOL_HPP
#define ZENO_NETWORK_HTTPPROTOCOL_HPP

#include <string>
#include <vector>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief  Collection of classes to allow for making
///         http requests
///
////////////////////////////////////////////////////////////
class HTTPProtocol
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Class representing an http request
    ///
    ////////////////////////////////////////////////////////////
    class Request
    {
    public:
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Enumeration of supported http request types
        ///
        ////////////////////////////////////////////////////////////
        enum RequestType {
            GET,        ///<
            HEAD,       ///<
            POST        ///<
        };

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Constructor
        ///
        /// Defaualts to an http GET request
        ///
        /// \param  _type   http request type
        ///
        ////////////////////////////////////////////////////////////
        Request(RequestType _type = RequestType::GET);

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the http request type
        ///
        /// \return std::string representing the http request type
        ///
        ////////////////////////////////////////////////////////////
        std::string getRequestType(void) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the Major http version of the Request
        ///
        /// \return Major http version number
        ///
        ////////////////////////////////////////////////////////////
        unsigned int getMajorVersion(void) const;
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the Minor http version of the Request
        ///
        /// \return Minor http version number
        ///
        ////////////////////////////////////////////////////////////
        unsigned int getMinorVersion(void) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Adds a field and value to the Request, if already
        ///         present, updates the value
        ///
        /// \param  _field  http request field
        ///
        /// \param  _value  http request value corresponding to \a _field
        ///
        ////////////////////////////////////////////////////////////
        void addField(const std::string& _field, const std::string& _value);

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets whether the Response has a given field
        ///
        /// \param  _field  Field to look for
        ///
        /// \return Boolean whether the given \a _field is present
        ///
        ////////////////////////////////////////////////////////////
        bool hasField(const std::string& _field) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the value associated with a field
        ///
        /// \param  _field  Field to get value of
        ///
        /// \return std::string value of the given \a _field
        ///
        ////////////////////////////////////////////////////////////
        std::string getFieldValue(const std::string& _field) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets read only access to the fields of the Response
        ///
        /// \return Reference to the vector of field-value pairs
        ///
        ////////////////////////////////////////////////////////////
        const std::vector<std::pair<std::string, std::string>>& getFields(void) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Sets the desired URI of the Request
        ///
        /// \param  _uri    Desired URI
        ///
        ////////////////////////////////////////////////////////////
        void setURI(const std::string& _uri);

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the desired URI of the Request
        ///
        /// \return std::string representing the desired URI
        ///
        ////////////////////////////////////////////////////////////
        std::string getURI(void) const;

    private:
        RequestType         m_Type;                                         ///<    HTTP request type

        std::string         m_URI;                                          ///<    Desired URI

        std::vector<std::pair<std::string, std::string>>        m_Fields;   ///<    Fields and values in the response

        unsigned int            m_MajorVersionNumber;                       ///<    Major http version of the response
        unsigned int            m_MinorVersionNumber;                       ///<    Minor http version of the response
    };

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Class containing a response from an http request
    ///
    ////////////////////////////////////////////////////////////
    class Response
    {
    public:
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets read only access to the fields of the Response
        ///
        /// \return Reference to the vector of field-value pairs
        ///
        ////////////////////////////////////////////////////////////
        const std::vector<std::pair<std::string, std::string>>& getFields(void) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets whether the Response has a given field
        ///
        /// \param  _field  Field to look for
        ///
        /// \return Boolean whether the given \a _field is present
        ///
        ////////////////////////////////////////////////////////////
        bool hasField(const std::string& _field) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the value associated with a field
        ///
        /// \param  _field  Field to get value of
        ///
        /// \return std::string value of the given \a _field
        ///
        ////////////////////////////////////////////////////////////
        std::string getFieldValue(const std::string& _field) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the body of the response
        ///
        /// \return std::string representing body of http Response
        ///
        ////////////////////////////////////////////////////////////
        std::string getBody(void) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the Major http version of the Response
        ///
        /// \return Major http version number
        ///
        ////////////////////////////////////////////////////////////
        unsigned int getMajorVersion(void) const;
        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the Minor http version of the Response
        ///
        /// \return Minor http version number
        ///
        ////////////////////////////////////////////////////////////
        unsigned int getMinorVersion(void) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Gets the status code of the Response
        ///
        /// \return Status code of the http Response
        ///
        ////////////////////////////////////////////////////////////
        unsigned int getStatus(void) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief  Internal method to parse the raw response into
        ///         useable Response format
        ///
        /// \param  _responseString std::string containing entire
        ///         response from host
        ///
        ////////////////////////////////////////////////////////////
        void parseResponseString(const std::string& _responseString);
    private:
        std::vector<std::pair<std::string, std::string>>        m_Fields;   ///<    Fields and values in the response

        unsigned int            m_MajorVersionNumber;                       ///<    Major http version of the response
        unsigned int            m_MinorVersionNumber;                       ///<    Minor http version of the response

        unsigned int            m_StatusCode;                               ///<    Status code of the response

        std::string m_Body;                                                 ///<    Body of the response
    };


    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the host and port to be used for any
    ///         following requests.
    ///
    ///         Host is in the form:
    ///         http(s)://www.website.com
    ///
    /// \param  _host   Host to use for http request
    ///
    /// \param  _port   Port number to use, defaults to 80 for
    ///                 http and 443 for https
    ///
    ////////////////////////////////////////////////////////////
    void setHost(const std::string& _host, unsigned int _port = 0);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Make a request using the given Request object
    ///         and return a Response object
    ///
    /// \param  _request    Request object to make http request
    ///                     from
    ///
    /// \return Response representing the servers response to
    ///         \a _request
    ///
    ////////////////////////////////////////////////////////////
    HTTPProtocol::Response makeRequest(const HTTPProtocol::Request& _request);

private:
    unsigned int            m_Port;     ///<    Port the request will use

    std::string             m_Host;     ///<    Host for the request

    bool                    m_HTTPS;    ///<    Whether or not the host is behind https
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
/// for (const std::pair<std::string, std::string>& pair : response.getFields())
/// {
///     std::cout << pair.first << ": " << pair.second << std::endl;
/// }
///
/// std::cout << response.getBody() << std::endl;
///
///	\endcode
///
////////////////////////////////////////////////////////////