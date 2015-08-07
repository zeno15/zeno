#ifndef INCLUDED_ZENO_GUI_BUTTON_HPP
#define INCLUDED_ZENO_GUI_BUTTON_HPP

#include <zeno/GUI/GuiBase.hpp>

#include <zeno/Graphics/Colour.hpp>
#include <zeno/System/Rect.hpp>

#include <functional>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

class Font;
class Label;

////////////////////////////////////////////////////////////
//
//	Simple push button class
//
////////////////////////////////////////////////////////////
class Button : public GuiBase
{
public:
    ////////////////////////////////////////////////////////////
	//
	//	Virtual function which returns whether or not the 
	//	element can handle the given event, and if it can handle
	//	it, it does so
	//
	////////////////////////////////////////////////////////////
	virtual bool processEvent(const GUIEvent& _event);

	////////////////////////////////////////////////////////////
	//
	//	Renders the element
	//
	////////////////////////////////////////////////////////////
	virtual void render(Mat4x4 _transform) const;

	////////////////////////////////////////////////////////////
	//
	//	Returns the Rect object that contains all the points of
	//	the GUI element.
	//
	////////////////////////////////////////////////////////////
	virtual FloatRect getBounds(void);

	////////////////////////////////////////////////////////////
	//
	//	Registers the function to be called on activation of button
	//
	////////////////////////////////////////////////////////////
	void registerCallback(std::function<void(void)> _function);
	
	////////////////////////////////////////////////////////////
	//
	//	Changes the size of the button so it can surround the
	//	label
	//  TODO - Will need to change this when requesting sizes 
	//  for pane packing etc
	//
	////////////////////////////////////////////////////////////
	void addLabel(const std::string& _labelString, Font *_font);

private:

    friend class Desktop;

    ////////////////////////////////////////////////////////////
    //
    //	Default constructor
    //
    ////////////////////////////////////////////////////////////
    Button(const std::string& _id, GuiBase *_parent, Desktop& _desktop);
    ////////////////////////////////////////////////////////////
    //
    //	Destructor
    //
    ////////////////////////////////////////////////////////////
    ~Button(void);

    static Button *createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop);


private:
	enum State {
		DEFAULT,
		HOVER,
		DEPRESSED
	};

	void resendColours(void);
	void resendPositions(void);

	void changeState(State _newState);

	
	
private:
	unsigned int					m_VAO;

	unsigned int					m_PositionVBO;
	unsigned int					m_ColourVBO;
	
	Colour							m_BackgroundDefaultColour;
	Colour							m_BackgroundDepressedColour;
	Colour							m_ForegroundDefaultColour;
	Colour							m_ForegroundHoverColour;

	State							m_State;

	FloatRect	m_Bounds;

	bool		m_Depressed;
	bool		m_MouseContained;

	float		m_OutlineThickness;

	std::function<void(void)>		m_ActivationFunction;

	Label *							m_Label;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_BUTTON_HPP