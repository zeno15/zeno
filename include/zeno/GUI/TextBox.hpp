#ifndef INCLUDED_ZENO_GUI_TEXT_BOX_HPP
#define INCLUDED_ZENO_GUI_TEXT_BOX_HPP

#include <zeno/GUI/GuiBase.hpp>

#include <zeno/Graphics/Text.hpp>

namespace zeno {

class Font;

////////////////////////////////////////////////////////////
//
//	GUI element for entering text
//
////////////////////////////////////////////////////////////
class TextBox : public GuiBase
{
public:
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
	//	Returns the Rect object that contains all the points of
	//	the GUI element.
	//
	////////////////////////////////////////////////////////////
	virtual FloatRect getBounds(void);

    void setFont(Font *_font);

	std::string getText(void);

	void setText(const std::string& _text);
	void addText(const std::string& _text);

	void setSize(const Vector2f& _size);

private:

    friend class Desktop;

    ////////////////////////////////////////////////////////////
    //
    //	Default constructor
    //
    ////////////////////////////////////////////////////////////
    TextBox(const std::string& _id, GuiBase *_parent, Desktop& _desktop);
    ////////////////////////////////////////////////////////////
    //
    //	Destructor
    //
    ////////////////////////////////////////////////////////////
    ~TextBox(void);

    static TextBox *createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop);

	void recreate(void);

	virtual void initialise(void);

private:
	Font *		m_Font;

	unsigned int m_VAO;

	Text		m_BoxText;

	std::string		m_String;

	Vector2f		m_Size;

	float			m_BorderSize;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_TEXT_BOX_HPP