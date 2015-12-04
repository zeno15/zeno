#ifndef INCLUDED_ZENO_SYSTEM_KEYBOARD_HPP
#define INCLUDED_ZENO_SYSTEM_KEYBOARD_HPP

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

class Window;

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
		Unknown = -1,	        ///< Unhandled key
		A = 65,			        ///< A Key
		B = 66,				    ///< B Key
		C = 67,				    ///< C Key
		D = 68,				    ///< D Key
		E = 69,				    ///< E Key
		F = 70,				    ///< F Key
		G = 71,				    ///< G Key
		H = 72,				    ///< H Key
		I = 73,				    ///< I Key
		J = 74,				    ///< J Key
		K = 75,				    ///< K Key
		L = 76,				    ///< L Key
		M = 77,				    ///< M Key
		N = 78,				    ///< N Key
		O = 79,				    ///< O Key
		P = 80,				    ///< P Key
		Q = 81,				    ///< Q Key
		R = 82,				    ///< R Key
		S = 83,				    ///< S Key
		T = 84,				    ///< T Key
		U = 85,				    ///< U Key
		V = 86,				    ///< V Key
		W = 87,				    ///< W Key
		X = 88,				    ///< X Key
		Y = 89,				    ///< Y Key
		Z = 90,				    ///< Z Key
		Num0 = 48,			    ///< Number 0 Key
		Num1 = 49,			    ///< Number 1 Key
		Num2 = 50,			    ///< Number 2 Key
		Num3 = 51,			    ///< Number 3 Key
		Num4 = 52,			    ///< Number 4 Key
		Num5 = 53,			    ///< Number 5 Key
		Num6 = 54,			    ///< Number 6 Key
		Num7 = 55,			    ///< Number 7 Key
		Num8 = 56,			    ///< Number 8 Key
		Num9 = 57,			    ///< Number 9 Key
		Escape = 256,			///< Escape Key
		LControl = 341,		    ///< Left Control Key
		LShift = 340,			///< Left Shift Key
		LAlt = 342,			    ///< Left Alt Key
		LSystem = 343,		    ///< Left System Key (e.g. Windows)
		RControl = 345,		    ///< Right Control Key
		RShift = 344,			///< Right Shift Key
		RAlt = 346,			    ///< Right Alt Key
		RSystem = 347,		    ///< Right System Key (e.g. Windows)
		Menu = 348,			    ///< Menu Key
		LBracket = 91,		    ///< [ Key
		RBracket = 93,		    ///< ] Key
		SemiColon = 59,		    ///< ; Key
		Comma = 44,			    ///< , Key
		Fullstop = 46,		    ///< . Key
		Apostrophe = 39,	    ///< ' Key
		ForwardSlash = 47,	    ///< / Key
		BackwardSlash = 92,	    ///< \ Key
		Equals = 61,			///< = Key
		Minus = 45,			    ///< - Key
		Space = 32,			    ///< SpaceBar Key
		Enter = 257,			///< Enter/Return Key
		BackSpace = 259,		///< BackSpace Key
		Tab = 258,			    ///< Tab Key
		PageUp = 266,			///< Page Up Key
		PageDown = 267,		    ///< Page Down Key
		End = 269,			    ///< End Key
		Home = 268,			    ///< Home Key
		Insert = 260,			///< Insert Key
		Delete = 261,			///< Delete Key
		Add = 334,			    ///< Numpad Add Key
		Subtract = 333,		    ///< Numpad Subtract Key
		Multiply = 332,		    ///< Numpad Multiply Key
		Divide = 331,			///< Numpad Divide Key
		Left = 263,			    ///< Left Arrow Key
		Right = 262,			///< Right Arrow Key
		Up = 265,				///< Up Arrow Key
		Down = 264,			    ///< Down Arrow Key
		Numpad0 = 320,		    ///< Numpad 0 Key
		Numpad1 = 321,		    ///< Numpad 1 Key
		Numpad2 = 322,		    ///< Numpad 2 Key
		Numpad3 = 323,		    ///< Numpad 3 Key
		Numpad4 = 324,		    ///< Numpad 4 Key
		Numpad5 = 325,		    ///< Numpad 5 Key
		Numpad6 = 326,		    ///< Numpad 6 Key
		Numpad7 = 327,		    ///< Numpad 7 Key
		Numpad8 = 328,		    ///< Numpad 8 Key
		Numpad9 = 329,		    ///< Numpad 9 Key
		F1 = 290,				///< F1 Key
		F2 = 291,				///< F2 Key
		F3 = 292,				///< F3 Key
		F4 = 293,				///< F4 Key
		F5 = 294,				///< F5 Key
		F6 = 295,				///< F6 Key
		F7 = 296,				///< F7 Key
		F8 = 297,				///< F8 Key
		F9 = 298,				///< F9 Key
		F10 = 299,			    ///< F10 Key
		F11 = 300,			    ///< F11 Key
		F12 = 301,			    ///< F12 Key
		F13 = 302,			    ///< F13 Key
		F14 = 303,			    ///< F14 Key
		F15 = 304,			    ///< F15 Key
		Pause = 284,			///< Pause Key

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
	static bool isKeyDown(Key _key, const Window& _window);
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