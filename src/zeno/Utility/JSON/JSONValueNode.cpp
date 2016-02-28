#include <zeno/Utility/JSON/JSONValueNode.hpp>

#include <zeno/Utility/StringMethods.hpp>

namespace zeno {

JSONValueNode::JSONValueNode(const std::string& _key, const std::string& _value) :
JSONNode(_key, JSONNode::NodeType::Value),
m_Value(_value)
{

}

bool JSONValueNode::asBool(void) const
{
    return compareCaseInsensitive("TRUE", m_Value);
}
int JSONValueNode::asInt(void) const
{
    return std::stoi(m_Value, nullptr, 10);
}
double JSONValueNode::asDouble(void) const
{
    return std::stod(m_Value, nullptr);
}
std::string JSONValueNode::asString(void) const
{
    return m_Value;
}

} //~ namespace zeno