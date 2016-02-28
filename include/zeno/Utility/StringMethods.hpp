#ifndef INCLUDED_ZENO_UTILITY_STRING_METHODS_HPP
#define INCLUDED_ZENO_UTILITY_STRING_METHODS_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief  Splits a string by a given delimiter string
///
/// \param  _string         String to be split
///
/// \param  _splitString    Delimiter string
///
/// \return Vector of String's that consists of \a _string
///         split by \a _splitString
///
////////////////////////////////////////////////////////////
std::vector<std::string> splitStringByString(const std::string& _string, const std::string& _splitString);

////////////////////////////////////////////////////////////
///
///	\brief  Splits a string by a set of given delimiters
///
/// \param  _string String to be split
///
/// \param  _splitStrings   Vector of delimiter strings
///
/// \return Vector of String's that consists of \a _string
///         split by each String in \a _splitStrings
///
////////////////////////////////////////////////////////////
std::vector<std::string> splitStringByDelimeters(const std::string& _string, const std::vector<std::string>& _splitStrings);

bool startsWith(const std::string& _str, const std::string& _start);
bool endsWith(const std::string& _str, const std::string& _end);

std::string stripWhitespace(const std::string& _str);

void replaceAll(std::string& _string, const std::string& _substring, const std::string& _replacement);

static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

bool compareCaseInsensitive(const std::string& _left, const std::string& _right);

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_UTILITY_STRING_METHODS_HPP