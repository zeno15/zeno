#ifndef INCLUDED_GUI_BUTTON_HPP
#define INCLUDED_GUI_BUTTON_HPP

#include <GuiBase.hpp>
#include <GL/glew.h>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	
//
////////////////////////////////////////////////////////////
class GuiButton : public GuiBase
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor
	//
	////////////////////////////////////////////////////////////
	GuiButton(void);
	////////////////////////////////////////////////////////////
	//
	//	Deconstructor
	//
	////////////////////////////////////////////////////////////
	~GuiButton(void);


	////////////////////////////////////////////////////////////
	//
	//	Virtual function which returns whether or not the 
	//	element can handle the given event, and if it can handle
	//	it, it does so
	//
	////////////////////////////////////////////////////////////
	virtual bool processEvent(const Event& _event);
	////////////////////////////////////////////////////////////
	//
	//	Renders the element
	//
	////////////////////////////////////////////////////////////
	virtual void render(void) const;
private:
	GLuint VAO;
};

} //~ namespace zeno

#endif //~ INCLUDED_GUI_BUTTON_HPP