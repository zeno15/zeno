#include <zeno/GUI/ProgressBar.hpp>

#include <zeno/GUI/GUIEvent.hpp>

#include <zeno/Graphics/ShaderManager.hpp>

#include <GL/glew.h>
#include <iostream>

#define NUM_QUAD_VERTICIES 6

#define DEFAULT_OUTLINE		Colour::Blue
#define DEFAULT_INCOMPLETE	Colour::Green
#define DEFAULT_COMPLETE	Colour::Cyan

namespace zeno {

ProgressBar::ProgressBar(const std::string& _id, GuiBase *_parent, Desktop& _desktop) :
GuiBase(_id, _parent, _desktop),
m_Size(200.0f, 100.0f),
m_Position(50.0f, 50.0f),
m_CurrentPercentage(0.0f),
m_OutlineThickness(1.0f)
{

	static const GLfloat dataV[] = {
		//~ Outline position
		m_Position.x,				m_Position.y,				0.0f,
		m_Position.x + m_Size.x,	m_Position.y,				0.0f,
		m_Position.x + m_Size.x,	m_Position.y + m_Size.y,	0.0f,
		m_Position.x,				m_Position.y,				0.0f,
		m_Position.x + m_Size.x,	m_Position.y + m_Size.y,	0.0f,
		m_Position.x,				m_Position.y + m_Size.y,	0.0f,

		//~ Complete position
		m_Position.x + m_OutlineThickness,	m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness,	m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness,	m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,
		m_Position.x + m_OutlineThickness,	m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness,	m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,
		m_Position.x + m_OutlineThickness,	m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,

		//~ Incomplete position
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.1f,
		m_Position.x + m_Size.x - m_OutlineThickness,	m_Position.y + m_OutlineThickness,				0.1f,
		m_Position.x + m_Size.x - m_OutlineThickness,	m_Position.y + m_Size.y - m_OutlineThickness,	0.1f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.1f,
		m_Position.x + m_Size.x - m_OutlineThickness,	m_Position.y + m_Size.y - m_OutlineThickness,	0.1f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_Size.y - m_OutlineThickness,	0.1f
	};

	static const GLfloat dataC[] = {
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f
	};
	
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	//~ position
	glGenBuffers(1, &m_PositionVBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(dataV), dataV, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


	//~ colour
	glGenBuffers(1, &m_ColourVBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6 * 3, nullptr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	changeOutlineColour(DEFAULT_OUTLINE);
	changeIncompleteColour(DEFAULT_INCOMPLETE);
	changeCompleteColour(DEFAULT_COMPLETE);

	resendData(m_CurrentPercentage);
}

ProgressBar::~ProgressBar(void)
{
	glDeleteBuffers(1, &m_PositionVBO);
	glDeleteBuffers(1, &m_ColourVBO);
	glDeleteVertexArrays(1, &m_VAO);
}


bool ProgressBar::processEvent(const GUIEvent& _event)
{
	return false;
}

void ProgressBar::render(Mat4x4 _transform) const
{
	Shader& shader = ShaderManager::getInstance().getShader("GUI");

	shader.bind();
	shader.passUniform("View", _transform);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, NUM_QUAD_VERTICIES * 3);
	glBindVertexArray(0);

	shader.unbind();
}

FloatRect ProgressBar::getBounds(void)
{
	std::cout << "TODO" << std::endl;

	return FloatRect();
}

void ProgressBar::changeOutlineColour(const Colour& _colour)
{
	if (m_OutlineColour != _colour)
	{
		m_OutlineColour = _colour;

		std::vector<float> data;

		for (unsigned int i = 0; i < NUM_QUAD_VERTICIES; i += 1)
		{
			data.push_back(m_OutlineColour.r);
			data.push_back(m_OutlineColour.g);
			data.push_back(m_OutlineColour.b);
			data.push_back(m_OutlineColour.a);
		}

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(float), data.data());
	}
}
void ProgressBar::changeIncompleteColour(const Colour& _colour)
{
	if (m_IncompleteColour != _colour)
	{
		m_IncompleteColour = _colour;

		std::vector<float> data;

		for (unsigned int i = 0; i < NUM_QUAD_VERTICIES; i += 1)
		{
			data.push_back(m_IncompleteColour.r);
			data.push_back(m_IncompleteColour.g);
			data.push_back(m_IncompleteColour.b);
			data.push_back(m_IncompleteColour.a);
		}

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);
		glBufferSubData(GL_ARRAY_BUFFER, data.size() * sizeof(float) * 2, data.size() * sizeof(float), data.data());
	}
}
void ProgressBar::changeCompleteColour(const Colour& _colour)
{
	if (m_CompleteColour != _colour)
	{
		m_CompleteColour = _colour;

		std::vector<float> data;

		for (unsigned int i = 0; i < NUM_QUAD_VERTICIES; i += 1)
		{
			data.push_back(m_CompleteColour.r);
			data.push_back(m_CompleteColour.g);
			data.push_back(m_CompleteColour.b);
			data.push_back(m_CompleteColour.a);
		}

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);
		glBufferSubData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.size() * sizeof(float), data.data());
	}
}

void ProgressBar::setPosition(const Vector2f& _position)
{
	if (m_Position != _position)
	{
		m_Position = _position;
		recreate();
	}
}
void ProgressBar::setSize(const Vector2f& _size)
{
	if (m_Size != _size)
	{
		m_Size = _size;
		recreate();
	}
}
void ProgressBar::setOutlineThickness(float _thickness)
{
	if (m_OutlineThickness != _thickness)
	{
		m_OutlineThickness = _thickness;
		recreate();
	}
}

void ProgressBar::setPercentage(float _perc)
{
    if (_perc != m_CurrentPercentage)
    {
        m_CurrentPercentage = _perc;
        resendData(m_CurrentPercentage);
    }
}

void ProgressBar::resendData(float _percent)
{
	float length = (m_Size.x - 2.0f * m_OutlineThickness) * _percent;

	GLfloat g_vertex_buffer_data[] = {
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness + length,		m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness + length,		m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness + length,		m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,
	};
	
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), sizeof(g_vertex_buffer_data), g_vertex_buffer_data);
	
}

void ProgressBar::recreate(void)
{
	GLfloat dataV[] = {
		//~ Outline position
		m_Position.x,						m_Position.y,						0.0f,
		m_Position.x + m_Size.x,			m_Position.y,						0.0f,
		m_Position.x + m_Size.x,			m_Position.y + m_Size.y,			0.0f,
		m_Position.x,						m_Position.y,						0.0f,
		m_Position.x + m_Size.x,			m_Position.y + m_Size.y,			0.0f,
		m_Position.x,						m_Position.y + m_Size.y,			0.0f,

		//~ Complete position
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.2f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_Size.y - m_OutlineThickness,	0.2f,

		//~ Incomplete position
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.1f,
		m_Position.x + m_Size.x - m_OutlineThickness,	m_Position.y + m_OutlineThickness,				0.1f,
		m_Position.x + m_Size.x - m_OutlineThickness,	m_Position.y + m_Size.y - m_OutlineThickness,	0.1f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_OutlineThickness,				0.1f,
		m_Position.x + m_Size.x - m_OutlineThickness,	m_Position.y + m_Size.y - m_OutlineThickness,	0.1f,
		m_Position.x + m_OutlineThickness,				m_Position.y + m_Size.y - m_OutlineThickness,	0.1f
	};
	
	//~ position
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(dataV), dataV);

	resendData(m_CurrentPercentage);
}

ProgressBar *ProgressBar::createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop)
{
    return new ProgressBar(_id, _parent, _desktop);
}

} //~ namespace zeno