#include <zeno/GUI/Label.hpp>

#include <iostream>

namespace zeno {

Label::Label(const std::string& _id, Font *_font) :
GuiBase(_id),
m_LabelFont(_font)
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
	zeno::RenderData data;
	data.transform = zeno::Mat4x4::Orthographic2D(0.0f, 1280.0f, 720.0f, 0.0f);
	data.transform *= getTransform();

	m_LabelText.render(data);
}

void Label::setLabel(const std::string& _label)
{
	m_LabelText.generateText(_label, m_LabelFont);
}

void Label::setLabelColour(const Colour& _colour)
{
	m_LabelText.setColour(_colour);
}

} //~ namespace zeno