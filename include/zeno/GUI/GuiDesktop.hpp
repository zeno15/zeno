#ifndef INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP
#define INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP

#include <zeno/Graphics/Font.hpp>

#include <zeno/GUI/GUIEvent.hpp>
#include <zeno/GUI/GuiPane.hpp>

#include <zeno/System/Vector2.hpp>

#include <vector>
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
class GuiDesktop
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief Constructor
    ///
    /// Ensures that the default shader is loaded correctly
    ///
    ////////////////////////////////////////////////////////////
	GuiDesktop(void);

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
    /// \brief  Adds a new pane to the GuiDesktop
    ///
    /// \param  _name The name of the new GuiPane
    ///
    ////////////////////////////////////////////////////////////
	void addPane(const std::string& _name);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets reference to GuiPane that has the given \a _id
    ///
    /// \param  _id Unique identification of the GuiPane
    ///
    /// \return Read/write reference to GuiPane
    ///
    ////////////////////////////////////////////////////////////
	GuiPane& getPane(const std::string& _id);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Adds a new GUI element to a GuiPane
    ///
    /// \param  _pane   The id of the GuiPane to add the child to
    ///
    /// \param  _child  Pointer to a new GUI element to add
    ///
    ////////////////////////////////////////////////////////////
    void addToPane(const std::string& _pane, GuiBase *_child);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Get a pointer to the desired GUI element
    ///
    /// \param  _pane       GuiPane name to get element from
    ///
    /// \param  _element    Name of desired element to retrieve
    ///
    /// \return Pointer to GUI element, provided type should
    ///         match the type of the element returned
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    T *getElementFromPane(const std::string& _pane, const std::string& _element);

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
	Vector2u					m_Resolution;       ///<    Resolution of the desktop

    std::vector<GuiPane>        m_Panes;            ///<    Vector of GuiPane the desktop owns

	std::vector<GUIEvent>		m_ThrownEvents;     ///<    Vector of events that have been thrown

	Font 						m_GUIFont;          ///<    Font to use for all GUI elements
};


#include <zeno/GUI/GuiDesktop.inl>


} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::GuiDesktop
///	\ingroup GUI
///
///	Explanation of how this all works
///
///	\code
///	\endcode
///
////////////////////////////////////////////////////////////