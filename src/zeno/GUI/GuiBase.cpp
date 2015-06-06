#include <zeno/GUI/GuiBase.hpp>

namespace zeno {

GuiBase::GuiBase(const std::string& _id) :
m_Active(true),
m_HasFocus(false),
m_Id(_id)
{

}


void GuiBase::setActive(bool _active)
{
	m_Active = _active;
}

bool GuiBase::getActive(void) const
{
	return m_Active;
}

void GuiBase::addChild(GuiBase *_child)
{
	m_Children.push_back(_child);
}

bool GuiBase::hasChildren(void) const
{
	return (m_Children.size() > 0);
}

std::vector<GuiBase *> GuiBase::getChildren(void)
{
	return m_Children;
}
std::string GuiBase::getId(void)
{
	return m_Id;
}

} //~ namespace zeno