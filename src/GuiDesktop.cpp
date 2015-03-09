#include <GuiDesktop.hpp>

#include <Time.hpp>
#include <GuiBase.hpp>

namespace zeno {

GuiDesktop::GuiDesktop(void)
{

}
GuiDesktop::~GuiDesktop(void)
{

}


void GuiDesktop::update(const Time& _delta)
{

}
void GuiDesktop::render(void)
{
	
}

void GuiDesktop::addChild(GuiBase *_child)
{
	m_Children.push_back(_child);
}

} //~ namespace zeno