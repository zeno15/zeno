#ifndef INCLUDED_ZENO_GUI_RADIO_BUTTON_GROUP_HPP
#define INCLUDED_ZENO_GUI_RADIO_BUTTON_GROUP_HPP

#include <zeno/GUI/GuiBase.hpp>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

class RadioButtonGroup : public GuiBase
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

    void addRadioButton(const std::string& _id);

    std::string getActiveOption(void) const;

    virtual void initialise(void);

private:
    friend class Desktop;

    ////////////////////////////////////////////////////////////
    //
    //	Default constructor
    //
    ////////////////////////////////////////////////////////////
    RadioButtonGroup(const std::string& _id, GuiBase *_parent, Desktop& _desktop);
    ////////////////////////////////////////////////////////////
    //
    //	Destructor
    //
    ////////////////////////////////////////////////////////////
    ~RadioButtonGroup(void);

    static RadioButtonGroup *createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

private:
    std::vector<std::string> m_RadioButtons;

    std::string m_ActiveOption;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_RADIO_BUTTON_GROUP_HPP