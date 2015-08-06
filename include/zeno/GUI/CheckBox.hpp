#ifndef INCLUDED_ZENO_GUI_CHECKBOX_HPP
#define INCLUDED_ZENO_GUI_CHECKBOX_HPP

#include <zeno/GUI/GuiBase.hpp>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

    class CheckBox : public GuiBase
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

        bool isChecked(void) const;

    private:
        friend class Desktop;

        ////////////////////////////////////////////////////////////
        //
        //	Default constructor
        //
        ////////////////////////////////////////////////////////////
        CheckBox(const std::string& _id, GuiBase *_parent);
        ////////////////////////////////////////////////////////////
        //
        //	Destructor
        //
        ////////////////////////////////////////////////////////////
        ~CheckBox(void);

        static CheckBox *createElement(const std::string& _id, GuiBase *_parent);

        void initialisePositions(void);
        void initialiseColours(void);

    private:
        unsigned int m_VAO;
        unsigned int m_PositionVBO;
        unsigned int m_ColourVBO;

        bool    m_Checked;
    };

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_CHECKBOX_HPP