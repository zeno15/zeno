#include <zeno/GUI/TextBox.hpp>

#include <zeno/Graphics/Font.hpp>

#include <zeno/GUI/GUIEvent.hpp>

#include <GL/glew.h>

#include <iostream>

#define NUM_VERTICES 12

namespace zeno {

TextBox::TextBox(const std::string& _id, Font *_font) :
m_Font(_font),
GuiBase(_id),
m_Size(100.0f, 50.0f),
m_BorderSize(4.0f)
{
	recreate();
	m_BoxText.setColour(Colour::Black);
	m_BoxText.generateText("", m_Font);
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
			bool textChanged = false;

			if (_event.text.character == 8)
			{
				if (m_String.size() > 0)
				{
					textChanged = true;
					m_String.pop_back();
				}
			}
			else if (_event.text.character == 9)
			{
				std::cout << "Tab, not dealt with" << std::endl;
			}
			else if (_event.text.character == 13)
			{
				std::cout << "Enter, not dealt with" << std::endl;
			}
			else if (_event.text.character == 27)
			{
				std::cout << "Escape, not dealt with" << std::endl;
			}
			else 
			{
				textChanged = true;

				m_String += static_cast<char>(_event.text.character);
			}

			if (textChanged)
			{
				std::cout << "String: " << m_String << std::endl;
				m_BoxText.generateText(m_String, m_Font);

				//std::cout << "Text left: " << m_BoxText.getBounds().left << ", bottom: " << m_BoxText.getBounds().bot << ", width: " << m_BoxText.getBounds().width << ", height: " << m_BoxText.getBounds().height << std::endl;
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

	if (m_String.size() > 0)
	{
		zeno::RenderData data;
		data.transform = _transform * getTransform() * Mat4x4::createTranslation(Vector3f(m_BorderSize * 2.0f, m_BorderSize * 2.0f, 0.2f));

		m_BoxText.render(data);
	}
}

FloatRect TextBox::getBounds(void)
{
	Vector2f  pos(getPosition().x, getPosition().y);
	Vector2f size(m_Size.x, m_Size.y);

	return FloatRect(pos, size);
}

void TextBox::setSize(const Vector2f& _size)
{
    if (_size != m_Size)
    {
        m_Size = _size;
        recreate();
    }
}

void TextBox::recreate(void)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);


	//~ Position data

	std::vector<float> data_p = {
		//~ Outline
		0.0f,								0.0f,								0.0f,
		0.0f + m_Size.x,					0.0f,								0.0f,
		0.0f + m_Size.x,					0.0f + m_Size.y,					0.0f,

		0.0f,								0.0f,								0.0f,
		0.0f + m_Size.x,					0.0f + m_Size.y,					0.0f,
		0.0f,								0.0f + m_Size.y,					0.0f,

		//~ Inner
		0.0f + m_BorderSize,				0.0f + m_BorderSize,				0.1f,
		0.0f + m_Size.x - m_BorderSize,		0.0f + m_BorderSize,				0.1f,
		0.0f + m_Size.x - m_BorderSize,		0.0f + m_Size.y - m_BorderSize,		0.1f,

		0.0f + m_BorderSize,				0.0f + m_BorderSize,				0.1f,
		0.0f + m_Size.x - m_BorderSize,		0.0f + m_Size.y - m_BorderSize,		0.1f,
		0.0f + m_BorderSize,				0.0f + m_Size.y - m_BorderSize,		0.1f

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
		0.4f,					0.4f,					0.4f,				1.0f,
		0.4f,					0.4f,					0.4f,				1.0f,
		0.4f,					0.4f,					0.4f,				1.0f,

		0.4f,					0.4f,					0.4f,				1.0f,
		0.4f,					0.4f,					0.4f,				1.0f,
		0.4f,					0.4f,					0.4f,				1.0f,

		//~ Inner
		0.8f,					0.8f,					0.8f,				1.0f,
		0.8f,					0.8f,					0.8f,				1.0f,
		0.8f,					0.8f,					0.8f,				1.0f,
		
		0.8f,					0.8f,					0.8f,				1.0f,
		0.8f,					0.8f,					0.8f,				1.0f,
		0.8f,					0.8f,					0.8f,				1.0f
	};

	unsigned int vbo_colour = 0;

	glGenBuffers(1, &vbo_colour);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_colour);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data_c.size(), data_c.data(), GL_STREAM_DRAW);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colour);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
}

std::string TextBox::getText(void)
{
	return m_String;
}

void TextBox::setText(const std::string& _text)
{
	m_String = _text;

	m_BoxText.generateText(m_String, m_Font);
}
void TextBox::addText(const std::string& _text)
{
	setText(getText() + _text);
}

} //~ namespace zeno