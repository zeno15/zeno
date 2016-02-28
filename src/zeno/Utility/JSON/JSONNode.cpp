#include <zeno/Utility/JSON/JSONNode.hpp>

namespace zeno {

    JSONNode::JSONNode(const std::string& _key, NodeType _type) :
    m_Key(_key),
    m_Type(_type)
    {

    }


    JSONNode::NodeType JSONNode::getType(void) const
    {
        return m_Type;
    }

    const std::string& JSONNode::getKey(void) const
    {
        return m_Key;
    }

} //~ namespace zeno