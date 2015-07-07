#ifndef INCLUDED_ZENO_UTILITY_EPUB_HPP
#define INCLUDED_ZENO_UTILITY_EPUB_HPP

//~ www.idpf.org/epub/301/spec/epub-overview.html

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
///	\brief
///
////////////////////////////////////////////////////////////
class Epub
{
public:
    Epub(void);

    void reset(void);

    void setEpubTitle(const std::string& _title);
    void setEpubAuthor(const std::string& _author);

    void addChapterContent(const std::string& _data, const std::string& _chapterName);

    void writeToFile(const std::string& _filename);


private:
    std::vector<std::vector<unsigned char>>    m_ChapterVector;
    std::vector<std::string>                    m_ChapterNames;

    std::string                                 m_Title;
    std::string                                 m_Author;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_UTILITY_EPUB_HPP