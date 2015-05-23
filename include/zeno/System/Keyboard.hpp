#ifndef INCLUDED_ZENO_SYSTEM_KEYBOARD_HPP
#define INCLUDED_ZENO_SYSTEM_KEYBOARD_HPP

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief  Class to give access to keyboard state
///
////////////////////////////////////////////////////////////
class Keyboard
{
public:
	////////////////////////////////////////////////////////////
	///
	/// \brief  List of supported keys
	///
	////////////////////////////////////////////////////////////
	enum Key
	{
		Unknown = -1,	///< Unhandled key
		A = 0,			///< A Key
		B,				///< B Key
		C,				///< C Key
		D,				///< D Key
		E,				///< E Key
		F,				///< F Key
		G,				///< G Key
		H,				///< H Key
		I,				///< I Key
		J,				///< J Key
		K,				///< K Key
		L,				///< L Key
		M,				///< M Key
		N,				///< N Key
		O,				///< O Key
		P,				///< P Key
		Q,				///< Q Key
		R,				///< R Key
		S,				///< S Key
		T,				///< T Key
		U,				///< U Key
		V,				///< V Key
		W,				///< W Key
		X,				///< X Key
		Y,				///< Y Key
		Z,				///< Z Key
		Num0,			///< Number 0 Key
		Num1,			///< Number 1 Key
		Num2,			///< Number 2 Key
		Num3,			///< Number 3 Key
		Num4,			///< Number 4 Key
		Num5,			///< Number 5 Key
		Num6,			///< Number 6 Key
		Num7,			///< Number 7 Key
		Num8,			///< Number 8 Key
		Num9,			///< Number 9 Key
		Escape,			///< Escape Key
		LControl,		///< Left Control Key
		LShift,			///< Left Shift Key
		LAlt,			///< Left Alt Key
		LSystem,		///< Left System Key (e.g. Windows)
		RControl,		///< Right Control Key
		RShift,			///< Right Shift Key
		RAlt,			///< Right Alt Key
		RSystem,		///< Right System Key (e.g. Windows)
		Menu,			///< Menu Key
		LBracket,		///< [ Key
		RBracket,		///< ] Key
		SemiColon,		///< ; Key
		Comma,			///< , Key
		Fullstop,		///< . Key
		Quote,			///< ' Key
		ForwardSlash,	///< / Key
		BackwardSlash,	///< \ Key
		Tilde,			///< ~ Key
		Equals,			///< = Key
		Hyphen,			///< - Key
		Space,			///< SpaceBar Key
		Enter,			///< Enter/Return Key
		BackSpace,		///< BackSpace Key
		Tab,			///< Tab Key
		PageUp,			///< Page Up Key
		PageDown,		///< Page Down Key
		End,			///< End Key
		Home,			///< Home Key
		Insert,			///< Insert Key
		Delete,			///< Delete Key
		Add,			///< Numpad Add Key
		Subtract,		///< Numpad Subtract Key
		Multiply,		///< Numpad Multiply Key
		Divide,			///< Numpad Divide Key
		Left,			///< Left Arrow Key
		Right,			///< Right Arrow Key
		Up,				///< Up Arrow Key
		Down,			///< Down Arrow Key
		Numpad0,		///< Numpad 0 Key
		Numpad1,		///< Numpad 1 Key
		Numpad2,		///< Numpad 2 Key
		Numpad3,		///< Numpad 3 Key
		Numpad4,		///< Numpad 4 Key
		Numpad5,		///< Numpad 5 Key
		Numpad6,		///< Numpad 6 Key
		Numpad7,		///< Numpad 7 Key
		Numpad8,		///< Numpad 8 Key
		Numpad9,		///< Numpad 9 Key
		F1,				///< F1 Key
		F2,				///< F2 Key
		F3,				///< F3 Key
		F4,				///< F4 Key
		F5,				///< F5 Key
		F6,				///< F6 Key
		F7,				///< F7 Key
		F8,				///< F8 Key
		F9,				///< F9 Key
		F10,			///< F10 Key
		F11,			///< F11 Key
		F12,			///< F12 Key
		F13,			///< F13 Key
		F14,			///< F14 Key
		F15,			///< F15 Key
		Pause,			///< Pause Key

		NumKeys			///< Total Number Of Keys
	};

	////////////////////////////////////////////////////////////
	///
	/// \brief	Method to determine if given key is down
    ///
    /// \param  _key Key to check state of
    ///
    /// \return Boolean representing whether or not \a _key is down
	///
	////////////////////////////////////////////////////////////
	static bool isKeyDown(Key _key);
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_KEYBOARD_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Keyboard
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code
///	zeno::Keyboard::isKeyDown(zeno::Keyboard::Space);
///	\endcode
///
////////////////////////////////////////////////////////////