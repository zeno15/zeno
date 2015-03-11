#include <GuiBase.hpp>

namespace zeno {

GuiBase::GuiBase(void) :
m_Active(true)
{

}

GuiBase::~GuiBase(void)
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

} //~ namespace zeno