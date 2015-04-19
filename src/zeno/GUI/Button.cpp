#include <zeno/GUI/Button.hpp>

#include <zeno/GUI/GUIEvent.hpp>

#include <GL/glew.h>

#include <iostream>

#define NUM_VERTEXES 12

namespace zeno {

Button::Button(const std::string& _id) :
GuiBase(_id), 
m_BackgroundDefaultColour(Colour::Cyan),
m_BackgroundDepressedColour(Colour::Yellow),
m_ForegroundDefaultColour(Colour::Magenta),
m_ForegroundHoverColour(Colour::Red),
m_State(State::DEFAULT),
m_Depressed(false),
m_MouseContained(false),
m_OutlineThickness(4.0f)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	
	//~ Positions
	glGenBuffers(1, &m_PositionVBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NUM_VERTEXES * 3, nullptr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//~ Colours
	glGenBuffers(1, &m_ColourVBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NUM_VERTEXES * 4, nullptr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);


	m_Bounds = FloatRect(Vector2f(50.0f, 50.0f), Vector2f(100.0f, 100.0f));

	resendPositions();
	resendColours();
}

Button::~Button(void)
{

}

bool Button::processEvent(const GUIEvent& _event)
{
	//~ TODO	-	Optimise away bounds checking in the click/release, keep track of if it is within in MouseMove if block
	if (m_MouseContained && _event.type == GUIEvent::EventType::LeftClick)
	{
		m_Depressed = true;
		changeState(State::DEPRESSED);
		return true;
	}
	else if (m_MouseContained && _event.type == GUIEvent::EventType::LeftRelease)
	{
		if (m_Depressed)
		{
			//~ Only call the function if it has been set
			if (m_ActivationFunction) m_ActivationFunction();
			m_Depressed = false;
			changeState(State::HOVER);
		}
		m_Depressed = false;

		return true;

	}
	else if (_event.type == GUIEvent::EventType::MouseMove)
	{
		if (m_Bounds.contains(Vector2f(static_cast<float>(_event.mouseMove.x), static_cast<float>(_event.mouseMove.y))))
		{
			if (!m_Depressed)
			{
				changeState(State::HOVER);
				m_MouseContained = true;
				return true;
			}
		}
		else if (m_MouseContained)
		{
			m_MouseContained = false;
			m_Depressed = false;
			changeState(State::DEFAULT);
		}
	}

	return false;
}

void Button::render(void) const
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXES);
	glBindVertexArray(0);
}

void Button::registerCallback(std::function<void(void)> _function)
{
	m_ActivationFunction = _function;
}

void Button::resendColours(void)
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

	Colour backgroundColour = m_BackgroundDefaultColour;
	Colour foregroundColour = m_ForegroundDefaultColour;

	switch (m_State)
	{
	case (State::HOVER):
		backgroundColour = m_BackgroundDefaultColour;
		foregroundColour = m_ForegroundHoverColour;
		break;
	case (State::DEPRESSED):
		backgroundColour = m_BackgroundDepressedColour;
		foregroundColour = m_ForegroundHoverColour;
		break;
	default:
		break;
	}

	std::vector<float> data = {
		//~ Background colours
		backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a,
		backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a,
		backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a,
		
		backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a,
		backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a,
		backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a,

		//~ Foreground colours
		foregroundColour.r, foregroundColour.g, foregroundColour.b, foregroundColour.a,
		foregroundColour.r, foregroundColour.g, foregroundColour.b, foregroundColour.a,
		foregroundColour.r, foregroundColour.g, foregroundColour.b, foregroundColour.a,
		
		foregroundColour.r, foregroundColour.g, foregroundColour.b, foregroundColour.a,
		foregroundColour.r, foregroundColour.g, foregroundColour.b, foregroundColour.a,
		foregroundColour.r, foregroundColour.g, foregroundColour.b, foregroundColour.a
	};

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}
void Button::resendPositions(void)
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

	std::vector<float> data = {
		//~ Background positions
		m_Bounds.left,						m_Bounds.bot,						0.0f,
		m_Bounds.left + m_Bounds.width,		m_Bounds.bot,						0.0f,
		m_Bounds.left + m_Bounds.width,		m_Bounds.bot + m_Bounds.height,		0.0f,

		m_Bounds.left,						m_Bounds.bot,						0.0f,
		m_Bounds.left + m_Bounds.width,		m_Bounds.bot + m_Bounds.height,		0.0f,
		m_Bounds.left,						m_Bounds.bot + m_Bounds.height,		0.0f,

		//~ Foreground positions
		m_Bounds.left + m_OutlineThickness,						m_Bounds.bot + m_OutlineThickness,						0.1f,
		m_Bounds.left + m_Bounds.width - m_OutlineThickness,	m_Bounds.bot + m_OutlineThickness,						0.1f,
		m_Bounds.left + m_Bounds.width - m_OutlineThickness,	m_Bounds.bot + m_Bounds.height - m_OutlineThickness,	0.1f,

		m_Bounds.left + m_OutlineThickness,						m_Bounds.bot + m_OutlineThickness,						0.1f,
		m_Bounds.left + m_Bounds.width - m_OutlineThickness,	m_Bounds.bot + m_Bounds.height - m_OutlineThickness,	0.1f,
		m_Bounds.left + m_OutlineThickness,						m_Bounds.bot + m_Bounds.height - m_OutlineThickness,	0.1f
	};

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}
void Button::changeState(State _newState)
{
	if (m_State != _newState)
	{
		m_State = _newState;

		resendColours();
	}
}

} //~ namespace zeno