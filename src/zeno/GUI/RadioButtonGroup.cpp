#include <zeno/GUI/RadioButtonGroup.hpp>

#include <zeno/GUI/Desktop.hpp>
#include <zeno/GUI/RadioButton.hpp>

namespace zeno {

RadioButtonGroup::RadioButtonGroup(const std::string& _id, GuiBase *_parent, Desktop& _desktop) :
GuiBase(_id, _parent, _desktop)
{
}

RadioButtonGroup::~RadioButtonGroup(void)
{

}


void RadioButtonGroup::addRadioButton(const std::string& _id)
{
    m_Desktop.addToElement<RadioButton>(_id, getId());

    m_RadioButtons.push_back(_id);
}

RadioButtonGroup *RadioButtonGroup::createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop)
{
    return new RadioButtonGroup(_id, _parent, _desktop);
}


bool RadioButtonGroup::processEvent(const GUIEvent& _event)
{
    for (GuiBase *child : m_Children)
    {
        if (child->processEvent(_event))
        {
            for (const std::string id : m_RadioButtons)
            {
                if (child->getId() != id)
                {
                    m_Desktop.getElement<RadioButton>(id).unset();
                }
            }
            return true;
        }
    }

    return false;
}

void RadioButtonGroup::render(Mat4x4 _transform) const
{
    for (const GuiBase *child : m_Children)
    {
        child->render(_transform);
    }
}

} //~ namespace zeno