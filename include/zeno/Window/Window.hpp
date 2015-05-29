#ifndef INCLUDED_ZENO_WINDOW_WINDOW_HPP
#define INCLUDED_ZENO_WINDOW_WINDOW_HPP

#include <zeno/System/Event.hpp>
#include <zeno/System/Vector2.hpp>

#include <zeno/Window/ContextImplementation.hpp>
#include <zeno/Window/WindowHandle.hpp>
#include <zeno/Window/WindowImplementation.hpp>
#include <zeno/Window/WindowStyle.hpp>
#include <zeno/Window/VideoMode.hpp>

#include <vector>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

//~ TODO Need context settings to set antialiasing/opengl version

////////////////////////////////////////////////////////////
///
/// \brief	Platform independent window class
///
////////////////////////////////////////////////////////////
class Window
{
public:
	////////////////////////////////////////////////////////////
	///
	/// \brief	Constructor
    ///
    /// Does not create a window, user must call create
	///
	////////////////////////////////////////////////////////////
	Window(void);

	////////////////////////////////////////////////////////////
	///
	/// \brief  Constructor
	///
	/// Calls create with the given parameters
	//
	////////////////////////////////////////////////////////////
	Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

	////////////////////////////////////////////////////////////
	///
	/// \brief	Destructor
	///
    /// Frees all resources associated with the window
    ///
	////////////////////////////////////////////////////////////
	~Window(void);


	////////////////////////////////////////////////////////////
	///
	/// \brief	Creates a window and context implementation
    ///
    /// \param  _videoMode  VideoMode to use for the window
    ///
    /// \param  _title      Title for the window
    ///
    /// \param  _style      WindowStyle for the window
    ///
    /// \return Boolean value on whether the Window was created
    ///         successfully or not
	///
	////////////////////////////////////////////////////////////
	bool create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

	////////////////////////////////////////////////////////////
	///
    /// \brief Closes the window, frees the resources associated
	///	       with the window and the context
	///
	////////////////////////////////////////////////////////////
	void close(void);

	////////////////////////////////////////////////////////////
	///
	///	\brief  Returns whether the window is open
    ///
    /// \return True if window is open, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool isOpen(void) const;

	////////////////////////////////////////////////////////////
	///
	/// \brief	Gets the position of the window relative to the
    ///         desktop
    ///
    /// \return Vector2 representing distance to top left of the
    ///         desktop
	///
	////////////////////////////////////////////////////////////
	Vector2i getPosition(void) const;

	////////////////////////////////////////////////////////////
	///
	/// \brief	Sets the position of the window relative to the
    ///         desktop
    ///
    /// \param  _position   Vector2 representing distance to top
    ///                     left of the desktop
	///
	////////////////////////////////////////////////////////////
	void setPosition(const Vector2i& _position);

	////////////////////////////////////////////////////////////
	///
	///	\brief  Gets the size of the window
	///
    /// \return Vector2 representing the width and height of the
    ///         window
    ///
	////////////////////////////////////////////////////////////
	Vector2u getSize(void) const;

	////////////////////////////////////////////////////////////
	///
	/// \brief	Sets the size of the window
	///
    /// \param  _size   Desired size of the window
    ///
	////////////////////////////////////////////////////////////
	void setSize(const Vector2u& _size);

	////////////////////////////////////////////////////////////
	///
	///	\brief  Swaps the buffers, displaying the window contents
	///
	////////////////////////////////////////////////////////////
	void display(void);

	////////////////////////////////////////////////////////////
	///
	///	\brief  Polls the window for the next event in the queue
    ///
    /// \param  _event  Event that will be modified with the
    ///                 first event in the queue
    ///
    /// \return True if there was an event in the queue and the
    ///         given event now represents it, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool pollEvent(Event& _event);
	////////////////////////////////////////////////////////////
	///
	///	\brief  Blocking version of pollEvent
    ///
    /// \param  _event  Event that will be modified with the
    ///                 first event in the queue
	///
	////////////////////////////////////////////////////////////
	void waitEvent(Event& _event);

	////////////////////////////////////////////////////////////
	///
	/// \brief	Sets whether repeated key input is being used
    ///
    /// \param  _repeat True to enable, False to disable
	///
	////////////////////////////////////////////////////////////
	void setRepeatedKeys(bool _repeat);

	////////////////////////////////////////////////////////////
	///
	///	\brief  Returns the system specific window handle
    ///
    /// \return WindowHandle, only for internal use
	///
	////////////////////////////////////////////////////////////
	WindowHandle getHandle(void) const;

	////////////////////////////////////////////////////////////
	///
	/// \brief	Sets the title of the window
    ///
    /// \param  _title  String to set the Window title to
	///
	////////////////////////////////////////////////////////////
	void setTitle(const std::string& _title);

	////////////////////////////////////////////////////////////
	///
	///	\brief  Gets the current title of the window
	///
    /// \return String containing the title of the window
    ///
	////////////////////////////////////////////////////////////
	std::string getTitle(void) const;
	
	////////////////////////////////////////////////////////////
	///
	/// \brief	Enables/disables v-sync
    ///
    /// \param  _vsync  True to enable v-sync, False to disable
	///
	////////////////////////////////////////////////////////////
	void setVerticalSync(bool _vsync = true);

	////////////////////////////////////////////////////////////
	///
	///	\brief  Returns whether or not v-sync is enabled
    ///
    /// \return True if v-sync is enabled, false otherwise
	///
	////////////////////////////////////////////////////////////
	bool getVerticalSyncState(void);
	

	////////////////////////////////////////////////////////////
	///
	///	\brief  Switches the window to fullscreen mode
    ///
    /// \param  _videoMode  The VideoMode to use
	///
	////////////////////////////////////////////////////////////
	void switchToFullscreen(const VideoMode& _videoMode);

private:
	VideoMode					m_VideoMode;        ///<    The currently implemented video mode

	std::string					m_Title;            ///<    The title of the window

	uint32_t					m_WindowStyle;      ///<    The style of the window

	WindowImplementation		m_WindowImpl;       ///<    The system specific window implementation

	ContextImplementation		m_ContextImpl;      ///<    The system specific context implementation
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_WINDOW_WINDOW_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Window
///	\ingroup Window
///
///	Explanation of how this all works
///
///	\code
///	\endcode
///
////////////////////////////////////////////////////////////