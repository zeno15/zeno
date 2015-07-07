#include <zeno/Utility/Epub.hpp>

#include <zeno/Utility/XML.hpp>
#include <zeno/Utility/Zip.hpp>

#include <iostream>

namespace zeno {

Epub::Epub(void)
{

}

void Epub::reset(void)
{
    m_Title = "";
    m_Author = "";
    m_ChapterNames.clear();
    m_ChapterVector.clear();
}

void Epub::setEpubTitle(const std::string& _title)
{
    m_Title = _title;
}
void Epub::setEpubAuthor(const std::string& _author)
{
    m_Author = _author;
}

void Epub::writeToFile(const std::string& _filename)
{
    XML containerxml = XML();

    std::string UNIQUE_ID = "UID";
    std::string IDENTIFIER_CONTENT = "asdadadsasdad";

    containerxml.addDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    containerxml.addElement("container", {{"xmlns", "urn:oasis:names:tc:opendocument:xmlns:container"}, {"version", "1.0"}}, "/");
    containerxml.addElement("rootfiles", {}, "/container/");
    containerxml.addClosedElement("rootfile", {{"media-type", "application/oebps-package+xml"}, {"full-path", "EPUB/content.opf"}}, "/container/rootfiles/");


    std::string containerString = containerxml.writeToString();

    XML contentopf = XML();

    contentopf.addDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    contentopf.addElement("package", {{"xmlns", "http://www.idpf.org/2007/opf"}, {"unique-identifier", UNIQUE_ID}, {"version", "2.0"}}, "/");

    //~ metadata section
    contentopf.addElement("metadata", {{"xmlns:dc", "http://purl.org/dc/elements/1.1/"}}, "/package/");

    contentopf.addElement("dc:identifier", {{"id", UNIQUE_ID}}, "/package/metadata/");
    contentopf.addContent(IDENTIFIER_CONTENT, "/package/metadata/dc:identifier/");

    contentopf.addElement("dc:title", {}, "/package/metadata/");
    contentopf.addContent(m_Title, "/package/metadata/dc:title/");

    contentopf.addElement("dc:creator", {}, "/package/metadata/");
    contentopf.addContent(m_Author, "/package/metadata/dc:creator/");

    contentopf.addElement("dc:language", {}, "/package/metadata/");
    contentopf.addContent("en-US", "/package/metadata/dc:language/");

    contentopf.addElement("dc:rights", {}, "/package/metadata/");
    contentopf.addContent("Public Domain", "/package/metadata/dc:rights/");

    contentopf.addElement("dc:publisher", {}, "/package/metadata/");
    contentopf.addContent("libzeno-utility", "/package/metadata/dc:publisher/");

    //~ manifest section
    contentopf.addElement("manifest", {}, "/package/");

    contentopf.addClosedElement("item", {{"id", "ncx"}, {"href", "toc.ncx"}, {"media-type", "application/x-dtbncx+xml"}}, "/package/manifest/");

    for (unsigned int i = 1; i <= m_ChapterVector.size(); i += 1)
    {
        std::string stringIndex = std::to_string(i);

        contentopf.addClosedElement("item", {{"id", std::string("Chapter" + stringIndex)}, {"href", std::string("Chapter" + stringIndex + ".xhtml")}, {"media-type", "application/xhtml+xml"}}, "/package/manifest/");
    }

    //~ spine section
    contentopf.addElement("spine", {{"toc", "ncx"}}, "/package/");

    for (unsigned int i = 1; i <= m_ChapterVector.size(); i += 1)
    {
        std::string stringIndex = std::to_string(i);

        contentopf.addClosedElement("itemref", {{"idref", std::string("Chapter" + stringIndex)}}, "/package/spine/");
    }

    std::string contentString = contentopf.writeToString();

    XML tocncx = XML();

    tocncx.addDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    tocncx.addElement("ncx", {{"xmlns:ncx", "http://www.daisy.org/z3986/2005/ncx/"}, {"xmlns", "http://www.daisy.org/z3986/2005/ncx/"}, {"version", "2005-1"}, {"xml:lang", "en"}}, "/");

    tocncx.addElement("head", {}, "/ncx/");
    tocncx.addClosedElement("meta", {{"name", "dtb:uid"}, {"content", IDENTIFIER_CONTENT}}, "/ncx/head/");

    tocncx.addElement("docTitle", {}, "/ncx/");
    tocncx.addElement("text", {}, "/ncx/docTitle/");
    tocncx.addContent(m_Title, "/ncx/docTitle/text/");

    tocncx.addElement("navMap", {}, "/ncx/");

    for (int i = 1; i <= static_cast<int>(m_ChapterVector.size()); i += 1)
    {
        std::string stringIndex = std::to_string(i);

        tocncx.addElement("navPoint", {{"id", std::string("Chapter" + stringIndex)}}, "/ncx/navMap/");
        tocncx.addElement("navLabel", {}, "/ncx/navMap/navPoint/", {0, 0, i - 1});
        tocncx.addElement("text", {}, "/ncx/navMap/navPoint/navLabel/", {0, 0, i - 1, 0});
        tocncx.addContent(m_ChapterNames.at(i - 1), "/ncx/navMap/navPoint/navLabel/text/", {0, 0, i - 1, 0, 0});
        tocncx.addClosedElement("content", {{"src", std::string("Chapter" + stringIndex + ".xhtml")}}, "/ncx/navMap/navPoint/", {0, 0, i - 1});
    }

    std::string tocString = tocncx.writeToString();

    Zip zip = Zip();

    std::string mimetypeString = "application/epub+zip";
    std::vector<unsigned char> mimeteypeData(mimetypeString.begin(), mimetypeString.end());

    zip.addFileFromMemory(mimeteypeData, "mimetype", "");
    zip.addFileFromMemory(std::vector<unsigned char>(containerString.begin(), containerString.end()), "container.xml", "META-INF/");
    zip.addFileFromMemory(std::vector<unsigned char>(contentString.begin(), contentString.end()), "content.opf", "EPUB/");
    zip.addFileFromMemory(std::vector<unsigned char>(tocString.begin(), tocString.end()), "toc.ncx", "EPUB/");

    for (unsigned int i = 1; i <= m_ChapterVector.size(); i += 1)
    {
        std::string stringIndex = std::to_string(i);

        zip.addFileFromMemory(std::vector<unsigned char>(m_ChapterVector.at(i - 1).begin(), m_ChapterVector.at(i - 1).end()), std::string("Chapter" + stringIndex + ".xhtml"), "EPUB/");
    }

    zip.saveToFile(_filename);
}

void Epub::addChapterContent(const std::string& _data, const std::string& _chapterName)
{
    std::string chapter = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><html xmlns=\"http://www.w3.org/1999/xhtml\"><head><title>" + _chapterName + "</title></head><body><div>" + _data + "</div></body></html>";

    m_ChapterVector.push_back(std::vector<unsigned char>(chapter.begin(), chapter.end()));

    m_ChapterNames.push_back(_chapterName);
}

} //~ namespace zeno