#ifndef INCLUDED_ZENO_GUI_PROGRESS_BAR_HPP
#define INCLUDED_ZENO_GUI_PROGRESS_BAR_HPP

#include <zeno/GUI/GuiBase.hpp>

#include <zeno/Graphics/Vertex.hpp>

#include <vector>

namespace zeno {

class ProgressBar : public GuiBase
{
public:
	////////////////////////////////////////////////////////////
	//
	//
	//
	////////////////////////////////////////////////////////////
	ProgressBar(void);
	
	////////////////////////////////////////////////////////////
	//
	//
	//
	////////////////////////////////////////////////////////////
	~ProgressBar(void);

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
	virtual void render(void) const;

	void changeOutlineColour(const Colour& _colour);
	void changeIncompleteColour(const Colour& _colour);
	void changeCompleteColour(const Colour& _colour);

	void setPosition(const Vector2f& _position);
	void setSize(const Vector2f& _size);

private:
	void resendData(float _percent);

	void recreate(void);

private:
	Vector2f				m_Size;
	Vector2f				m_Position;

	float					m_CurrentPercentage;

	unsigned int VAO;
	
	unsigned int positionVBO;
	unsigned int colourVBO;

	Colour	m_OutlineColour;
	Colour	m_IncompleteColour;
	Colour	m_CompleteColour;

};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GUI_PROGRESS_BAR_HPP

