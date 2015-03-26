#include <zeno/Graphics/Text.hpp>

#include <zeno/Graphics/ShaderManager.hpp>
#include <zeno/System/Vector4.hpp>

#include <GL/glew.h>

#include <iostream>

namespace zeno {

Text::Text(void) :
Text("", nullptr)
{
}
Text::Text(const std::string& _text, Font *_font, unsigned int _fontSize /*= 20*/) :
m_VAO(0),
m_Font(_font)
{
	setText(_text);
}
Text::~Text(void)
{
}


void Text::render(RenderData _data)
{
	Shader& shader = ShaderManager::getInstance().getShader("Zenos_Text_Shader");
	shader.bind();
	zeno::Vector2f vec;
	if (_data.texture != nullptr)
	{
		_data.texture->bind();
		 vec = zeno::Vector2f(static_cast<float>(_data.texture->getSize().x), static_cast<float>(_data.texture->getSize().y));
	}
	else
	{
		m_Font->getTexture()->bind();
		vec = zeno::Vector2f(static_cast<float>(m_Font->getTexture()->getSize().x), static_cast<float>(m_Font->getTexture()->getSize().y));
	}

	_data.transform *= getTransform();
	
	shader.passUniform("View", _data.transform);
	shader.passUniform("texSize", vec);
	shader.passUniform("textColour", Vector4f(m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_Verticies.size());
	glBindVertexArray(0);
	
	Texture::unbind();
	Shader::unbind();
}

void Text::setText(const std::string& _text)
{
	if (_text.size() == 0)
	{
		return;
	}

	m_Verticies.clear();

	m_Verticies = m_Font->createVerticies(_text);

	float *data = reinterpret_cast<float *>(m_Verticies.data());

	glDeleteVertexArrays(1, &m_VAO);
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Verticies.size(), data, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
}


void Text::setColour(const Colour& _colour)
{
	m_Colour = _colour;
}

} //~ namespace zeno