#ifndef ZENO_UTILITY_JSON_HPP
#define ZENO_UTILITY_JSON_HPP

#include <zeno/Utility/JSON/JSONNode.hpp>
#include <zeno/Utility/JSON/JSONValueNode.hpp>
#include <zeno/Utility/JSON/JSONObjectNode.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief  Class to encapsulate all functionality to create
///         and parse JSON documents
///
////////////////////////////////////////////////////////////
class JSON
{
public:
    static JSONNode parseFile(const std::string& _filename);
private:

};

} //~ namespace zeno

#endif //~ ZENO_UTILITY_JSON_HPP
