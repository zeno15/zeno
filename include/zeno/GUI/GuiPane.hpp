#ifndef INCLUDED_ZENO_GUI_GUI_PANE_HPP
#define INCLUDED_ZENO_GUI_GUI_PANE_HPP

#include <zeno/GUI/GuiBase.hpp>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	
//
////////////////////////////////////////////////////////////
class GuiPane : public GuiBase
{
public:
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	GuiPane(const std::string& _id);

	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	~GuiPane(void);

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
	
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	void addChild(GuiBase *_child);
	
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	//~ Need to change this to return a type specific reference
	GuiBase *getChild(const std::string& _id);

protected:
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	std::vector<GuiBase *>		m_Children;

};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_GUI_PANE_HPP