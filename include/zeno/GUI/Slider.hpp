#ifndef INCLUDED_ZENO_GUI_SLIDER_HPP
#define INCLUDED_ZENO_GUI_SLIDER_HPP

#include <zeno/GUI/GuiBase.hpp>

#include <zeno/Graphics/Colour.hpp>

#include <zeno/System/Vector2.hpp>

#include <functional>

namespace zeno {
	
////////////////////////////////////////////////////////////
//
//	Slider which allows selection of values between a 
//	given range of values (discrete or continuous)
//
////////////////////////////////////////////////////////////
class Slider : public GuiBase
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
	//	Registers the callback to be used when the slider
	//	changes its value
	//
	////////////////////////////////////////////////////////////
	void registerCallback(std::function<void(float)> _function);

	virtual void initialise(void);

private:

    friend class Desktop;

    ////////////////////////////////////////////////////////////
    //
    //	Constructor
    //
    ////////////////////////////////////////////////////////////
    Slider(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

    ////////////////////////////////////////////////////////////
    //
    //	Destructor
    //
    ////////////////////////////////////////////////////////////
    ~Slider(void);

    static Slider *createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

    enum State {
		DEFAULT,
		HOVER,
		HELD
	};

	void recreate(void);

	void resendPositions(void);
	void resendColours(State _state);

	float calculateDiscretePosition(float _continuousPosition);

private:
	unsigned int						m_VAO;

	unsigned int						m_PositionVBO;
	unsigned int						m_ColourVBO;

	unsigned int						m_NumDiscreteValues;

	Colour								m_BarColour;
	Colour								m_DefaultSlideColour;
	Colour								m_HoverSlideColour;
	Colour								m_HeldSlideColour;

	Vector2f							m_Position;

	float								m_Length;
	float								m_SlideOffsetPercent;

	bool								m_HasSlide;
	bool								m_MouseContained;
	bool								m_Continuous;

	State								m_State;

	std::function<void(float)>			m_ChangeFunction;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_SLIDER_HPP