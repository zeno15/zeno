#include <zeno/Utility/JSON.hpp>

#include <fstream>

namespace zeno {

JSONNode JSON::parseFile(const std::string& _filename)
{
    std::ifstream input(_filename.c_str());
}

} //~ namespace zeno