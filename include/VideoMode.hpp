#ifndef INCLUDED_VIDEO_MODE_HPP
#define INCLUDED_VIDEO_MODE_HPP

#include <cstdint>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Struct describing basic video mode
//
////////////////////////////////////////////////////////////
struct VideoMode
{
	unsigned int bitsPerPixel;
	unsigned int width;
	unsigned int height;
};

} //~ namespace zeno

#endif //~ INCLUDED_VIDEO_MODE_HPP