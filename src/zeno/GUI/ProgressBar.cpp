#include  <zeno/GUI/ProgressBar.hpp>

#include <zeno/GUI/GUIEvent.hpp>

#include <GL/glew.h>
#include <iostream>

#define THICK 5.0f
#define NUM_QUAD_VERTICIES 6

namespace zeno {

ProgressBar::ProgressBar(void) :
m_Size(200.0f, 100.0f),
m_Position(50.0f, 50.0f),
m_CurrentPercentage(0.0f),
m_OutlineColour(Colour::Blue),
m_IncompleteColour(Colour::Green),
m_CompleteColour(Colour::Cyan)
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
		m_Position.x + THICK,	m_Position.y + THICK,				0.2f,
		m_Position.x + THICK,	m_Position.y + THICK,				0.2f,
		m_Position.x + THICK,	m_Position.y + m_Size.y - THICK,	0.2f,
		m_Position.x + THICK,	m_Position.y + THICK,				0.2f,
		m_Position.x + THICK,	m_Position.y + m_Size.y - THICK,	0.2f,
		m_Position.x + THICK,	m_Position.y + m_Size.y - THICK,	0.2f,

		//~ Incomplete position
		m_Position.x + THICK,				m_Position.y + THICK,				0.1f,
		m_Position.x + m_Size.x - THICK,	m_Position.y + THICK,				0.1f,
		m_Position.x + m_Size.x - THICK,	m_Position.y + m_Size.y - THICK,	0.1f,
		m_Position.x + THICK,				m_Position.y + THICK,				0.1f,
		m_Position.x + m_Size.x - THICK,	m_Position.y + m_Size.y - THICK,	0.1f,
		m_Position.x + THICK,				m_Position.y + m_Size.y - THICK,	0.1f
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
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//~ position
	glGenBuffers(1, &positionVBO);

	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(dataV), dataV, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


	//~ colour
	glGenBuffers(1, &colourVBO);

	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(dataC), dataC, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);


	resendData(m_CurrentPercentage);
}

ProgressBar::~ProgressBar(void)
{
}


bool ProgressBar::processEvent(const GUIEvent& _event)
{
	if (_event.type == GUIEvent::ProgressUpdate)
	{
		m_CurrentPercentage = _event.progress.progress;
		resendData(m_CurrentPercentage);
		return true;
	}
	return false;
}

void ProgressBar::render(void) const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, NUM_QUAD_VERTICIES * 3);
	glBindVertexArray(0);
}

void ProgressBar::changeOutlineColour(const Colour& _colour)
{
	std::vector<float> data;

	for (unsigned int i = 0; i < NUM_QUAD_VERTICIES; i += 1)
	{
		data.push_back(_colour.r);
		data.push_back(_colour.g);
		data.push_back(_colour.b);
		data.push_back(_colour.a);
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(float), data.data());
}
void ProgressBar::changeIncompleteColour(const Colour& _colour)
{
	std::vector<float> data;

	for (unsigned int i = 0; i < NUM_QUAD_VERTICIES; i += 1)
	{
		data.push_back(_colour.r);
		data.push_back(_colour.g);
		data.push_back(_colour.b);
		data.push_back(_colour.a);
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferSubData(GL_ARRAY_BUFFER, data.size() * sizeof(float) * 2, data.size() * sizeof(float), data.data());
}
void ProgressBar::changeCompleteColour(const Colour& _colour)
{
	std::vector<float> data;

	for (unsigned int i = 0; i < NUM_QUAD_VERTICIES; i += 1)
	{
		data.push_back(_colour.r);
		data.push_back(_colour.g);
		data.push_back(_colour.b);
		data.push_back(_colour.a);
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferSubData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.size() * sizeof(float), data.data());
}

void ProgressBar::setPosition(const Vector2f& _position)
{
	m_Position = _position;
	recreate();
}
void ProgressBar::setSize(const Vector2f& _size)
{
	m_Size = _size;
	recreate();
}

void ProgressBar::resendData(float _percent)
{
	float length = (m_Size.x - 2.0f * THICK) * _percent;

	GLfloat g_vertex_buffer_data[] = {
		m_Position.x + THICK,				m_Position.y + THICK,				0.2f,
		m_Position.x + THICK + length,		m_Position.y + THICK,				0.2f,
		m_Position.x + THICK + length,		m_Position.y + m_Size.y - THICK,	0.2f,
		m_Position.x + THICK,				m_Position.y + THICK,				0.2f,
		m_Position.x + THICK + length,		m_Position.y + m_Size.y - THICK,	0.2f,
		m_Position.x + THICK,				m_Position.y + m_Size.y - THICK,	0.2f,
	};
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
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
		m_Position.x + THICK,				m_Position.y + THICK,				0.2f,
		m_Position.x + THICK,				m_Position.y + THICK,				0.2f,
		m_Position.x + THICK,				m_Position.y + m_Size.y - THICK,	0.2f,
		m_Position.x + THICK,				m_Position.y + THICK,				0.2f,
		m_Position.x + THICK,				m_Position.y + m_Size.y - THICK,	0.2f,
		m_Position.x + THICK,				m_Position.y + m_Size.y - THICK,	0.2f,

		//~ Incomplete position
		m_Position.x + THICK,				m_Position.y + THICK,				0.1f,
		m_Position.x + m_Size.x - THICK,	m_Position.y + THICK,				0.1f,
		m_Position.x + m_Size.x - THICK,	m_Position.y + m_Size.y - THICK,	0.1f,
		m_Position.x + THICK,				m_Position.y + THICK,				0.1f,
		m_Position.x + m_Size.x - THICK,	m_Position.y + m_Size.y - THICK,	0.1f,
		m_Position.x + THICK,				m_Position.y + m_Size.y - THICK,	0.1f
	};
	
	//~ position
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(dataV), dataV);

	resendData(m_CurrentPercentage);
}

} //~ namespace zeno