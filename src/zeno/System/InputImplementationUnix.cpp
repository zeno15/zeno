#include <zeno/System/InputImplementationUnix.hpp>

#include <iostream>

#include <X11/Xlib-xcb.h>
#include <X11/keysym.h>

namespace zeno {

bool InputImplementation::isKeyDown(Keyboard::Key _key)
{
	KeySym keysym = 0;
	switch(_key)
	{
		case Keyboard::A: keysym = XK_A; break;
		case Keyboard::B: keysym = XK_B; break;
		case Keyboard::C: keysym = XK_C; break;
		case Keyboard::D: keysym = XK_D; break;
		case Keyboard::E: keysym = XK_E; break;
		case Keyboard::F: keysym = XK_F; break;
		case Keyboard::G: keysym = XK_G; break;
		case Keyboard::H: keysym = XK_H; break;
		case Keyboard::I: keysym = XK_I; break;
		case Keyboard::J: keysym = XK_J; break;
		case Keyboard::K: keysym = XK_K; break;
		case Keyboard::L: keysym = XK_L; break;
		case Keyboard::M: keysym = XK_M; break;
		case Keyboard::N: keysym = XK_N; break;
		case Keyboard::O: keysym = XK_O; break;
		case Keyboard::P: keysym = XK_P; break;
		case Keyboard::Q: keysym = XK_Q; break;
		case Keyboard::R: keysym = XK_R; break;
		case Keyboard::S: keysym = XK_S; break;
		case Keyboard::T: keysym = XK_T; break;
		case Keyboard::U: keysym = XK_U; break;
		case Keyboard::V: keysym = XK_V; break;
		case Keyboard::W: keysym = XK_W; break;
		case Keyboard::X: keysym = XK_X; break;
		case Keyboard::Y: keysym = XK_Y; break;
		case Keyboard::Z: keysym = XK_Z; break;
		default:		  keysym = 0;    break;
	}
	
	// Open a connection with the X server
	Display* display = XOpenDisplay(NULL);
	xcb_connection_t* connection = XGetXCBConnection(display);
	// Convert to keycode
	KeyCode keycode = XKeysymToKeycode(display, keysym);
	if (keycode != 0)
	{
		// Get the whole keyboard state
		xcb_query_keymap_reply_t* keymap = xcb_query_keymap_reply(connection, xcb_query_keymap(connection), NULL);
		// Close the connection with the X server
		XCloseDisplay(display);
		// Check our keycode
		bool isPressed = (keymap->keys[keycode / 8] & (1 << (keycode % 8))) != 0;
		free(keymap);
		return isPressed;
	}
	else
	{
		// Close the connection with the X server
		XCloseDisplay(display);
		return false;
	}
}

} //~ namespace zeno
