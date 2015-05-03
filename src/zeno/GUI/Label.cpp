#include <zeno/GUI/Label.hpp>

namespace zeno {

Label::Label(const std::string& _id) :
GuiBase(_id)
{
}
Label::~Label(void)
{
}


bool Label::processEvent(const GUIEvent& _event)
{
	return false;
}

void Label::render(void) const
{
}

} //~ namespace zeno