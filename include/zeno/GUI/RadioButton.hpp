#ifndef INCLUDED_ZENO_GUI_RADIO_BUTTON_HPP
#define INCLUDED_ZENO_GUI_RADIO_BUTTON_HPP

#include <zeno/GUI/GuiBase.hpp>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

class RadioButton : public GuiBase
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

    virtual void initialise(void);

private:
    friend class Desktop;
    friend class RadioButtonGroup;

    ////////////////////////////////////////////////////////////
    //
    //	Default constructor
    //
    ////////////////////////////////////////////////////////////
    RadioButton(const std::string& _id, GuiBase *_parent, Desktop& _desktop);
    ////////////////////////////////////////////////////////////
    //
    //	Destructor
    //
    ////////////////////////////////////////////////////////////
    ~RadioButton(void);

    static RadioButton *createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

    void unset(void);
    void set(void);

    void initialisePositions(void);
    void initialiseColours(void);

private:
    unsigned int m_VAO;
    unsigned int m_PositionVBO;
    unsigned int m_ColourVBO;

    bool m_Checked;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_RADIO_BUTTON_HPP