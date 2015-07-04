#ifndef INCLUDED_ZENO_UTILITY_XML_HPP
#define INCLUDED_ZENO_UTILITY_XML_HPP

#include <string>
#include <vector>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief	Class to implement basic XML creation/parsing
///
////////////////////////////////////////////////////////////
class XML
{
private:
    class XMLNode
    {
    public:
        enum NodeType {
            DECLARATION,
            COMMENT,
            CONTENT,
            ELEMENT,
            CLOSED_ELEMENT
        };

        void clear(void);

        bool create(const std::string& _data);

        void print(unsigned int _indentation);

        unsigned int getNumChildren(void)
        {
            return m_Nodes.size();
        }

        XMLNode *getChild(const std::string& _tagName);

    public:
        std::vector<XMLNode *>      m_Nodes;

        NodeType                    m_Type;

        //~ Used for element and closed element
        std::string                 m_Tag;

        std::vector<std::pair<std::string, std::string>>    m_AttributePairs;

        //~ Used for content node, declaration and comment node
        std::string                 m_Content;
    };



public:
    ~XML(void);

    bool loadFromFile(const std::string& _filename);

    bool createTree(const std::string& _data);

    void printTree(void);

    bool addComment(const std::string& _comment, const std::string& _path = "/", unsigned int _index = -1);

private:
    static bool extractFromBetweenTag(const std::string& _tag, std::string& _extracted, std::string& _data);

    static bool extractAttributesFromElement(const std::string& _element, XMLNode *node);

private:
    XMLNode     m_Root;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_UTILITY_XML_HPP