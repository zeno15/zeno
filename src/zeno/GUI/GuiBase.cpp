#include <zeno/GUI/GuiBase.hpp>

#include <zeno/GUI/Desktop.hpp>

#include <iostream>

namespace zeno {

GuiBase::GuiBase(const std::string& _id, GuiBase *_parent, Desktop& _desktop) :
m_Active(true),
m_HasFocus(false),
m_Visible(true),
m_IsPane(false),
m_Parent(_parent),
m_Id(_id),
m_Desktop(_desktop)
{

}


FloatRect GuiBase::getBounds(void)
{
    throw std::runtime_error("unimplemented function GuiBase::getBounds()");
}

void GuiBase::setActive(bool _active)
{
	m_Active = _active;
}

bool GuiBase::getActive(void) const
{
	return m_Active;
}

void GuiBase::setVisibility(bool _visible)
{
    m_Visible = _visible;
}

bool GuiBase::getVisibility(void) const
{
    return m_Visible;
}

void GuiBase::addChild(GuiBase *_child)
{
	m_Children.push_back(_child);
}

GuiBase *GuiBase::getChild(const std::string& _id)
{
    for (GuiBase *child : m_Children)
    {
        if (child->getId() == _id)
        {
            return child;
        }

        GuiBase *c = child->getChild(_id);

        if (c != nullptr)
        {
            return c;
        }
    }

    return nullptr;
}

std::string GuiBase::getId(void) const
{
	return m_Id;
}

void GuiBase::initialise(void)
{

}

} //~ namespace zeno