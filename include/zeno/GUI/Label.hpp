#ifndef INCLUDED_ZENO_GUI_LABEL_HPP
#define INCLUDED_ZENO_GUI_LABEL_HPP

#include <zeno/GUI/GuiBase.hpp>

#include <zeno/Graphics/Text.hpp>

namespace zeno {

class Label : public GuiBase
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor
	//
	////////////////////////////////////////////////////////////
	Label(const std::string& _id, Font *_font);
	////////////////////////////////////////////////////////////
	//
	//	Deconstructor
	//
	////////////////////////////////////////////////////////////
	~Label(void);


	////////////////////////////////////////////////////////////
	//
	//	Virtual function which returns whether or not the 
	//	element can handle the given event, and if it can handle
	//	it, it does so
	//
	////////////////////////////////////////////////////////////
	virtual bool processEvent(const GUIEvent& _event);

	////////////////////////////////////////////////////////////
	//
	//	Renders the element
	//
	////////////////////////////////////////////////////////////
	virtual void render(Mat4x4 _transform) const;
	
	////////////////////////////////////////////////////////////
	//
	//	Sets the text to be used for the label
	//
	////////////////////////////////////////////////////////////
	void setLabel(const std::string& _label);
	
	////////////////////////////////////////////////////////////
	//
	//	Changes the colour of the label text
	//
	////////////////////////////////////////////////////////////
	void setLabelColour(const Colour& _colour);

private:
	////////////////////////////////////////////////////////////
	//
	//	Text object that the label consists of
	//
	////////////////////////////////////////////////////////////
	Text					m_LabelText;

	////////////////////////////////////////////////////////////
	//
	//	Pointer to the font used for the label
	//
	////////////////////////////////////////////////////////////
	Font *					m_LabelFont;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_LABEL_HPP