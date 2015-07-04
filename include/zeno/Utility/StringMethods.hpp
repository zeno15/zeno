#ifndef INCLUDED_ZENO_UTILITY_STRING_METHODS_HPP
#define INCLUDED_ZENO_UTILITY_STRING_METHODS_HPP

#include <vector>
#include <string>

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

std::string stripLeadingWhitespace(const std::string& _str);

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_UTILITY_STRING_METHODS_HPP