#ifndef INCLUDED_ZENO_GUI_GUI_BASE_HPP
#define INCLUDED_ZENO_GUI_GUI_BASE_HPP

#include <string>
#include <vector>

namespace zeno {

class GUIEvent;

////////////////////////////////////////////////////////////
//
//	Base for all GUI elements
//
////////////////////////////////////////////////////////////
class GuiBase
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor
	//
	////////////////////////////////////////////////////////////
	GuiBase(const std::string& _id);
	////////////////////////////////////////////////////////////
	//
	//	Deconstructor
	//
	////////////////////////////////////////////////////////////
	virtual ~GuiBase(void);

	////////////////////////////////////////////////////////////
	//
	//	Virtual function which returns whether or not the 
	//	element can handle the given event, and if it can handle
	//	it, it does so
	//
	////////////////////////////////////////////////////////////
	virtual bool processEvent(const GUIEvent& _event) = 0;
	////////////////////////////////////////////////////////////
	//
	//	Renders the element
	//
	////////////////////////////////////////////////////////////
	virtual void render(void) const = 0;

	////////////////////////////////////////////////////////////
	//
	//	Sets the active state
	//
	////////////////////////////////////////////////////////////
	void setActive(bool _active);

	////////////////////////////////////////////////////////////
	//
	//	Returns the elements active state
	//
	////////////////////////////////////////////////////////////
	bool getActive(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Adds a child to the element
	//
	////////////////////////////////////////////////////////////
	void addChild(GuiBase *_child);

	////////////////////////////////////////////////////////////
	//
	//	Returns whether the element has children or not
	//
	////////////////////////////////////////////////////////////
	bool hasChildren(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Gets the list of children
	//
	////////////////////////////////////////////////////////////
	std::vector<GuiBase *> getChildren(void);

	////////////////////////////////////////////////////////////
	//
	//	Gets the id of the base
	//
	////////////////////////////////////////////////////////////
	std::string getId(void);

protected:
	////////////////////////////////////////////////////////////
	//
	//	The elements state (enabled or not)
	//
	////////////////////////////////////////////////////////////
	bool						m_Active;

	////////////////////////////////////////////////////////////
	//
	//	List of children elements attached to this element
	//
	////////////////////////////////////////////////////////////
	std::vector<GuiBase *>		m_Children;
	
	////////////////////////////////////////////////////////////
	//
	//	Unique id for gui component, cannot be the same as any
	//	other component on the same level
	//
	////////////////////////////////////////////////////////////
	std::string					m_Id;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_GUI_BASE_HPP