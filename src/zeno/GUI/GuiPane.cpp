#include <zeno/GUI/GuiPane.hpp>

#include <iostream>

namespace zeno {

GuiPane::GuiPane(const std::string& _id, GuiBase *_parent) :
GuiBase(_id, _parent)
{
    m_IsPane = true;
}

GuiPane::~GuiPane(void)
{
}


bool GuiPane::processEvent(const GUIEvent& _event)
{
	if (!m_Active)
    {
        return false;
    }
	for (GuiBase *element : m_Children)
	{
        //~ Don't update inactive elements
        if (!element->getActive()) continue;

		if (element->processEvent(_event))
		{
			return true;
		}
	}

	return false;
}

void GuiPane::render(Mat4x4 _transform) const
{
    if (!m_Active)
    {
        return;
    }
	for (GuiBase *element : m_Children)
	{
		element->render(_transform);
	}
}
    GuiPane *GuiPane::createElement(const std::string& _id, GuiBase *_parent)
{
    return new GuiPane(_id, _parent);
}


} //~ namespace zeno