#ifndef INCLUDED_ZENO_WINDOW_WINDOW_STYLE_HPP
#define INCLUDED_ZENO_WINDOW_WINDOW_STYLE_HPP

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
///////////////////////////////////////////////////////////
namespace zeno {

///////////////////////////////////////////////////////////
///
/// \brief  Class describing possible window styles
///
///////////////////////////////////////////////////////////
class WindowStyle
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief	Enumerated description of available window styles
    ///
    ////////////////////////////////////////////////////////////
    enum {
        NoStyle = 0,                          ///<    Splash screen like mode
        Titlebar = 1 << 0,                    ///<    Title bar with no buttons
        Resize = 1 << 1,                      ///<    Allows the window to be resized
        Close = 1 << 2,                       ///<    Adds a close button to the title bar
        Fullscreen = 1 << 3,                  ///<    Sets the window to fullscreen

        Default = Titlebar | Resize | Close   ///<    Usual combination of options to use
    };

};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_WINDOW_WINDOW_STYLE_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::WindowStyle
///	\ingroup Window
///
///	Explanation of how this all works
///
///	\code
///	\endcode
///
////////////////////////////////////////////////////////////