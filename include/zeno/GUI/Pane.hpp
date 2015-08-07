#ifndef INCLUDED_ZENO_GUI_GUI_PANE_HPP
#define INCLUDED_ZENO_GUI_GUI_PANE_HPP

#include <zeno/GUI/GuiBase.hpp>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	
//
////////////////////////////////////////////////////////////
class Pane : public GuiBase
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

    void setColour(const Colour& _col);

    void setBounds(const FloatRect& _bounds);

    void removeBounds(void);

private:

    friend class Desktop;

    ////////////////////////////////////////////////////////////
    //
    //
    //
    ////////////////////////////////////////////////////////////
    Pane(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

    ////////////////////////////////////////////////////////////
    //
    //
    //
    ////////////////////////////////////////////////////////////
    ~Pane(void);

    static Pane *createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

private:
    bool                    m_Bounded;
    FloatRect               m_Bounds;

    unsigned int            m_VAO;
    unsigned int            m_PositionVBO;
    unsigned int            m_ColourVBO;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_GUI_PANE_HPP