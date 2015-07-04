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

void XML::XMLNode::print(unsigned int _indentation)
{
    std::string indent(4 * _indentation, ' ');

    if (m_Type == NodeType::DECLARATION ||
        m_Type == NodeType::COMMENT ||
        m_Type == NodeType::CONTENT)
    {
        std::cout << indent << m_Content << std::endl;
    }

    if (m_Type == NodeType::ELEMENT)
    {
        std::cout << indent << "<" << m_Tag;

        for (std::pair<std::string, std::string>& pair : m_AttributePairs)
        {
            std::cout << " " << pair.first << "=\"" << pair.second << "\"";
        }

        std::cout << ">" << std::endl;
    }
    if (m_Type == NodeType::CLOSED_ELEMENT)
    {
        std::cout << indent << "<" << m_Tag;

        for (std::pair<std::string, std::string>& pair : m_AttributePairs)
        {
            std::cout << " " << pair.first << "=\"" << pair.second << "\"";
        }

        std::cout << "/>" << std::endl;
    }

    for (XMLNode *node : m_Nodes)
    {
        node->print(_indentation + 1);
    }

    if (m_Type == NodeType::ELEMENT)
    {
        std::cout << indent << "</" << m_Tag << ">" << std::endl;
    }
}

XMLNode *XML::XMLNode::getChild(const std::string& _tagName)
{
    
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

    return m_Root.create(_data);
}

void XML::printTree(void)
{
    m_Root.print(0);
}

bool XML::addComment(const std::string& _comment, const std::string& _path /*= "/"*/, unsigned int _index /*= -1*/)
{
    std::vector<std::string> pathVector = splitStringByString(_path, "/");

    std::cout << "Path '" << _path << "' split has length: " << pathVector.size() << std::endl;
    for (std::string str : pathVector)
    {
        std::cout << "Path: " << str << std::endl;
    }

    return false;
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