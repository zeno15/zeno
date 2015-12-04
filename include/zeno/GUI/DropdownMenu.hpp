#ifndef INCLUDED_ZENO_GUI_COMBO_BOX_HPP
#define INCLUDED_ZENO_GUI_COMBO_BOX_HPP

#include <zeno/GUI/GuiBase.hpp>

namespace zeno {

class DropdownMenu : public GuiBase
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

    //~ Expensive, causes combo box to be rebuilt
    void addChoice(const std::string& _choice);

    std::string getCurrentChoice(void) const;

    void setSize(const zeno::Vector2f& _size);

private:
    friend class Desktop;

    ////////////////////////////////////////////////////////////
    //
    //	Default constructor
    //
    ////////////////////////////////////////////////////////////
    DropdownMenu(const std::string& _id, GuiBase *_parent, Desktop& _desktop);
    ////////////////////////////////////////////////////////////
    //
    //	Destructor
    //
    ////////////////////////////////////////////////////////////
    ~DropdownMenu(void);

    static DropdownMenu *createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

    void createBoxPositions(void);
    void createBoxColours(void);

    void setTrianglePositions(void);
    void setTriangleColours(void);

    void setBackgroundPositions(void);
    void setBackgroundColours(void);

    void setOptionBoxPositions(void);
    void setOptionBoxColours(void);

    virtual void initialise(void);

private:
    unsigned int m_VAO;
    unsigned int m_PositionVBO;
    unsigned int m_ColourVBO;

    Vector2f m_BoxSize;

    bool m_Extended;

    unsigned int m_Options;

    std::vector<std::string> m_OptionStrings;

    int m_CurrentChoice;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_COMBO_BOX_HPP