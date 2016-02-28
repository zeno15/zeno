#ifndef ZENO_UTILITY_JSON_JSONVALUENODE_HPP
#define ZENO_UTILITY_JSON_JSONVALUENODE_HPP

#include <zeno/Utility/JSON/JSONNode.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief  JSON Node that contains a single value
///
////////////////////////////////////////////////////////////
class JSONValueNode : public JSONNode
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Constructor
    ///
    /// \param  _key    String representing the Key for this node
    ///
    /// \param  _value  String representing the value for this node
    ///
    ////////////////////////////////////////////////////////////
    JSONValueNode(const std::string& _key, const std::string& _value);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Converts the string representation of the value
    ///         into a boolean and returns it
    ///
    /// \return Boolean representing the value of the Node
    ///
    ////////////////////////////////////////////////////////////
    bool asBool(void) const;
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Converts the string representation of the value
    ///         into an integer and returns it
    ///
    /// \return Integer representing the value of the Node
    ///
    ////////////////////////////////////////////////////////////
    int asInt(void) const;
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Converts the string representation of the value
    ///         into a double and returns it
    ///
    /// \return Double representing the value of the Node
    ///
    ////////////////////////////////////////////////////////////
    double asDouble(void) const;
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Returns the internal string representation of the
    ///         value
    ///
    /// \return String representing the value of the Node
    ///
    ////////////////////////////////////////////////////////////
    std::string asString(void) const;

private:
    std::string         m_Value;    ///<    String representing the value of the Node
};

} //~ namespace zeno

#endif //~ ZENO_UTILITY_JSON_JSONVALUENODE_HPP
