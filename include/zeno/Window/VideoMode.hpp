#ifndef INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP
#define INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP

#include <cstdint>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Struct describing basic video mode
//
////////////////////////////////////////////////////////////
struct VideoMode
{
    VideoMode() :
            width(0),
            height(0),
            bitsPerPixel(32)
    {
    }

    VideoMode(unsigned int _width, unsigned int _height) :
            width(_width),
            height(_height),
            bitsPerPixel(32)
    {
    }

    VideoMode(unsigned int _width, unsigned int _height, unsigned int _bitsPerPixel) :
            width(_width),
            height(_height),
            bitsPerPixel(_bitsPerPixel)
    {
    }

	////////////////////////////////////////////////////////////
	//
	//	Width of the window
	//
	////////////////////////////////////////////////////////////
	unsigned int width;
	////////////////////////////////////////////////////////////
	//
	//	Height of the window
	//
	////////////////////////////////////////////////////////////
	unsigned int height;
    ////////////////////////////////////////////////////////////
    //
    //	Bits per pixel
    //
    ////////////////////////////////////////////////////////////
    unsigned int bitsPerPixel;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP