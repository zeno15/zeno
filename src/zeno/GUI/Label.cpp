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

void Label::render(Mat4x4 _transform) const
{
	zeno::RenderData data;
	data.transform = _transform * getTransform();

	m_LabelText.render(data);
}

FloatRect Label::getBounds(void)
{
	m_LabelText.getBounds();

	Vector2f pos (m_LabelText.getBounds().left + getPosition().x, m_LabelText.getBounds().bot + getPosition().y);
	Vector2f size(m_LabelText.getBounds().width, m_LabelText.getBounds().height);

	return FloatRect(pos, size);
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