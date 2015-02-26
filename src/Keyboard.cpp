#include <Keyboard.hpp>

#ifdef _WIN32
#include <InputImplementationWindows.hpp>
#else
#include <InputImplementationUnix.hpp>
#endif //~ _WIN32

namespace zeno {

bool Keyboard::isKeyDown(Key _key)
{
	return InputImplementation::isKeyDown(_key);
}

} //~ namespace zeno