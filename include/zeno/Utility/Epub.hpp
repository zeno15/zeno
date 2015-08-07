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
///	\brief  Class to create epub files from text data
///
////////////////////////////////////////////////////////////
class Epub
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Resets the Epub so you can create a new one
    ///
    ////////////////////////////////////////////////////////////
    void reset(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the title of the Epub
    ///
    /// \param  _title  Desired title of the Epub
    ///
    ////////////////////////////////////////////////////////////
    void setEpubTitle(const std::string& _title);
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the author of the Epub
    ///
    /// \param  _author Desired author of the Epub
    ///
    ////////////////////////////////////////////////////////////
    void setEpubAuthor(const std::string& _author);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Adds a new chapter to the Epub
    ///
    /// \param  _data   String containing the chapter data
    ///
    /// \param  _chapterName    Desired name of the chapter
    ///
    ////////////////////////////////////////////////////////////
    void addChapterContent(const std::string& _data, const std::string& _chapterName);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Saves the Epub to a file
    ///
    /// \param  _filename   Desired filename of the Epub
    ///
    ////////////////////////////////////////////////////////////
    void writeToFile(const std::string& _filename);


private:
    std::vector<std::vector<unsigned char>>     m_ChapterVector;    ///<    vector containing chapter data in unsigned char format
    std::vector<std::string>                    m_ChapterNames;     ///<    Vector containing chapter names in string format

    std::string                                 m_Title;            ///<    Title of the ebook
    std::string                                 m_Author;           ///<    Author of the ebook
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_UTILITY_EPUB_HPP