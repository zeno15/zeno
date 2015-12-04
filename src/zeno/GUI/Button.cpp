#include <zeno/GUI/Button.hpp>

#include <zeno/GUI/GUIEvent.hpp>
#include <zeno/GUI/Label.hpp>

#include <zeno/Graphics/Font.hpp>
#include <zeno/Graphics/ShaderManager.hpp>

#include <GL/glew.h>

#include <iostream>

#define NUM_VERTEXES 12

namespace zeno {

Button::Button(const std::string& _id, GuiBase *_parent, Desktop& _desktop) :
GuiBase(_id, _parent, _desktop),
m_BackgroundDefaultColour(Colour::Cyan),
m_BackgroundDepressedColour(Colour::Yellow),
m_ForegroundDefaultColour(Colour::Magenta),
m_ForegroundHoverColour(Colour::Red),
m_State(State::DEFAULT),
m_Depressed(false),
m_MouseContained(false),
m_OutlineThickness(4.0f),
m_Label(nullptr)
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


	m_Bounds = FloatRect(Vector2f(), Vector2f(100.0f, 100.0f));

	move(zeno::Vector3f(m_Bounds.left, m_Bounds.bot, 0.0f));

	resendPositions();
	resendColours();
}

Button::~Button(void)
{
}

bool Button::processEvent(const GUIEvent& _event)
{
    //~ TODO - better way of modifying the bounds of the button

    m_Bounds.left   = getTransform()[12];
    m_Bounds.bot    = getTransform()[13];



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

void Button::render(Mat4x4 _transform) const
{
	Shader& shader = ShaderManager::getInstance().getShader("GUI");

	Mat4x4 trans = _transform * getTransform();

	shader.bind();
	shader.passUniform("View", trans);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXES);
	glBindVertexArray(0);

	shader.unbind();
}

FloatRect Button::getBounds(void)
{
	Vector2f  pos(m_Bounds.left + getPosition().x, m_Bounds.bot + getPosition().y);
	Vector2f size(m_Bounds.width, m_Bounds.height);

	return FloatRect(pos, size);
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
		0.0f,											0.0f,											0.0f,
		0.0f + m_Bounds.width,							0.0f,											0.0f,
		0.0f + m_Bounds.width,							0.0f + m_Bounds.height,							0.0f,

		0.0f,											0.0f,											0.0f,
		0.0f + m_Bounds.width,							0.0f + m_Bounds.height,							0.0f,
		0.0f,											0.0f + m_Bounds.height,							0.0f,

		//~ Foreground positions
		0.0f + m_OutlineThickness,						0.0f + m_OutlineThickness,						0.1f,
		0.0f + m_Bounds.width - m_OutlineThickness,		0.0f + m_OutlineThickness,						0.1f,
		0.0f + m_Bounds.width - m_OutlineThickness,		0.0f + m_Bounds.height - m_OutlineThickness,	0.1f,

		0.0f + m_OutlineThickness,						0.0f + m_OutlineThickness,						0.1f,
		0.0f + m_Bounds.width - m_OutlineThickness,		0.0f + m_Bounds.height - m_OutlineThickness,	0.1f,
		0.0f + m_OutlineThickness,						0.0f + m_Bounds.height - m_OutlineThickness,	0.1f
	};

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}

void Button::setSize(const Vector2f& _size)
{
    m_Bounds.width = _size.x;
    m_Bounds.height = _size.y;

    resendPositions();
}

void Button::setOutlineThickness(float _thickness)
{
    m_OutlineThickness = _thickness;

    resendPositions();
}

void Button::setBackgroundDefaultColour(const zeno::Colour& _col)
{
    m_BackgroundDefaultColour = _col;

    resendColours();
}
void Button::setBackgroundDepressedColour(const zeno::Colour& _col)
{
    m_BackgroundDepressedColour = _col;

    resendColours();
}
void Button::setForegroundDefaultColour(const zeno::Colour& _col)
{
    m_ForegroundDefaultColour = _col;

    resendColours();
}
void Button::setForegroundHoverColour(const zeno::Colour& _col)
{
    m_ForegroundHoverColour = _col;

    resendColours();
}

void Button::changeState(State _newState)
{
	if (m_State != _newState)
	{
		m_State = _newState;

		resendColours();
	}
}

void Button::addLabel(const std::string& _labelString, Font *_font)
{
    throw std::runtime_error("Need to change new label to use the child heirachy");
    /*
	if (m_Label != nullptr)
	{
		delete m_Label;
	}

	m_Label = new Label(m_Id + _labelString, this, _font);
	m_Label->move(Vector3f(0.0f, 0.0f, 0.2f));

	m_Label->setLabel(_labelString);

	m_Bounds.width = m_Label->getBounds().width + m_OutlineThickness * 4.0f + m_Label->getBounds().left;
	m_Bounds.height = m_Label->getBounds().height + m_OutlineThickness * 4.0f + m_Label->getBounds().bot;

	resendPositions();
     */
}

Button *Button::createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop)
{
    return new Button(_id, _parent, _desktop);
}

void Button::initialise(void)
{

}


} //~ namespace zeno