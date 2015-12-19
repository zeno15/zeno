#include <zeno/Utility/XML.hpp>

#include <zeno/Utility/StringMethods.hpp>

#include <fstream>
#include <iostream>


static const char OpenTag = '<';
static const char CloseTag = '>';
static const char NewLine = '\n';
static const char ForwardSlash = '/';
static const char Exclaimation = '!';
static const char Question = '?';
static const char Space = ' ';
static const char Equals = '=';
static const char DoubleQuote = '"';
static const char SingleQuote = '\'';

static const std::string CommentSequenceOpen = "<!--";
static const std::string CommentSequenceClose = "-->";

namespace zeno {

    XML::XML(void)
    {
        /*m_TagDeclarationMethod = [](const std::string& _declarationString)
        {
            std::cout << "Func Encountered declaration tag: '" << _declarationString << "'" << std::endl;
        };
        m_TagCloseMethod = [](const std::string& _tagString)
        {
            std::cout << "Func Encountered closing tag: '" << _tagString << "'" << std::endl;
        };
        m_ContentMethod = [](const std::string& _content)
        {
            std::cout << "Func Encountered content: '" << _content << "'" << std::endl;
        };
        m_CommentMethod = [](const std::string& _comment)
        {
            std::cout << "Func Encountered a comment: '" << _comment << "'" << std::endl;
        };
        m_TagOpenMethod = [](const std::string& _tagString, const std::vector<std::pair<std::string, std::string>> _attirbutes)
        {
            std::cout << "Func Encountered opening tag: '" << _tagString << "'";
            for (const auto& p : _attirbutes)
            {
                std::cout << " " << p.first << "=\"" << p.second << "\"";
            }
            std::cout << std::endl;
        };
        m_TagSelfCloseMethod = [](const std::string& _tagString, const std::vector<std::pair<std::string, std::string>> _attirbutes)
        {
            std::cout << "Func Encountered self closing tag: '" << _tagString << "'";
            for (const auto& p : _attirbutes)
            {
                std::cout << " " << p.first << "=\"" << p.second << "\"";
            }
            std::cout << std::endl;
        };*/
    }

    void XML::loadFromFile(const std::string &_filename)
    {
        std::ifstream input(_filename);

        while (input.good())
        {
            readTag(input);
            readContent(input);
        }

        input.close();
    }

    void XML::setDeclarationTagCallback(std::function<void(const std::string&, const std::vector<std::pair<std::string, std::string>>)> _method)
    {
        m_TagDeclarationMethod = _method;
    }
    void XML::setClosingTagCallback(std::function<void(const std::string&)> _method)
    {
        m_TagCloseMethod = _method;
    }
    void XML::setContentCallback(std::function<void(const std::string&)> _method)
    {
        m_ContentMethod = _method;
    }
    void XML::setCommentTagCallback(std::function<void(const std::string&)> _method)
    {
        m_CommentMethod = _method;
    }
    void XML::setOpeningTagCallback(std::function<void(const std::string&, const std::vector<std::pair<std::string, std::string>>)> _method)
    {
        m_TagOpenMethod = _method;
    }
    void XML::setSelfClosingTagCallback(std::function<void(const std::string&, const std::vector<std::pair<std::string, std::string>>)> _method)
    {
        m_TagSelfCloseMethod = _method;
    }

    XML::Node::Node(NodeType _type, Node *_parent, bool _selfClosing /*= false*/) :
    m_Type(_type),
    m_Parent(_parent),
    m_IsSelfClosing(_selfClosing)
    {
    }

    XML::NodeType XML::Node::getType(void) const
    {
        return m_Type;
    }

    std::string XML::Node::toString(unsigned int indentation) const
    {
        std::string nodeString;
        std::string indentationStr;
        for (unsigned int i = 0; i < indentation * 4; i += 1)
        {
            indentationStr += ' ';
        }

        switch (m_Type)
        {
            case NodeType::Declaration:
                nodeString += indentationStr + "<?" + m_Tag;
                for (const auto& p : m_Attributes)
                {
                    nodeString += " " + p.first + ": \"" + p.second + "\"";
                }
                nodeString += "?>\n";
                break;
            case NodeType::Comment:
                nodeString += indentationStr + "<!--" + m_Content + "-->\n";
                break;
            case NodeType::Content:
                nodeString += indentationStr + m_Content + "\n";
                break;
            case NodeType::Regular:
                nodeString += indentationStr + "<" + m_Tag;
                for (const auto& p : m_Attributes)
                {
                    nodeString += " " + p.first + ":\"" + p.second + "\"";
                }
                if (m_IsSelfClosing)
                {
                    nodeString += "/>\n";
                }
                else
                {
                    nodeString += ">\n";

                    for (Node *child : m_ChildNodes)
                    {
                        nodeString += child->toString(indentation + 1);
                    }

                    nodeString += indentationStr + "</" + m_Tag + ">\n";
                }
                break;
            default:
                throw new std::runtime_error("Invalid node type");
        }

        return nodeString;
    }

    void XML::Node::setTag(const std::string& _tag)
    {
        m_Tag = _tag;
    }
    void XML::Node::setContent(const std::string& _content)
    {
        m_Content = _content;
    }
    void XML::Node::addAttribute(const std::string& _key, const std::string& _value)
    {
        m_Attributes.push_back(std::pair<std::string, std::string>(_key, _value));
    }

    std::string XML::Node::getTag(void) const
    {
        return m_Tag;
    }
    std::string XML::Node::getContent(void) const
    {
        return m_Content;
    }
    std::vector<std::pair<std::string, std::string>> XML::Node::getAttributes(void) const
    {
        return m_Attributes;
    }
    XML::Node *XML::Node::getParent(void) const
    {
        return m_Parent;
    }

    bool XML::Node::isSelfClosing(void) const
    {
        return m_IsSelfClosing;
    }

    void XML::Node::addChild(Node *_node)
    {
        m_ChildNodes.push_back(_node);
    }

    XML::Document::Document(void) :
    m_CurrentNode(nullptr)
    {
        Node *dec = new Node(NodeType::Declaration, nullptr);

        dec->setTag("xml");
        dec->addAttribute("version", "1.0");

        m_Nodes.push_back(dec);
    }

    void XML::Document::loadFromFile(const std::string& _filename)
    {
        XML xml;

        xml.setDeclarationTagCallback([&](const std::string& _declarationTag, const std::vector<std::pair<std::string, std::string>>& _attributes){
            this->addDeclarationStream(_declarationTag, _attributes);
        });
        xml.setOpeningTagCallback([&](const std::string& _tag, const std::vector<std::pair<std::string, std::string>>& _attributes){
            this->addOpeningTag(_tag, _attributes);
        });
        xml.setCommentTagCallback([&](const std::string& _comment){
            this->addCommentStream(_comment);
        });
        xml.setContentCallback([&](const std::string& _content){
            this->addContentStream(_content);
        });
        xml.setClosingTagCallback([&](const std::string& _tag){
           this->addClosingTag(_tag);
        });

        xml.loadFromFile(_filename);
    }

    void XML::Document::addCommentStream(const std::string& _comment)
    {
        Node *commentNode = new Node(NodeType::Comment, m_CurrentNode);

        commentNode->setContent(_comment);

        if (m_CurrentNode == nullptr)
        {
            m_Nodes.push_back(commentNode);
        }
        else
        {
            m_CurrentNode->addChild(commentNode);
        }
    }
    void XML::Document::addContentStream(const std::string& _content)
    {
        Node *contentNode = new Node(NodeType::Content, m_CurrentNode);

        contentNode->setContent(_content);

        if (m_CurrentNode == nullptr)
        {
            m_Nodes.push_back(contentNode);
        }
        else
        {
            m_CurrentNode->addChild(contentNode);
        }
    }
    void XML::Document::addDeclarationStream(const std::string& _declarationTag, const std::vector<std::pair<std::string, std::string>>& _attributes)
    {
        for (Node *node : m_Nodes)
        {
            if (node->getType() == NodeType::Declaration)
            {
                delete node;
                node = new Node(NodeType::Declaration, nullptr);
                node->setTag(_declarationTag);
                for (const auto& p : _attributes)
                {
                    node->addAttribute(p.first, p.second);
                }
                return;
            }
        }


        Node *node = new Node(NodeType::Declaration, nullptr);
        node->setTag(_declarationTag);
        for (const auto& p : _attributes)
        {
            node->addAttribute(p.first, p.second);
        }

        m_Nodes.push_back(node);
    }
    void XML::Document::addOpeningTag(const std::string& _tag, const std::vector<std::pair<std::string, std::string>>& _attributes, bool _isSelfClosing /*= false*/)
    {
        Node *openingNode = new Node(NodeType::Regular, m_CurrentNode);

        openingNode->setTag(_tag);
        for (const auto p : _attributes)
        {
            openingNode->addAttribute(p.first, p.second);
        }

        if (m_CurrentNode == nullptr)
        {
            m_Nodes.push_back(openingNode);
        }
        else
        {
            m_CurrentNode->addChild(openingNode);
        }

        if (!_isSelfClosing)
        {
            m_CurrentNode = openingNode;
        }
    }
    void XML::Document::addClosingTag(const std::string& _tag)
    {
        if (_tag != m_CurrentNode->getTag())
        {
            std::string error = "Got closing tag of '" + _tag + "' and current node is '" + m_CurrentNode->getTag() + "'";
            throw std::runtime_error(error);
        }

        m_CurrentNode = m_CurrentNode->getParent();
    }

    std::string XML::Document::dumpTree(void) const
    {
        std::string tree;

        for (Node *node : m_Nodes)
        {
            tree += node->toString(0);
        }

        return tree;
    }

    void XML::readTag(std::ifstream& _input)
    {
        std::string tag;

        bool running = true;
        bool withinTag = false;
        bool withinComment = false;

        while (running)
        {
            if (!_input.good())
            {
                return;
            }

            switch (_input.peek())
            {
                case OpenTag:
                    tag += _input.get();
                    withinTag = true;
                    if (_input.peek() == Exclaimation)
                    {
                        withinComment = true;
                    }
                    break;
                case CloseTag:
                    tag += _input.get();
                    running = false;
                    break;
                case NewLine:
                    if (!withinComment)
                    {
                        _input.get();
                    }
                    break;
                default:
                    if (withinTag) {
                        tag += _input.get();
                    }
                    else {
                        _input.get();
                    }
                    break;
            }
        }

        handleGenericTag(tag);
    }

    void XML::readContent(std::ifstream& _input)
    {
        std::string content;

        while (_input.good() && _input.peek() != OpenTag)
        {
            unsigned int c = _input.get();

            if (c != std::numeric_limits<unsigned int>().max())
            {
                content += c;
            }
        }

        trim(content);

        if (!content.size())
        {
            return;
        }

        handleContent(content);
    }

    void XML::handleContent(std::string& _content)
    {
        if (m_ContentMethod)
        {
            m_ContentMethod(_content);
        }
    }

    void XML::handleGenericTag(const std::string& _tag)
    {

        std::size_t slashLoc = _tag.find(ForwardSlash);
        std::size_t exclaimLoc = _tag.find(Exclaimation);
        std::size_t questionLoc = _tag.find(Question);

        if (questionLoc == 1)
        {
            parseDeclaration(_tag);
        }
        else if (exclaimLoc == 1)
        {
            parseCommentTag(_tag);
        }
        else if (slashLoc == std::string::npos)
        {
            parseOpeningTag(_tag);
        }
        else if (slashLoc == 1)
        {
            parseClosingTag(_tag);
        }
        else if (slashLoc == _tag.size() - 2)
        {
            parseSelfClosingTag(_tag);
        }
        else
        {
            throw std::invalid_argument("Unhadled XML tag type: '" + _tag + "'");
        }
    }

    void XML::parseDeclaration(const std::string& _declarationTag)
    {
        std::size_t startIndex = _declarationTag.find(OpenTag);
        std::size_t closeIndex = std::min(_declarationTag.find(Space), _declarationTag.find(CloseTag));

        std::string tagName = _declarationTag.substr(startIndex + 2, closeIndex - startIndex - 2);

        std::string attributes = _declarationTag.substr(closeIndex - startIndex, _declarationTag.find(CloseTag) - (closeIndex - startIndex));

        auto a = extractAttributes(attributes);

        if (m_TagDeclarationMethod)
        {
            m_TagDeclarationMethod(tagName, a);
        }
    }
    void XML::parseCommentTag(const std::string& _commentTag)
    {
        std::size_t startLocation = _commentTag.find(CommentSequenceOpen);
        std::size_t closeLocation = _commentTag.find(CommentSequenceClose);

        std::string comment = _commentTag.substr(startLocation + CommentSequenceOpen.size(), closeLocation - startLocation - CommentSequenceOpen.size());

        trim(comment);

        if (m_CommentMethod)
        {
            m_CommentMethod(comment);
        }
    }
    void XML::parseOpeningTag(const std::string& _openingTag)
    {
        std::size_t startIndex = _openingTag.find(OpenTag);
        std::size_t closeIndex = std::min(_openingTag.find(Space), _openingTag.find(CloseTag));

        std::string tagName = _openingTag.substr(startIndex + 1, closeIndex - startIndex - 1);

        std::string attributes = _openingTag.substr(closeIndex - startIndex, _openingTag.find(CloseTag) - (closeIndex - startIndex));

        auto a = extractAttributes(attributes);

        if (m_TagOpenMethod)
        {
            m_TagOpenMethod(tagName, a);
        }
    }
    void XML::parseClosingTag(const std::string& _closingTag)
    {
        std::size_t startIndex = _closingTag.find(ForwardSlash);
        std::size_t closeIndex = _closingTag.find(CloseTag);

        std::string tagName = _closingTag.substr(startIndex + 1, closeIndex - startIndex - 1);

        if (m_TagCloseMethod)
        {
            m_TagCloseMethod(tagName);
        }
    }
    void XML::parseSelfClosingTag(const std::string& _selfClosingTag)
    {
        std::size_t startIndex = _selfClosingTag.find(OpenTag);
        std::size_t closeIndex = std::min(_selfClosingTag.find(Space), _selfClosingTag.find(ForwardSlash));

        std::string tagName = _selfClosingTag.substr(startIndex + 1, closeIndex - startIndex - 1);

        std::string attributes = _selfClosingTag.substr(startIndex + 1 + tagName.size(), _selfClosingTag.find(ForwardSlash) - (startIndex + 1 + tagName.size()));

        auto a = extractAttributes(attributes);

        if (m_TagSelfCloseMethod)
        {
            m_TagSelfCloseMethod(tagName, a);
        }
    }

    std::vector<std::pair<std::string, std::string>> XML::extractAttributes(const std::string& _attributeString)
    {
        std::vector<std::pair<std::string, std::string>> attributes;

        std::string att = _attributeString;

        while (att.size())
        {
            trim(att);

            std::size_t equalsLoc = att.find(Equals);

            std::string attribute = att.substr(0, equalsLoc);

            QuoteType type = discoverNextAttributeQuoteType(att);

            if (type == QuoteType::Neither)
            {
                break;
            }

            char quote = (type == QuoteType::Double ? static_cast<char>('"') : static_cast<char>('\''));

            std::size_t quoteOpenLoc = att.find(quote);
            std::size_t quoteCloseLoc = att.find(quote, quoteOpenLoc + 1);

            std::string value = att.substr(quoteOpenLoc + 1, quoteCloseLoc - quoteOpenLoc - 1);

            att = att.substr(quoteCloseLoc + 1);

            attributes.push_back(std::make_pair(attribute, value));
        }

        return attributes;
    }

    XML::QuoteType XML::discoverNextAttributeQuoteType(const std::string& _attributes)
    {
        std::size_t doubleOpenLoc = _attributes.find(DoubleQuote);
        std::size_t singleOpenLoc = _attributes.find(SingleQuote);


        if (doubleOpenLoc == std::string::npos)
        {
            if (singleOpenLoc == std::string::npos)
            {
                return QuoteType::Neither;
            }
            else
            {
                return QuoteType::Single;
            }
        }
        else
        {
            if (singleOpenLoc == std::string::npos)
            {
                return QuoteType::Double;
            }
            else
            {
                //~ Both valid
                if (doubleOpenLoc < singleOpenLoc)
                {
                    return QuoteType::Double;
                }
                else
                {
                    return QuoteType::Single;
                }
            }
        }
    }

} //~ namespace zeno