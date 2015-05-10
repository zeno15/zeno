#include <zeno/GUI/TextBox.hpp>

#include <zeno/GUI/GUIEvent.hpp>

#include <GL/glew.h>

#include <iostream>

#define NUM_VERTICES 12

#define BORDER_SIZE 4.0f

#define WIDTH		100.0f
#define HEIGHT		50.0f

namespace zeno {

TextBox::TextBox(const std::string& _id) :
GuiBase(_id)
{
	recreate();
}
TextBox::~TextBox(void)
{
	glDeleteVertexArrays(1, &m_VAO);
}


bool TextBox::processEvent(const GUIEvent& _event)
{
	if (m_HasFocus)
	{
		if (_event.type == GUIEvent::EventType::LeftRelease)
		{
			if (!getBounds().contains(Vector2f(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y))))
			{
				m_HasFocus = false;
				std::cout << "Now lost focus." << std::endl;
			}
		}
		else if (_event.type == GUIEvent::EventType::TextEntered)
		{
			if (_event.text.character == 8)
			{
				std::cout << "Backspace!" << std::endl;
			}
			else if (_event.text.character == 9)
			{
				std::cout << "Tab!" << std::endl;
			}
			else if (_event.text.character == 13)
			{
				std::cout << "Enter!" << std::endl;
			}
			else if (_event.text.character == 27)
			{
				std::cout << "Escape!" << std::endl;
			}
			else {
				std::cout << "Text box received char: \"" << static_cast<char>(_event.text.character) << "\"" << std::endl;
			}
		}
	}
	else
	{
		if (_event.type == GUIEvent::EventType::LeftRelease)
		{
			if (getBounds().contains(Vector2f(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y))))
			{
				m_HasFocus = true;
				std::cout << "Now has focus." << std::endl;
			}
		}
	}
	return false;
}

void TextBox::render(Mat4x4 _transform) const
{
	Shader& shader = ShaderManager::getInstance().getShader("GUI");

	shader.bind();
	shader.passUniform("View", _transform * getTransform());

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
	glBindVertexArray(0);

	shader.unbind();
}

FloatRect TextBox::getBounds(void)
{
	Vector2f  pos(getPosition().x, getPosition().y);
	Vector2f size(WIDTH, HEIGHT);

	return FloatRect(pos, size);
}

void TextBox::recreate(void)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);


	//~ Position data

	std::vector<float> data_p = {
		//~ Outline
		0.0f,							0.0f,								0.5f,
		0.0f + WIDTH,					0.0f,								0.5f,
		0.0f + WIDTH,					0.0f + HEIGHT,						0.5f,

		0.0f,							0.0f,								0.5f,
		0.0f + WIDTH,					0.0f + HEIGHT,						0.5f,
		0.0f,							0.0f + HEIGHT,						0.5f,

		//~ Inner
		0.0f + BORDER_SIZE,				0.0f + BORDER_SIZE,					0.6f,
		0.0f + WIDTH - BORDER_SIZE,		0.0f + BORDER_SIZE,					0.6f,
		0.0f + WIDTH - BORDER_SIZE,		0.0f + HEIGHT - BORDER_SIZE,		0.6f,

		0.0f + BORDER_SIZE,				0.0f + BORDER_SIZE,					0.6f,
		0.0f + WIDTH - BORDER_SIZE,		0.0f + HEIGHT - BORDER_SIZE,		0.6f,
		0.0f + BORDER_SIZE,				0.0f + HEIGHT - BORDER_SIZE,		0.6f

	};

	unsigned int vbo_position = 0;

	glGenBuffers(1, &vbo_position);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data_p.size(), data_p.data(), GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//~ Colour data

	std::vector<float> data_c = {
		//~ Outline
		0.4f,							0.4f,								0.4f,			1.0f,
		0.4f,							0.4f,								0.4f,			1.0f,
		0.4f,							0.4f,								0.4f,			1.0f,

		0.4f,							0.4f,								0.4f,			1.0f,
		0.4f,							0.4f,								0.4f,			1.0f,
		0.4f,							0.4f,								0.4f,			1.0f,

		//~ Inner
		0.8f,							0.8f,								0.8f,			1.0f,
		0.8f,							0.8f,								0.8f,			1.0f,
		0.8f,							0.8f,								0.8f,			1.0f,

		0.8f,							0.8f,								0.8f,			1.0f,
		0.8f,							0.8f,								0.8f,			1.0f,
		0.8f,							0.8f,								0.8f,			1.0f
	};

	unsigned int vbo_colour = 0;

	glGenBuffers(1, &vbo_colour);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_colour);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data_c.size(), data_c.data(), GL_STREAM_DRAW);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colour);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
}

} //~ namespace zeno