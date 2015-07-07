#include <zeno/GUI/GuiPane.hpp>

#include <iostream>

namespace zeno {

GuiPane::GuiPane(const std::string& _id) :
GuiBase(_id)
{
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

FloatRect GuiPane::getBounds(void)
{
	std::cout << "TODO" << std::endl;

	return FloatRect();
}

void GuiPane::addChild(GuiBase *_child)
{
	m_Children.push_back(_child);
}

GuiBase *GuiPane::getChild(const std::string& _id)
{
	for (GuiBase *child : m_Children)
	{
		if (child->getId() == _id)
		{
			return child;
		}
	}
	
	throw std::runtime_error(std::string("Child \"" + _id + "\" not present in pane."));
}

} //~ namespace zeno