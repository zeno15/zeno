#include <zeno/Utility/Zip.hpp>

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>

uint32_t CRC_32(const std::vector<unsigned char>& _data)
{
    uint32_t crc = 0xFFFFFFFF;
    uint32_t polynomial = 0xEDB88320;

    for (unsigned char c : _data)
    {
        crc ^= c;

        for (unsigned int i = 0; i < 8; i += 1)
        {
            if ((crc & 1) != 0)
            {
                crc = (crc >> 1) ^ polynomial;
            }
            else
            {
                crc = crc >> 1;
            }
        }
    }

    return ~crc;
}

namespace zeno {

Zip::Zip(void)
{

}


bool Zip::addFile(const std::string& _filename)
{
    std::ifstream input;
    input.open(_filename, std::ios::in | std::ios::binary);
    if (!input.good())
    {
        return false;
    }

    std::vector<unsigned char> str;

    input.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned int>(input.tellg()));
    input.seekg(0, std::ios::beg);


    str.insert(str.begin(), std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());

    std::size_t pos = _filename.find_last_of('/');

    pos = (pos == std::string::npos) ? 0 : pos + 1;

    m_Files.push_back(str);

    m_Filenames.push_back(_filename.substr(pos));

    input.close();

    return true;
}

bool Zip::saveToFile(const std::string& _filename)
{
    std::ofstream file;
    file.open(_filename, std::ios::out | std::ios::binary);

    std::vector<unsigned int> offsets;

    unsigned int offset = 0;

    std::vector<unsigned char> total;

    for (unsigned int i = 0; i < m_Files.size(); i += 1)
    {
        std::vector<unsigned char> result = createLocalHeader(m_Files.at(i), m_Filenames.at(i));
        total.insert(total.end(), result.begin(), result.end());
        total.insert(total.end(), m_Files.at(i).begin(), m_Files.at(i).end());

        offsets.push_back(offset);
        offset += result.size();
        offset += m_Files.at(i).size();
    }

    unsigned int centralHeaderTotal = 0;

    for (unsigned int i = 0; i < m_Files.size(); i += 1)
    {
        std::vector<unsigned char> result = createCentralDirectoryFileHeader(m_Files.at(i), m_Filenames.at(i), offsets.at(i));
        total.insert(total.end(), result.begin(), result.end());
        centralHeaderTotal += result.size();
    }
    std::vector<unsigned char> result = Zip::createCentralDirectoryEnd(total.size() - centralHeaderTotal, m_Files.size(), centralHeaderTotal);
    total.insert(total.end(), result.begin(), result.end());


    file.write(reinterpret_cast<char *>(total.data()), total.size());

    file.close();

    return true;
}

bool Zip::loadFromFile(const std::string& _filename)
{
    std::ifstream file;
    file.open(_filename, std::ios::in | std::ios::binary);

    if (!file.good())
    {
        return false;
    }

    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned int>(file.tellg()));
    file.seekg(0, std::ios::beg);

    std::cout << "'" << _filename << "': " << file.tellg() << "REDO see the add file method" << std::endl;

    str.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::cout << Zip::getType(str) << std::endl;

    return true;
}

std::vector<unsigned char> Zip::createLocalHeader(const std::vector<unsigned char>& _data, const std::string& _filename)
{
    std::vector<unsigned char> str;

    //~ Signature 0x50 0x4B 0x04 0x04
    str.push_back(static_cast<unsigned char>(80));
    str.push_back(static_cast<unsigned char>(75));
    str.push_back(static_cast<unsigned char>(3));
    str.push_back(static_cast<unsigned char>(4));

    //~ Version 0x14 0x00
    str.push_back(static_cast<unsigned char>(20));
    str.push_back(static_cast<unsigned char>(0));

    //~ Flags 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Compression 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Modification Time 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Modification Date 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ CRC-32 0x00 0x00 0x00 0x00
    uint32_t crc = CRC_32(_data);
    str.push_back(static_cast<unsigned char>(crc >>  0));
    str.push_back(static_cast<unsigned char>(crc >>  8));
    str.push_back(static_cast<unsigned char>(crc >> 16));
    str.push_back(static_cast<unsigned char>(crc >> 24));

    //~ Compressed Size 0x?? 0x?? 0x?? 0x??
    str.push_back(static_cast<unsigned char>(_data.size() >>  0));
    str.push_back(static_cast<unsigned char>(_data.size() >>  8));
    str.push_back(static_cast<unsigned char>(_data.size() >> 16));
    str.push_back(static_cast<unsigned char>(_data.size() >> 24));

    //~ Uncompressed Size 0x?? 0x?? 0x?? 0x??
    str.push_back(static_cast<unsigned char>(_data.size() >>  0));
    str.push_back(static_cast<unsigned char>(_data.size() >>  8));
    str.push_back(static_cast<unsigned char>(_data.size() >> 16));
    str.push_back(static_cast<unsigned char>(_data.size() >> 24));

    //~ Filename length 0x?? 0x??
    str.push_back(static_cast<unsigned char>(_filename.size() >>  0));
    str.push_back(static_cast<unsigned char>(_filename.size() >>  8));

    //~ Extra field length 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    str.insert(str.end(), _filename.begin(), _filename.end());

    return str;
}

std::vector<unsigned char> Zip::createCentralDirectoryFileHeader(const std::vector<unsigned char>& _data, const std::string& _filename, unsigned int _offset)
{
    std::vector<unsigned char> str;

    //~ Central Directory File Header Signature 0x50 0x4B 0x01 0x02
    str.push_back(static_cast<unsigned char>(80));
    str.push_back(static_cast<unsigned char>(75));
    str.push_back(static_cast<unsigned char>(1));
    str.push_back(static_cast<unsigned char>(2));

    //~ Version 0x14 0x00
    str.push_back(static_cast<unsigned char>(20));
    str.push_back(static_cast<unsigned char>(0));

    //~ Version Needed 0x14 0x00
    str.push_back(static_cast<unsigned char>(20));
    str.push_back(static_cast<unsigned char>(0));

    //~ Flags 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Compression 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Modification Time 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Modification Date 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ CRC-32 0x00 0x00 0x00 0x00
    uint32_t crc = CRC_32(_data);
    str.push_back(static_cast<unsigned char>(crc >>  0));
    str.push_back(static_cast<unsigned char>(crc >>  8));
    str.push_back(static_cast<unsigned char>(crc >> 16));
    str.push_back(static_cast<unsigned char>(crc >> 24));

    //~ Compressed Size 0x?? 0x?? 0x?? 0x??
    str.push_back(static_cast<unsigned char>(_data.size() >>  0));
    str.push_back(static_cast<unsigned char>(_data.size() >>  8));
    str.push_back(static_cast<unsigned char>(_data.size() >> 16));
    str.push_back(static_cast<unsigned char>(_data.size() >> 24));

    //~ Uncompressed Size 0x?? 0x?? 0x?? 0x??
    str.push_back(static_cast<unsigned char>(_data.size() >>  0));
    str.push_back(static_cast<unsigned char>(_data.size() >>  8));
    str.push_back(static_cast<unsigned char>(_data.size() >> 16));
    str.push_back(static_cast<unsigned char>(_data.size() >> 24));

    //~ Filename length 0x?? 0x??
    str.push_back(static_cast<unsigned char>(_filename.size() >> 0));
    str.push_back(static_cast<unsigned char>(_filename.size() >> 8));

    //~ Extra field length 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ File comment length 0x00 0x00
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ TODO if a file/folder can go over multiple archive files this will need to be changed
    //~ Disk number start 0x?? 0x??
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Internal attributes
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ External attributes
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Offset of local header 0x?? 0x?? 0x?? 0x??
    str.push_back(static_cast<unsigned char>(_offset >>  0));
    str.push_back(static_cast<unsigned char>(_offset >>  8));
    str.push_back(static_cast<unsigned char>(_offset >> 16));
    str.push_back(static_cast<unsigned char>(_offset >> 24));

    //~ File name
    str.insert(str.end(), _filename.begin(), _filename.end());

    //~ Extra field

    //~ File comment


    return str;
}

std::vector<unsigned char> Zip::createCentralDirectoryEnd(unsigned int _startingOffset, unsigned int _numberEntries, unsigned int _centralHeadersSize)
{
    std::vector<unsigned char> str;

    //~ Signature 0x50 0x4B 0x05 0x06
    str.push_back(static_cast<unsigned char>(80));
    str.push_back(static_cast<unsigned char>(75));
    str.push_back(static_cast<unsigned char>(5));
    str.push_back(static_cast<unsigned char>(6));

    //~ This disk number
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Disk number containing Central Directory start
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Number of Central Directory entries on this disk
    str.push_back(static_cast<unsigned char>(_numberEntries >> 0));
    str.push_back(static_cast<unsigned char>(_numberEntries >> 8));

    //~ Total number of entries in the Central Directory
    str.push_back(static_cast<unsigned char>(_numberEntries >> 0));
    str.push_back(static_cast<unsigned char>(_numberEntries >> 8));

    //~ Size of Central Directory in bytes
    str.push_back(static_cast<unsigned char>(_centralHeadersSize >>  0));
    str.push_back(static_cast<unsigned char>(_centralHeadersSize >>  8));
    str.push_back(static_cast<unsigned char>(_centralHeadersSize >> 16));
    str.push_back(static_cast<unsigned char>(_centralHeadersSize >> 24));

    //~ Offset of the start of the Central Directory from the start of its disk
    str.push_back(static_cast<unsigned char>(_startingOffset >>  0));
    str.push_back(static_cast<unsigned char>(_startingOffset >>  8));
    str.push_back(static_cast<unsigned char>(_startingOffset >> 16));
    str.push_back(static_cast<unsigned char>(_startingOffset >> 24));

    //~ Comment Length
    str.push_back(static_cast<unsigned char>(0));
    str.push_back(static_cast<unsigned char>(0));

    //~ Comment

    return str;
}

Zip::HeaderType Zip::getType(const std::string& _string)
{
    if (_string.size() < 4)
    {
        return HeaderType::INVALID;
    }
    unsigned int byte0 = static_cast<unsigned int>(_string[0]);
    unsigned int byte1 = static_cast<unsigned int>(_string[1]);
    unsigned int byte2 = static_cast<unsigned int>(_string[2]);
    unsigned int byte3 = static_cast<unsigned int>(_string[3]);

    if (byte0 != 80 || byte1 != 75)
    {
        return HeaderType::INVALID;
    }

    if (byte2 == 1 && byte3 == 2)
    {
        return HeaderType::CENTRAL_START;
    }
    else if (byte2 == 3 && byte3 == 4)
    {
        return HeaderType::LOCAL_HEADER;
    }
    else if (byte2 == 5 && byte3 == 6)
    {
        return HeaderType::CENTRAL_END;
    }

    return HeaderType::INVALID;
}

} //~ namespace zeno