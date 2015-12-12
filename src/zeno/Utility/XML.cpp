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
        m_TagOpenMethod = [](const std::string& _tagString)
        {
            std::cout << "Encountered opening tag: '" << _tagString << "'" << std::endl;
        };
        m_TagCloseMethod = [](const std::string& _tagString)
        {
            std::cout << "Encountered closing tag: '" << _tagString << "'" << std::endl;
        };
    }

    void XML::loadFromFile(const std::string &_filename)
    {
        std::ifstream input(_filename);

        if (!input.good())
        {
            return;
        }

        for (unsigned int i = 0; i < 200; i += 1)
        {
            readTag(input);
            readContent(input);
        }

        input.close();
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
        std::cout << "Content: '" << _content << "'" << std::endl;
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
        std::cout << "Parsing a declaration tag: '" << _declarationTag << "'" << std::endl;
    }
    void XML::parseCommentTag(const std::string& _commentTag)
    {
        std::size_t startLocation = _commentTag.find(CommentSequenceOpen);
        std::size_t closeLocation = _commentTag.find(CommentSequenceClose);

        std::string comment = _commentTag.substr(startLocation + CommentSequenceOpen.size(), closeLocation - startLocation - CommentSequenceOpen.size());

        trim(comment);

        std::cout << "Comment tag: '" << comment << "'" << std::endl;
    }
    void XML::parseOpeningTag(const std::string& _openingTag)
    {
        std::size_t startIndex = _openingTag.find(OpenTag);
        std::size_t closeIndex = std::min(_openingTag.find(Space), _openingTag.find(CloseTag));

        std::string tagName = _openingTag.substr(startIndex + 1, closeIndex - startIndex - 1);

        std::string attributes = _openingTag.substr(closeIndex - startIndex, _openingTag.find(CloseTag) - (closeIndex - startIndex));

        std::cout << "Opening tag: '" << tagName << "'" << std::endl;
        auto a = extractAttributes(attributes);
        for (auto p : a)
        {
            std::cout << "\t" << p.first << ": " << p.second << std::endl;
        }
    }
    void XML::parseClosingTag(const std::string& _closingTag)
    {
        std::size_t startIndex = _closingTag.find(ForwardSlash);
        std::size_t closeIndex = _closingTag.find(CloseTag);

        std::string tagName = _closingTag.substr(startIndex + 1, closeIndex - startIndex - 1);

        std::cout << "Closing tag '" << tagName << "'" << std::endl;
    }
    void XML::parseSelfClosingTag(const std::string& _selfClosingTag)
    {
        std::size_t startIndex = _selfClosingTag.find(OpenTag);
        std::size_t closeIndex = std::min(_selfClosingTag.find(Space), _selfClosingTag.find(ForwardSlash));

        std::string tagName = _selfClosingTag.substr(startIndex + 1, closeIndex - startIndex - 1);

        std::string attributes = _selfClosingTag.substr(startIndex + 1 + tagName.size(), _selfClosingTag.find(ForwardSlash) - (startIndex + 1 + tagName.size()));

        std::cout << "Self-Closing tag '" << tagName << "'" << std::endl;
        auto a = extractAttributes(attributes);
        for (auto p : a)
        {
            std::cout << "\t'" << p.first << "': '" << p.second << "'" << std::endl;
        }
    }

    std::vector<std::pair<std::string, std::string>> XML::extractAttributes(const std::string& _attributeString)
    {
        std::vector<std::pair<std::string, std::string>> attributes;

        std::cout << "Working on attributes: '" << _attributeString << "'" << std::endl;

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

            char quote = (type == QuoteType::Double ? '"' : '\'');

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