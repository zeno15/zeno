#include <zeno/Utility/StringMethods.hpp>

#include <iostream>

namespace zeno {

std::vector<std::string> splitStringByString(const std::string& _string, const std::string& _splitString)
{
    std::vector<std::string> returnValue;
    std::string string(_string);
    std::size_t loc;

    while (std::string::npos != (loc = string.find(_splitString)))
    {
        std::string pre = string.substr(0, loc);

        string = string.substr(loc + 1, std::string::npos);

        if (pre.size() > 0)
        {
            returnValue.push_back(pre);
        }
    }

    return returnValue;
}

std::vector<std::string> splitStringByDelimeters(const std::string& _string, const std::vector<std::string>& _splitStrings)
{
    std::vector<std::string> returnValue;

    //~ TODO implement

    std::cout << "TODO: Implement splitStringByDelimeters" << std::endl;

    return returnValue;
}

bool startsWith(const std::string& _str, const std::string& _start)
{
    return (_str.find(_start) == 0);
}
bool endsWith(const std::string& _str, const std::string& _end)
{
    return (_str.find(_end) == _str.size() - _end.size());
}

std::string stripLeadingWhitespace(const std::string& _str)
{
    std::string str(_str);

    const std::string whitespace(" \n\r\t");

    while (str.find_first_of(whitespace) == 0)
    {
        str = str.substr(1, std::string::npos);
    }

    return str;
}

void replaceAll(std::string& _string, const std::string& _substring, const std::string& _replacement)
{
    std::size_t pos = 0;
    while ((pos = _string.find(_substring, pos)) != std::string::npos)
    {
        _string.replace(pos, _substring.size(), _replacement);

        pos += _replacement.size();
    }
}

} //~ namespace zeno