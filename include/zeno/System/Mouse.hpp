#ifndef INCLUDED_ZENO_SYSTEM_MOUSE_HPP
#define INCLUDED_ZENO_SYSTEM_MOUSE_HPP

#include <zeno/System/Vector2.hpp>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

class Window;

////////////////////////////////////////////////////////////
///
/// \brief  Class to give simple real time access to mouse position
///	        and state
///
////////////////////////////////////////////////////////////
class Mouse
{
public:
	////////////////////////////////////////////////////////////
	///
	/// \brief	Enumeration of supported mouse buttons
	///
	////////////////////////////////////////////////////////////
	enum Button {	Left = 0,       ///<    Left mouse button
					Right = 1,      ///<    Right mouse button
					Middle = 2,     ///<    Middle (wheel) mouse button
					Extra1 = 3,     ///<    First extra mouse button
					Extra2 = 4,     ///<    Second extra mouse button
					NUM_BUTTONS ///<    Number of mouse buttons
    };

	////////////////////////////////////////////////////////////
	///
    /// \brief      Provides access to the state of mouse buttons
    ///
    /// \param      _button The mouse Button who's state to check
    ///
    /// \return     Boolean value representing whether or not
    ///             the given mouse button is held down
    ///
	////////////////////////////////////////////////////////////
	static bool isButtonDown(Button _button, const Window& _window);

	////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the position of the mouse cursor relative
    ///         to the window
    ///
    /// \param  _window Window to get mouse position relative to
    ///
    /// \return Vector2 representing position of mouse cursor
    ///
	////////////////////////////////////////////////////////////
	static Vector2i getPosition(const Window& _window);

	////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the position of the mouse cursor in desktop
    ///         coordinates
    ///
    /// \param  _position   Vector2 representing the coordinates
    ///                     to set the mouse position to
    ///
    /// \param  _window     Window to set the mouse position relate to
    ///
    ////////////////////////////////////////////////////////////
	static void setPosition(const Vector2i& _position, const Window& _window);
};
	
} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_MOUSE_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Mouse
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code
///	bool isLeftButtonDown = zeno::Mouse::isButtonDown(zeno::Mouse::Left);
///	\endcode
///
////////////////////////////////////////////////////////////