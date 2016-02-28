#include <cstdlib>
#include <iostream>

#include <zeno/Utility/XML.hpp>

#include <zeno/Utility/JSON.hpp>

std::string enumToString(zeno::JSONNode::NodeType _type)
{
    switch (_type)
    {
        case zeno::JSONNode::NodeType::Array:
            return "Array";
        case zeno::JSONNode::NodeType::Value:
            return "Value";
        case zeno::JSONNode::NodeType::Object:
            return "Object";
        default:
            return "Not handled";
    }
}

void printValueNode(const zeno::JSONValueNode& _node)
{
    std::cout << "Node of type '" << enumToString(_node.getType()) << "' with key: '" << _node.getKey() << "'" << std::endl;
    std::cout << "As Bool: " << (_node.asBool() ? "True" : "False") << std::endl;
    std::cout << "As Int: '" << _node.asInt() << "'" << std::endl;
    std::cout << "As Double: '" << _node.asDouble() << "'" << std::endl;
    std::cout << "As String: '" << _node.asString() << "'" << std::endl;
}

int main(int _argc, char **_argv)
{
    //zeno::XML::Document d;
    //d.loadFromFile("C:/Users/Mark/Desktop/test.xml");

    //std::cout << d.dumpTree() << std::endl;

    zeno::JSON json;

    zeno::JSONValueNode n = zeno::JSONValueNode("Key", "25.654");

    printValueNode(n);

    return EXIT_SUCCESS;
}
