#ifndef INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP
#define INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP

#include <cstdint>

////////////////////////////////////////////////////////////
///
///	\namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief  Struct describing video mode to be applied to
///         a window
///
////////////////////////////////////////////////////////////
struct VideoMode
{
    ////////////////////////////////////////////////////////////
    ///
    /// \brief Default constructor
    ///
    /// Sets width to 640 pixels, sets height to 480 pixels
    /// and sets 32 bits per pixel
    ///
    ////////////////////////////////////////////////////////////
    VideoMode() :
            width(640),
            height(480),
            bitsPerPixel(32)
    {
    }

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Constructor
    ///
    /// Sets 32 bits per pixel
    ///
    /// \param  _width  Desired width of the window
    ///
    /// \param  _height Desired height of the window
    ///
    ////////////////////////////////////////////////////////////
    VideoMode(unsigned int _width, unsigned int _height) :
            width(_width),
            height(_height),
            bitsPerPixel(32)
    {
    }

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Constructor
    ///
    /// \param  _width          Desired width of the window
    ///
    /// \param  _height         Desired height of the window
    ///
    /// \param  _bitsPerPixel   Desired bits per pixel
    ///
    ////////////////////////////////////////////////////////////
    VideoMode(unsigned int _width, unsigned int _height, unsigned int _bitsPerPixel) :
            width(_width),
            height(_height),
            bitsPerPixel(_bitsPerPixel)
    {
    }


	unsigned int width;             ///<    Width of the window

	unsigned int height;            ///<    Height of the window

    unsigned int bitsPerPixel;      ///<    Number of bits per pixel
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::VideoMode
///	\ingroup Window
///
///	Explanation of how this all works
///
///	\code
///	\endcode
///
////////////////////////////////////////////////////////////