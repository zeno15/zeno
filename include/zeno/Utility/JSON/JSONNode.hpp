#ifndef ZENO_UTILITY_JSON_JSONNODE_HPP
#define ZENO_UTILITY_JSON_JSONNODE_HPP

#include <string>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief  Base class for different value type JSON nodes
///
////////////////////////////////////////////////////////////
class JSONNode
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief   Enumeration of possible node types in JSON file
    ///
    ////////////////////////////////////////////////////////////
    enum NodeType {
        Value,      ///<    Node representing a string/boolean/number
        Array,      ///<    Node representing an array of JSONNode's
        Object      ///<
    };

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Constructor
    ///
    /// \param  _key    string representing the key for the node
    ///
    /// \param  _type   NodeType representing the type of the node
    ///
    ////////////////////////////////////////////////////////////
    JSONNode(const std::string& _key, NodeType _type);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the type of JSONNode this node is
    ///
    /// \return NodeType representing the type of the node
    ///
    ////////////////////////////////////////////////////////////
    NodeType getType(void) const;

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the Key of the JSONNode
    ///
    /// \return string representing the Key of the JSONNode
    ///
    ////////////////////////////////////////////////////////////
    const std::string& getKey(void) const;

protected:
    std::string             m_Key;      ///<    Key of the Node
    NodeType                m_Type;     ///<    Type of the Node

};

} //~ namespace zeno

#endif //~ ZENO_UTILITY_JSON_JSONNODE_HPP
