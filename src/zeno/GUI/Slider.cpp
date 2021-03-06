#include <zeno/GUI/Slider.hpp>

#include <zeno/GUI/GUIEvent.hpp>

#include <zeno/Graphics/ShaderManager.hpp>

#include <zeno/System/Rect.hpp>

#include <GL/glew.h>
#include <vector>
#include <iostream>

#define BAR_VERTICIES	6
#define NUM_VERTEXES	12
#define LINE_HEIGHT		2.0f
#define SLIDE_HEIGHT	20.0f
#define SLIDE_WIDTH		12.0f



namespace zeno {

Slider::Slider(const std::string& _id, GuiBase *_parent, Desktop& _desktop) :
GuiBase(_id, _parent, _desktop),
m_NumDiscreteValues(6),
m_BarColour(0.5f, 0.5f, 0.5f),
m_DefaultSlideColour(0.6f, 0.6f, 0.6f),
m_HoverSlideColour(Colour::Yellow),
m_HeldSlideColour(Colour::Green),
m_Position(0.0f, 0.0f),
m_Length(100.0f),
m_SlideOffsetPercent(0.0f),
m_HasSlide(false),
m_MouseContained(false),
m_Continuous(true),
m_State(State::HOVER)
{
	glGenVertexArrays(1, &m_VAO);

	recreate();
}
Slider::~Slider(void)
{
	glDeleteBuffers(1, &m_PositionVBO);
	glDeleteBuffers(1, &m_ColourVBO);
	glDeleteVertexArrays(1, &m_VAO);
}


bool Slider::processEvent(const GUIEvent& _event)
{
    float x = getTransform()[12];
    float y = getTransform()[13];

	if (m_HasSlide)
	{
		if (_event.type == GUIEvent::EventType::LeftRelease)
		{
			m_HasSlide = false;

			FloatRect slideBounds(Vector2f(x, y) - Vector2f(SLIDE_WIDTH, SLIDE_HEIGHT) * 0.5f + Vector2f(m_SlideOffsetPercent * m_Length, 0.0f), Vector2f(SLIDE_WIDTH, SLIDE_HEIGHT));

			if (slideBounds.contains(Vector2f(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y))))
			{
				resendColours(State::HOVER);
			}
			else
			{
				resendColours(State::DEFAULT);
			}
			
		}
		else if (_event.type == GUIEvent::EventType::MouseMove)
		{
			float newX = static_cast<float>(_event.mouseMove.x);

			if (newX < x)
			{
				newX = x;
			}
			if (newX > x + m_Length)
			{
				newX = x + m_Length;
			}

			float newPercent = calculateDiscretePosition((newX - x) / m_Length);

			if (newPercent != m_SlideOffsetPercent)
			{
				m_SlideOffsetPercent = newPercent;
				resendPositions();

				//~ Don't call it if it doesn't exist
				if (m_ChangeFunction) m_ChangeFunction(newPercent);
			}
		}
	}
	else
	{
		if (_event.type == GUIEvent::EventType::MouseMove)
		{
			FloatRect slideBounds(Vector2f(x, y) - Vector2f(SLIDE_WIDTH, SLIDE_HEIGHT) * 0.5f + Vector2f(m_SlideOffsetPercent * m_Length, 0.0f), Vector2f(SLIDE_WIDTH, SLIDE_HEIGHT));

			if (slideBounds.contains(Vector2f(static_cast<float>(_event.mouseMove.x), static_cast<float>(_event.mouseMove.y))))
			{
				m_MouseContained = true;

				resendColours(State::HOVER);
			}
			else
			{
				m_MouseContained = false;
				
				resendColours(State::DEFAULT);
			}
		}
		else if (_event.type == GUIEvent::EventType::LeftClick)
		{
			if (m_MouseContained)
			{
				m_HasSlide = true;

				resendColours(State::HELD);
			}
		}
	}
	

	return false;
}

void Slider::render(Mat4x4 _transform) const
{
	Shader& shader = ShaderManager::getInstance().getShader("GUI");

    _transform *= getTransform();

	shader.bind();
	shader.passUniform("View", _transform);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXES + (m_Continuous ? 0 : (m_NumDiscreteValues - 2) * 6));
	glBindVertexArray(0);

	shader.unbind();
}

void Slider::registerCallback(std::function<void(float)> _function)
{
	m_ChangeFunction = _function;
}

void Slider::recreate(void)
{
	glBindVertexArray(m_VAO);

	int TotalVertexCount = NUM_VERTEXES + (m_Continuous ? 0 : (m_NumDiscreteValues - 2) * 6);



	//~ Positions
	glGenBuffers(1, &m_PositionVBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * TotalVertexCount * 3, nullptr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//~ Colours
	glGenBuffers(1, &m_ColourVBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * TotalVertexCount * 4, nullptr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);



	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

	std::vector<float> posData = {
		m_Position.x,				m_Position.y - LINE_HEIGHT / 2.0f,		0.0f,
		m_Position.x + m_Length,	m_Position.y - LINE_HEIGHT / 2.0f,		0.0f,
		m_Position.x + m_Length,	m_Position.y + LINE_HEIGHT / 2.0f,		0.0f,

		m_Position.x,				m_Position.y - LINE_HEIGHT / 2.0f,		0.0f,
		m_Position.x + m_Length,	m_Position.y + LINE_HEIGHT / 2.0f,		0.0f,
		m_Position.x,				m_Position.y + LINE_HEIGHT / 2.0f,		0.0f
	};

	//~ Add segment data here
	unsigned int count = (m_Continuous ? 0 : (m_NumDiscreteValues - 2));

	std::vector<float> pdata;

	float segOffset = m_Length / static_cast<float>(m_NumDiscreteValues - 1);

	for (unsigned int i = 0; i < count; i += 1)
	{
		pdata.push_back(m_Position.x + (i + 1) * segOffset - SLIDE_WIDTH / 8.0f);	pdata.push_back(m_Position.y - SLIDE_HEIGHT - SLIDE_HEIGHT / 4.0f);	pdata.push_back(0.5f);
		pdata.push_back(m_Position.x + (i + 1) * segOffset + SLIDE_WIDTH / 8.0f);	pdata.push_back(m_Position.y - SLIDE_HEIGHT - SLIDE_HEIGHT / 4.0f);	pdata.push_back(0.5f);
		pdata.push_back(m_Position.x + (i + 1) * segOffset + SLIDE_WIDTH / 8.0f);	pdata.push_back(m_Position.y - SLIDE_HEIGHT + SLIDE_HEIGHT / 4.0f);	pdata.push_back(0.5f);

		pdata.push_back(m_Position.x + (i + 1) * segOffset - SLIDE_WIDTH / 8.0f);	pdata.push_back(m_Position.y - SLIDE_HEIGHT - SLIDE_HEIGHT / 4.0f);	pdata.push_back(0.5f);
		pdata.push_back(m_Position.x + (i + 1) * segOffset + SLIDE_WIDTH / 8.0f);	pdata.push_back(m_Position.y - SLIDE_HEIGHT + SLIDE_HEIGHT / 4.0f);	pdata.push_back(0.5f);
		pdata.push_back(m_Position.x + (i + 1) * segOffset - SLIDE_WIDTH / 8.0f);	pdata.push_back(m_Position.y - SLIDE_HEIGHT + SLIDE_HEIGHT / 4.0f);	pdata.push_back(0.5f);
	}
	

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * posData.size(), posData.data());

	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * posData.size(), sizeof(GLfloat) * pdata.size(), pdata.data());

	glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

	std::vector<float> colData = {
		m_BarColour.r, m_BarColour.g, m_BarColour.b, m_BarColour.a,
		m_BarColour.r, m_BarColour.g, m_BarColour.b, m_BarColour.a,
		m_BarColour.r, m_BarColour.g, m_BarColour.b, m_BarColour.a,

		m_BarColour.r, m_BarColour.g, m_BarColour.b, m_BarColour.a,
		m_BarColour.r, m_BarColour.g, m_BarColour.b, m_BarColour.a,
		m_BarColour.r, m_BarColour.g, m_BarColour.b, m_BarColour.a,
	};

	for (unsigned int i = 0; i < count; i += 1)
	{
		colData.push_back(m_BarColour.r);	colData.push_back(m_BarColour.g);	colData.push_back(m_BarColour.b);	colData.push_back(m_BarColour.a);
		colData.push_back(m_BarColour.r);	colData.push_back(m_BarColour.g);	colData.push_back(m_BarColour.b);	colData.push_back(m_BarColour.a);
		colData.push_back(m_BarColour.r);	colData.push_back(m_BarColour.g);	colData.push_back(m_BarColour.b);	colData.push_back(m_BarColour.a);

		colData.push_back(m_BarColour.r);	colData.push_back(m_BarColour.g);	colData.push_back(m_BarColour.b);	colData.push_back(m_BarColour.a);
		colData.push_back(m_BarColour.r);	colData.push_back(m_BarColour.g);	colData.push_back(m_BarColour.b);	colData.push_back(m_BarColour.a);
		colData.push_back(m_BarColour.r);	colData.push_back(m_BarColour.g);	colData.push_back(m_BarColour.b);	colData.push_back(m_BarColour.a);
	}

	//~ Add segment data here

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * colData.size(), colData.data());

	resendPositions();
	resendColours(State::DEFAULT);
}

FloatRect Slider::getBounds(void)
{
    std::cout << "TODO: Slider::getBounds()" << std::endl;

    return FloatRect();
}

void Slider::resendPositions(void)
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

	std::vector<float>	data = {
		m_Position.x - SLIDE_WIDTH / 2.0f + m_SlideOffsetPercent * m_Length,		m_Position.y - SLIDE_HEIGHT / 2.0f,		0.1f,
		m_Position.x + SLIDE_WIDTH / 2.0f + m_SlideOffsetPercent * m_Length,		m_Position.y - SLIDE_HEIGHT / 2.0f,		0.1f,
		m_Position.x + SLIDE_WIDTH / 2.0f + m_SlideOffsetPercent * m_Length,		m_Position.y + SLIDE_HEIGHT / 2.0f,		0.1f,

		m_Position.x - SLIDE_WIDTH / 2.0f + m_SlideOffsetPercent * m_Length,		m_Position.y - SLIDE_HEIGHT / 2.0f,		0.1f,
		m_Position.x + SLIDE_WIDTH / 2.0f + m_SlideOffsetPercent * m_Length,		m_Position.y + SLIDE_HEIGHT / 2.0f,		0.1f,
		m_Position.x - SLIDE_WIDTH / 2.0f + m_SlideOffsetPercent * m_Length,		m_Position.y + SLIDE_HEIGHT / 2.0f,		0.1f
	};

	glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (BAR_VERTICIES + (m_Continuous ? 0 : (m_NumDiscreteValues - 2) * 6)) * 3, sizeof(GLfloat) * data.size(), data.data());
}
void Slider::resendColours(State _state)
{
	if (_state != m_State)
	{
		m_State = _state;

		Colour colour = m_DefaultSlideColour;

		switch (m_State)
		{
		case (State::HOVER):
			colour = m_HoverSlideColour;
			break;
		case (State::HELD):
			colour = m_HeldSlideColour;
			break;
		default:
			break;
		}

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

		std::vector<float>	data = {
			colour.r, colour.g, colour.b, colour.a,
			colour.r, colour.g, colour.b, colour.a,
			colour.r, colour.g, colour.b, colour.a,
			
			colour.r, colour.g, colour.b, colour.a,
			colour.r, colour.g, colour.b, colour.a,
			colour.r, colour.g, colour.b, colour.a
		};

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (BAR_VERTICIES + (m_Continuous ? 0 : (m_NumDiscreteValues - 2) * 6)) * 4, sizeof(GLfloat) * data.size(), data.data());
	}
}

float Slider::calculateDiscretePosition(float _continuousPosition)
{
	if (m_Continuous)
	{
		return _continuousPosition;
	}

	//~ Substract 1 so that the end counts as a position
	float discreteDistance = 1.0f / static_cast<float>(m_NumDiscreteValues - 1);

	float discreteValue = _continuousPosition / discreteDistance;
	
	return floorf(discreteValue + 0.5f) * discreteDistance;
}

Slider *Slider::createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop)
{
    return new Slider(_id, _parent, _desktop);
}

void Slider::initialise(void)
{

}

} //~ namespace zeno