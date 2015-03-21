#include <zeno/System/Keyboard.hpp>

#ifdef _WIN32
#include <zeno/System/InputImplementationWindows.hpp>
#else
#include <zeno/System/InputImplementationUnix.hpp>
#endif //~ _WIN32

namespace zeno {

bool Keyboard::isKeyDown(Key _key)
{
	return InputImplementation::isKeyDown(_key);
}

} //~ namespace zeno