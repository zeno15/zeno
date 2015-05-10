#include <zeno/GUI/TextBox.hpp>

#include <iostream>

namespace zeno {

TextBox::TextBox(const std::string& _id) :
GuiBase(_id)
{
}
TextBox::~TextBox(void)
{
}


bool TextBox::processEvent(const GUIEvent& _event)
{
	return false;
}

void TextBox::render(Mat4x4 _transform) const
{
}

FloatRect TextBox::getBounds(void)
{
	std::cout << "TODO" << std::endl;

	return FloatRect();
}

} //~ namespace zeno