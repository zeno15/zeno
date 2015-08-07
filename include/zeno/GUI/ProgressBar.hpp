#ifndef INCLUDED_ZENO_GUI_PROGRESS_BAR_HPP
#define INCLUDED_ZENO_GUI_PROGRESS_BAR_HPP

#include <zeno/GUI/GuiBase.hpp>

#include <zeno/Graphics/Vertex.hpp>

#include <vector>

namespace zeno {
	
////////////////////////////////////////////////////////////
//
//	Simple 3-tone progress bar
//
////////////////////////////////////////////////////////////
class ProgressBar : public GuiBase
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
	//	Changes the colour of the outline segment
	//
	////////////////////////////////////////////////////////////
	void changeOutlineColour(const Colour& _colour);
	////////////////////////////////////////////////////////////
	//
	//	Changes the colour of the incomplete segment
	//
	////////////////////////////////////////////////////////////
	void changeIncompleteColour(const Colour& _colour);
	////////////////////////////////////////////////////////////
	//
	//	Changes the colour of the complete segment
	//
	////////////////////////////////////////////////////////////
	void changeCompleteColour(const Colour& _colour);
	
	////////////////////////////////////////////////////////////
	//
	//	Sets the position of the bottom left corner of the 
	//	progress bar
	//
	////////////////////////////////////////////////////////////
	void setPosition(const Vector2f& _position);
	////////////////////////////////////////////////////////////
	//
	//	Sets the size of the progress bar
	//
	////////////////////////////////////////////////////////////
	void setSize(const Vector2f& _size);
	////////////////////////////////////////////////////////////
	//
	//	Sets the thickness of the outline
	//
	////////////////////////////////////////////////////////////
	void setOutlineThickness(float _thickness);

    void setPercentage(float _perc);

private:

    friend class Desktop;

    ////////////////////////////////////////////////////////////
    //
    //	Constructor
    //
    ////////////////////////////////////////////////////////////
    ProgressBar(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

    ////////////////////////////////////////////////////////////
    //
    //	Destructor
    //
    ////////////////////////////////////////////////////////////
    ~ProgressBar(void);

    ////////////////////////////////////////////////////////////
	//
	//	Resends the updateded complete segment data
	//
	////////////////////////////////////////////////////////////
	void resendData(float _percent);
	
	////////////////////////////////////////////////////////////
	//
	//	Recreates the progress bar when a new size/position
	//	is set
	//
	////////////////////////////////////////////////////////////
	void recreate(void);

    static ProgressBar *createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

private:
	////////////////////////////////////////////////////////////
	//
	//	Size of the progress bar
	//
	////////////////////////////////////////////////////////////
	Vector2f				m_Size;
	////////////////////////////////////////////////////////////
	//
	//	Position of the bottom left of the progress bar
	//
	////////////////////////////////////////////////////////////
	Vector2f				m_Position;
	
	////////////////////////////////////////////////////////////
	//
	//	Current percentage that the progress bar is at
	//
	////////////////////////////////////////////////////////////
	float					m_CurrentPercentage;
	////////////////////////////////////////////////////////////
	//
	//	Thickness of the outline segment
	//
	////////////////////////////////////////////////////////////
	float					m_OutlineThickness;
	
	////////////////////////////////////////////////////////////
	//
	//	Vertex Array Object
	//
	////////////////////////////////////////////////////////////
	unsigned int m_VAO;
	
	////////////////////////////////////////////////////////////
	//
	//	Vertex Buffer object for the positions
	//
	////////////////////////////////////////////////////////////
	unsigned int m_PositionVBO;
	////////////////////////////////////////////////////////////
	//
	//	Vertex Buffer Object for the colours
	//
	////////////////////////////////////////////////////////////
	unsigned int m_ColourVBO;
	
	////////////////////////////////////////////////////////////
	//
	//	Colour of the outline of the bar
	//
	////////////////////////////////////////////////////////////
	Colour	m_OutlineColour;
	////////////////////////////////////////////////////////////
	//
	//	Colour of the constant incomplete progress segment
	//
	////////////////////////////////////////////////////////////
	Colour	m_IncompleteColour;
	////////////////////////////////////////////////////////////
	//
	//	Colour of the increasing complete progress segment
	//
	////////////////////////////////////////////////////////////
	Colour	m_CompleteColour;

};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_PROGRESS_BAR_HPP

