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
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Adds a file from disk to the archive
    ///
    /// \param  _filename   File to be added to archive
    ///
    /// \param  _destination    Destination within the archive for
    ///                         the file to be added to
    ///
    /// \return Boolean representing if the file could be found
    ///         and added
    ///
    ////////////////////////////////////////////////////////////
    bool addFile(const std::string& _filename, const std::string& _destination = "");

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Adds a file from memory to the archive
    ///
    /// \param  _data   Data representing the desired file
    ///
    /// \param  _filename   Desired filename of the data
    ///
    /// \param  _destination    Destination within the archive for
    ///                         the file to be added to
    ///
    /// \return Boolean representing if the given file data could
    ///         be added
    ///
    ////////////////////////////////////////////////////////////
    bool addFileFromMemory(const std::vector<unsigned char>& _data, const std::string& _filename, const std::string& _destination = "");

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Saves the zip archive to a file
    ///
    /// \param  _filename   Desired filename of the archive
    ///
    /// \return Boolean represnting if the archive could be saved
    ///
    ////////////////////////////////////////////////////////////
    bool saveToFile(const std::string& _filename);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Loads an archive from disk
    ///
    /// \param  _filename   Desired archive filename
    ///
    /// \return Boolean representing if the given file could be
    ///         loaded
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromFile(const std::string& _filename);

private:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Enumeration of possible header types
    ///
    ////////////////////////////////////////////////////////////
    enum HeaderType {
        LOCAL_HEADER,   ///<    Local file header
        CENTRAL_START,  ///<    Beginning of central directory header
        CENTRAL_END,    ///<    End of central directory header
        INVALID         ///<    Invalid header
    };

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Creates a local header for the given data and
    ///         filename
    ///
    /// \param  _data   Data for the local header
    ///
    /// \param  _filename   Filename for the local header
    ///
    /// \return vector<unsigned char> containing the local header
    ///
    ////////////////////////////////////////////////////////////
    static std::vector<unsigned char> createLocalHeader(const std::vector<unsigned char>& _data, const std::string& _filename);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Creates the central directory file header for a
    ///         given file
    ///
    /// \param  _data   Data for the local header
    ///
    /// \param  _filename   Filename for the local header
    ///
    /// \param  _offset The offset of the given file within the archive
    ///
    /// \return vector<unsigned char> containing the central
    ///         directory file header
    ///
    ////////////////////////////////////////////////////////////
    static std::vector<unsigned char> createCentralDirectoryFileHeader(const std::vector<unsigned char>& _data, const std::string& _filename, unsigned int _offset);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Creates the central directory end header
    ///
    /// \param  _startingOffset The starting offset of the
    ///         central directory
    ///
    /// \param  _numberEntries  The number of entries in the archive
    ///
    /// \param  _centralHeaderSize  The size of the central directory
    ///                             header
    ///
    ////////////////////////////////////////////////////////////
    static std::vector<unsigned char> createCentralDirectoryEnd(unsigned int _startingOffset, unsigned int _numberEntries, unsigned int _centralHeadersSize);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the header type
    ///
    /// \param  _string The String containing the header
    ///
    /// \return Zip::HeaderType enum representing the header
    ///
    ////////////////////////////////////////////////////////////
    static Zip::HeaderType getType(const std::string& _string);

private:
    std::vector<std::vector<unsigned char>>   m_Files;          ///< List of files to add to the archive
    std::vector<std::string>   m_Filenames;                     ///< List of filenames to add to the archive
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_UTILITY_ZIP_HPP