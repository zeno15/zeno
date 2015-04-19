#ifndef INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP
#define INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP

#include <zeno/GUI/GUIEvent.hpp>
#include <zeno/GUI/GuiPane.hpp>
#include <zeno/System/Vector2.hpp>

#include <vector>

namespace zeno {

class GuiBase;
class Time;
class Event;

////////////////////////////////////////////////////////////
//
//	Class which manages all gui components for a window
//
////////////////////////////////////////////////////////////
class GuiDesktop
{
public:
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	GuiDesktop(void);
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	~GuiDesktop(void);

	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	void processEvent(const Event& _event) const;
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	void render(void);

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
	void setResolution(unsigned int _x, unsigned int _y);

	////////////////////////////////////////////////////////////
	//
	//
	//
	////////////////////////////////////////////////////////////
	void setResolution(const Vector2u& _resolution);
	
	////////////////////////////////////////////////////////////
	//
	//
	//
	////////////////////////////////////////////////////////////
	void throwEvent(const GUIEvent& _guiEvent);


	void addPane(const std::string& _name);

	GuiPane& getPane(const std::string& _id);


private:
	////////////////////////////////////////////////////////////
	//
	//	Translates a window event to a guiEvent, returns whether
	//	or not it was able to be translated
	//
	////////////////////////////////////////////////////////////
	bool translateEvent(const Event& _event, GUIEvent& _guiEvent) const;

private:
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	std::vector<GuiBase *>		m_Children;

	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	Vector2u					m_Resolution;



	std::vector<GuiPane>		m_Panes;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_GUI_DESKTOP_HPP