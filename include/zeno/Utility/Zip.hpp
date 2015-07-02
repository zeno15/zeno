#ifndef INCLUDED_ZENO_UTILITY_ZIP_HPP
#define INCLUDED_ZENO_UTILITY_ZIP_HPP

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
///	\brief  Class to create/read/modify zip archives
///         Initially without any compression
///
/// Implemented from: https://users/cs/jmu.edu/buchhofp/forensics/formats/pkzip.html
///
////////////////////////////////////////////////////////////
class Zip
{
public:
    enum HeaderType {
        LOCAL_HEADER,
        CENTRAL_START,
        CENTRAL_END,
        INVALID
    };

    ////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ////////////////////////////////////////////////////////////
    Zip(void);


    ////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ////////////////////////////////////////////////////////////
    bool addFile(const std::string& _filename, const std::string& _destination = "");

    ////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ////////////////////////////////////////////////////////////
    bool saveToFile(const std::string& _filename);

    ////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromFile(const std::string& _filename);

private:
    ////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ////////////////////////////////////////////////////////////
    static std::vector<unsigned char> createLocalHeader(const std::vector<unsigned char>& _data, const std::string& _filename);

    static std::vector<unsigned char> createCentralDirectoryFileHeader(const std::vector<unsigned char>& _data, const std::string& _filename, unsigned int _offset);

    ////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ////////////////////////////////////////////////////////////
    static std::vector<unsigned char> createCentralDirectoryEnd(unsigned int _startingOffset, unsigned int _numberEntries, unsigned int _centralHeadersSize);

    ////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ////////////////////////////////////////////////////////////
    static Zip::HeaderType getType(const std::string& _string);

private:
    std::vector<std::vector<unsigned char>>   m_Files;         ///< List of files to add to the archive
    std::vector<std::string>   m_Filenames;     ///< List of filenames to add to the archive
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_UTILITY_ZIP_HPP