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

    if (m_ActiveOption == std::string())
    {
        //~ No default has been selected.
        m_Desktop.getElement<RadioButton>(_id).set();
        m_ActiveOption = _id;
    }
}

std::string RadioButtonGroup::getActiveOption(void) const
{
    return m_ActiveOption;
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

            m_ActiveOption = child->getId();

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