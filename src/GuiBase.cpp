#include <GuiBase.hpp>

namespace zeno {

void GuiBase::setActive(bool _active)
{
	m_Active = _active;
}

bool GuiBase::getActive(void)
{
	return m_Active;
}

} //~ namespace zeno