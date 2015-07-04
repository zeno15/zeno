#include <zeno/Utility/XML.hpp>

#include <zeno/Utility/StringMethods.hpp>

#include <fstream>
#include <iostream>

#define DECLARATION_START       "<?"
#define DECLARATION_END         "?>"
#define COMMENT_START           "<!--"
#define COMMENT_END             "-->"
#define CLOSED_ELEMENT_START    "<"
#define CLOSED_ELEMENT_END      "/>"

namespace zeno {

void XML::XMLNode::clear(void)
{
    for (XMLNode *node : m_Nodes)
    {
        node->clear();

        delete node;
    }

    m_Nodes.clear();
}

bool XML::XMLNode::create(const std::string& _data)
{
    std::string data = _data;

    while (data.size())
    {
        std::size_t startLoc = data.find('<');
        std::size_t closeLoc = data.find('>');

        if (startLoc == std::string::npos)
        {
            //~ Either _data is pure content, or an error has occured
            //~ Assume content

            data = stripLeadingWhitespace(data);

            if (data.size())
            {
                XMLNode *node = new XMLNode();

                node->m_Type = NodeType::CONTENT;
                node->m_Content = data;

                m_Nodes.push_back(node);
            }

            return true;
        }

        if (closeLoc == std::string::npos)
        {
            std::cout << "Found close < without open >: poorly formatted xml" << std::endl;
            return false;
        }

        std::string element = data.substr(startLoc, closeLoc - startLoc + 1);

        if (startsWith(element, DECLARATION_START) && endsWith(element, DECLARATION_END))
        {
            //~ TODO extract declaration from element

            XMLNode *node = new XMLNode();

            node->m_Type = NodeType::DECLARATION;
            node->m_Content = element;

            m_Nodes.push_back(node);

            data = data.substr(data.find('<', closeLoc), std::string::npos);
        }
        else if (startsWith(element, COMMENT_START) && endsWith(element, COMMENT_END))
        {
            //~ TODO extract comment from element

            XMLNode *node = new XMLNode();

            node->m_Type = NodeType::COMMENT;
            node->m_Content = element;

            m_Nodes.push_back(node);

            data = data.substr(data.find('<', closeLoc), std::string::npos);
        }
        else if (startsWith(element, CLOSED_ELEMENT_START) && endsWith(element, CLOSED_ELEMENT_END))
        {
            data = data.substr(data.find('<', closeLoc), std::string::npos);

            std::size_t loc = element.find_first_of("> ");
            std::string tag = element.substr(1, loc - 1);

            XMLNode *node = new XMLNode();

            node->m_Tag = tag;
            node->m_Type = NodeType::CLOSED_ELEMENT;

            if (!extractAttributesFromElement(element, node))
            {
                std::cout << "Closed element failed to extract attributes" << std::endl;
                return false;
            }

            m_Nodes.push_back(node);
        }
        else
        {
            std::size_t loc = element.find_first_of("> ");
            std::string tag = element.substr(1, loc - 1);

            std::string extracted;

            if (!extractFromBetweenTag(tag, extracted, data))
            {
                std::cout << "Could not extract data from between the '<" << tag << ">' tag." << std::endl;

                return false;
            }
            else
            {
                XMLNode *node = new XMLNode();

                if (!node->create(extracted))
                {
                    return false;
                }

                node->m_Tag = tag;
                node->m_Type = NodeType::ELEMENT;

                if (!extractAttributesFromElement(element, node))
                {
                    std::cout << "Element failed to extract attributes" << std::endl;
                    return false;
                }

                m_Nodes.push_back(node);
            }
        }

    }

    return true;
}


std::string XML::XMLNode::writeToString(unsigned int _indentation)
{
    std::string output;

    std::string indent(4 * _indentation, ' ');

    if (m_Type == NodeType::DECLARATION ||
        m_Type == NodeType::COMMENT ||
        m_Type == NodeType::CONTENT)
    {
        output += (indent + m_Content + "\n");
    }
    if (m_Type == NodeType::ELEMENT)
    {
        output += (indent + "<" + m_Tag);

        for (std::pair<std::string, std::string>& pair : m_AttributePairs)
        {
            //~ TODO Check if pair.second contains ", if so use 'pair.second'
            output += (" " + pair.first + "=\"" + pair.second + "\"");
        }

        output += (">\n");
    }
    if (m_Type == NodeType::CLOSED_ELEMENT)
    {
        output += (indent + "<" + m_Tag);

        for (std::pair<std::string, std::string>& pair : m_AttributePairs)
        {
            //~ TODO Check if pair.second contains ", if so use 'pair.second'
            output += (" " + pair.first + "=\"" + pair.second + "\"");
        }

        output += ("/>\n");
    }

    for (XMLNode *node : m_Nodes)
    {
        output += node->writeToString(_indentation + 1);
    }

    if (m_Type == NodeType::ELEMENT)
    {
        //std::cout << indent << "</" << m_Tag << ">" << std::endl;
        output += (indent + "</" + m_Tag + ">\n");
    }

    return output;
}

XML::XMLNode *XML::XMLNode::getChild(const std::string& _tagName, int _index /*= -1*/)
{
    int count = 0;

    for (XMLNode *node : m_Nodes)
    {
        if (node->m_Tag == _tagName)
        {
            if (count == _index || _index == -1)
            {
                return node;
            }

            count += 1;
        }
    }

    return nullptr;
}


XML::~XML(void)
{
    m_Root.clear();
}


bool XML::loadFromFile(const std::string& _filename)
{
    std::ifstream file;
    file.open(_filename);

    if (!file.good())
    {
        std::cout << "Failed to load XML file: " << _filename << std::endl;
        return false;
    }

    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned int>(file.tellg()));
    file.seekg(0, std::ios::beg);

    str.insert(str.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    bool outcome = createTree(str);

    if (!outcome)
    {
        std::cout << "Failed to build xml tree." << std::endl;
    }

    file.close();

    return outcome;
}

bool XML::createTree(const std::string& _data)
{
    m_Root.clear();

    bool val = m_Root.create(_data);

    m_Root.m_Type = XMLNode::NodeType::ROOT;

    return val;
}

void XML::printTree(void)
{
    std::cout << writeToString();
}

bool XML::addComment(const std::string& _comment, const std::string& _path /*= "/"*/, std::vector<int> _index /* = std::vector<int>()*/)
{
    //~ TODO remove this common code from the various addXXX methods
    std::vector<std::string> pathVector = splitStringByString(_path, "/");

    XMLNode *node = &m_Root;

    if (_index.size() == 0)
    {
        _index = std::vector<int>(pathVector.size(), -1);
    }
    if (_index.size() != pathVector.size())
    {
        std::cout << "Incorrectly sized index vector" << std::endl;
        return false;
    }


    for (unsigned int i = 0; i < pathVector.size(); i += 1)
    {
        if (node->getChild(pathVector.at(i), _index.at(i)) != nullptr)
        {
            node = node->getChild(pathVector.at(i), _index.at(i));
        }
        else
        {
            std::cout << "Could not get desired node" << std::endl;
            return false;
        }
    }

    XMLNode *newNode = new XMLNode();
    newNode->m_Type = XMLNode::NodeType::COMMENT;
    newNode->m_Content = "<!--" + _comment + "-->";

    node->m_Nodes.insert(node->m_Nodes.begin(), newNode);

    return true;
}
bool XML::addContent(const std::string& _content, const std::string& _path /*= "/"*/, std::vector<int> _index /*= std::vector<int>()*/)
{
    std::vector<std::string> pathVector = splitStringByString(_path, "/");

    XMLNode *node = &m_Root;

    if (_index.size() == 0)
    {
        _index = std::vector<int>(pathVector.size(), -1);
    }
    if (_index.size() != pathVector.size())
    {
        std::cout << "Incorrectly sized index vector" << std::endl;
        return false;
    }


    for (unsigned int i = 0; i < pathVector.size(); i += 1)
    {
        if (node->getChild(pathVector.at(i), _index.at(i)) != nullptr)
        {
            node = node->getChild(pathVector.at(i), _index.at(i));
        }
        else
        {
            std::cout << "Could not get desired node" << std::endl;
            return false;
        }
    }

    XMLNode *newNode = new XMLNode();
    newNode->m_Type = XMLNode::NodeType::CONTENT;
    newNode->m_Content = _content;

    node->m_Nodes.push_back(newNode);

    return true;
}
bool XML::addElement(const std::string& _tag,
                     const std::vector<std::pair<std::string, std::string>>& _attributes /*= std::vector<std::pair<std::string, std::string>>()*/,
                     const std::string& _path /*= "/"*/,
                     std::vector<int> _index /*= std::vector<int>()*/)

{
    std::vector<std::string> pathVector = splitStringByString(_path, "/");

    XMLNode *node = &m_Root;

    if (_index.size() == 0)
    {
        _index = std::vector<int>(pathVector.size(), -1);
    }
    if (_index.size() != pathVector.size())
    {
        std::cout << "Incorrectly sized index vector" << std::endl;
        return false;
    }


    for (unsigned int i = 0; i < pathVector.size(); i += 1)
    {
        if (node->getChild(pathVector.at(i), _index.at(i)) != nullptr)
        {
            node = node->getChild(pathVector.at(i), _index.at(i));
        }
        else
        {
            std::cout << "Could not get desired node" << std::endl;
            return false;
        }
    }
    XMLNode *newNode = new XMLNode();
    newNode->m_Type = XMLNode::NodeType::ELEMENT;
    newNode->m_Tag = _tag;
    for (auto& pair : _attributes)
    {
        newNode->m_AttributePairs.push_back(pair);
    }

    node->m_Nodes.push_back(newNode);

    return true;
}
bool XML::addClosedElement(const std::string& _tag,
                           const std::vector<std::pair<std::string, std::string>>& _attributes /*= std::vector<std::pair<std::string, std::string>>()*/,
                           const std::string& _path /*= "/"*/,
                           std::vector<int> _index /*= std::vector<int>()*/)
{
    std::vector<std::string> pathVector = splitStringByString(_path, "/");

    XMLNode *node = &m_Root;

    if (_index.size() == 0)
    {
        _index = std::vector<int>(pathVector.size(), -1);
    }
    if (_index.size() != pathVector.size())
    {
        std::cout << "Incorrectly sized index vector" << std::endl;
        return false;
    }


    for (unsigned int i = 0; i < pathVector.size(); i += 1)
    {
        if (node->getChild(pathVector.at(i), _index.at(i)) != nullptr)
        {
            node = node->getChild(pathVector.at(i), _index.at(i));
        }
        else
        {
            std::cout << "Could not get desired node" << std::endl;
            return false;
        }
    }
    XMLNode *newNode = new XMLNode();
    newNode->m_Type = XMLNode::NodeType::CLOSED_ELEMENT;
    newNode->m_Tag = _tag;
    for (const std::pair<std::string, std::string>& pair : _attributes)
    {
        newNode->m_AttributePairs.push_back(pair);
    }

    node->m_Nodes.push_back(newNode);

    return true;
}
bool XML::addDeclaration(const std::string& _declaration)
{
    XMLNode *newNode = new XMLNode();
    newNode->m_Type = XMLNode::NodeType::DECLARATION;
    newNode->m_Content = "<?" + _declaration + "?>";

    m_Root.m_Nodes.insert(m_Root.m_Nodes.begin(), newNode);

    return true;
}

std::string XML::writeToString(void)
{
    std::string output;

    for (XMLNode *node : m_Root.m_Nodes)
    {
        output += node->writeToString(0);
    }

    return output;
}
bool XML::writeToFile(const std::string& _filename)
{
    std::ofstream output;
    output.open(_filename);
    if (!output.good())
    {
        return false;
    }

    output << (writeToString());

    output.close();

    return true;
}

bool XML::extractFromBetweenTag(const std::string& _tag, std::string& _extracted, std::string& _data)
{
    std::size_t loc = _data.find(std::string("<" + _tag));

    if (loc == std::string::npos) {
        return false;
    }

    std::size_t nextTagLoc = _data.find('<', loc + _tag.size());

    if (nextTagLoc == _data.find(std::string("</" + _tag + ">")))
    {

        std::size_t openEnd = _data.find('>');
        std::size_t closeStart = _data.find("</");

        _extracted = _data.substr(openEnd + 1, closeStart - openEnd - 1);
    }
    else
    {
        _extracted = _data.substr(nextTagLoc, std::string::npos);

        _extracted = _extracted.substr(0, _extracted.find(std::string("</" + _tag + ">")));
    }

    _data = _data.substr(_data.find(std::string("</" + _tag + ">")) + 3 + _tag.size(), std::string::npos);

    return true;
}

bool XML::extractAttributesFromElement(const std::string& _element, XMLNode *node)
{
    std::string element(_element);

    std::size_t equalLoc = element.find('=');

    while (equalLoc != std::string::npos)
    {
        std::size_t attribStart = element.find_last_of(" ", equalLoc);

        std::string attrib = element.substr(attribStart + 1, equalLoc - attribStart - 1);

        std::size_t endValueLoc = element.find(element[equalLoc + 1], equalLoc + 2);

        std::string value = element.substr(equalLoc + 2, endValueLoc - equalLoc - 2);

        element = element.substr(endValueLoc, std::string::npos);

        node->m_AttributePairs.push_back(std::pair<std::string, std::string>(attrib, value));

        equalLoc = element.find('=');
    }

    return true;
}

} //~ namespace zeno