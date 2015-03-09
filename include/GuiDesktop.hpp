#ifndef INCLUDED_GUI_DESKTOP_HPP
#define INCLUDED_GUI_DESKTOP_HPP

#include <vector>

namespace zeno {

class GuiBase;
class Time;

class GuiDesktop
{
public:
	GuiDesktop(void);
	~GuiDesktop(void);

	void update(const Time& _delta);
	void render(void);

	void addChild(GuiBase *_child);

private:
	std::vector<GuiBase *>		m_Children;

};

} //~ namespace zeno

#endif //~ INCLUDED_GUI_DESKTOP_HPP