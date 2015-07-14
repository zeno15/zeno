#ifndef INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP
#define INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP

#include <zeno/Graphics/Font.hpp>

#include <zeno/GUI/GUIEvent.hpp>
#include "Pane.hpp"

#include <zeno/System/Vector2.hpp>

#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

class GuiBase;
class Time;
class Event;

////////////////////////////////////////////////////////////
///
///	\brief  Class to manage rendering and updating gui elements
///
////////////////////////////////////////////////////////////
class Desktop
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief Constructor
    ///
    /// Ensures that the default shader is loaded correctly
    ///
    ////////////////////////////////////////////////////////////
	Desktop(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Processes an event
    ///
    /// Passes the event to the relevant GUI elements
    ///
    /// \param  _event  Event to be processed
    ///
    ////////////////////////////////////////////////////////////
	void processEvent(const Event& _event);
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Renders all GUI elements and panes
    ///
    ////////////////////////////////////////////////////////////
	void render(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the resolution of the desktop so rendering
    ///         looks correct
    ///
    /// \param  _resolution Vector2 size of the desktop
    ///
    ////////////////////////////////////////////////////////////
	void setResolution(const Vector2u& _resolution);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Used to manually throw an event onto the queue
    ///
    /// \param  _guiEvent   GUIEvent to add to processing queue
    ///
    ////////////////////////////////////////////////////////////
	void throwEvent(const GUIEvent& _guiEvent);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Processes all manually thrown events
    ///
    ////////////////////////////////////////////////////////////
    void processThrown(void);

    ////////////////////////////////////////////////////////////
    ///
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    void addToElement(const std::string& _id, const std::string& _parent = std::string());

    ////////////////////////////////////////////////////////////
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T& getElement(const std::string& _id);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Loads the font to use for GUI elements
    ///
    /// \param  _filename   Filename of the font file
    ///
    /// \param  _fontSize   Size of the Font to use
    ///
    /// \return True if font loaded successfully, false otherwise
    ///
    ////////////////////////////////////////////////////////////
	bool loadGUIFont(const std::string& _filename, unsigned int _fontSize = 32);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the font used fro GUI elements
    ///
    /// \return Pointer to the Font in use
    ///
    ////////////////////////////////////////////////////////////
	Font *getGUIFont(void);

private:
	////////////////////////////////////////////////////////////
	///
	///	\brief  Translates a Window Event to a GUIEvent
    ///
    /// \param  _event  Window Event to translate
    ///
    /// \param  _guiEvent   GUIEvent to be modified
    ///
    /// \return True if Event can be translated
	///
	////////////////////////////////////////////////////////////
	bool translateEvent(const Event& _event, GUIEvent& _guiEvent) const;

private:
    static const std::string           m_DesktopPaneId;

private:
	Vector2u					m_Resolution;       ///<    Resolution of the desktop

    Pane m_DesktopPane;      ///<    Base pane that contains all elements

	std::vector<GUIEvent>		m_ThrownEvents;     ///<    Vector of events that have been thrown

	Font 						m_GUIFont;          ///<    Font to use for all GUI elements

    std::vector<std::string>    m_InvalidIds;       ///<    Vector containing all Ids that have been used
};


#include <zeno/GUI/Desktop.inl>


} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Desktop
///	\ingroup GUI
///
///	Explanation of how this all works
///
///	\code
///	\endcode
///
////////////////////////////////////////////////////////////