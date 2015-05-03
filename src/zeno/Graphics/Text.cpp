#include <zeno/Graphics/Text.hpp>

#include <zeno/Graphics/Font.hpp>
#include <zeno/Graphics/ShaderManager.hpp>

#include <GL/glew.h>

#include <iostream>

namespace zeno {

Text::Text(void) :
m_VAO(0),
m_Verticies(0)
{
	if (zeno::ShaderManager::getInstance().addShader("TextShader", "C:/Users/Mark/Documents/Github/textVertexShader.glsl", "C:/Users/Mark/Documents/Github/textFragmentShader.glsl"))
	{
		std::cout << "Shader loaded succesfully." << std::endl;
		zeno::ShaderManager::getInstance().getShader("TextShader").bind();

		if (!zeno::ShaderManager::getInstance().getShader("TextShader").getLocationOfUniform("colour"))
		{
			std::cout << "Failed to get \"colour\" uniform" << std::endl;
		}
		if (!zeno::ShaderManager::getInstance().getShader("TextShader").getLocationOfUniform("view"))
		{
			std::cout << "Failed to get \"view\" uniform" << std::endl;
		}
		if (!zeno::ShaderManager::getInstance().getShader("TextShader").getLocationOfUniform("texSize"))
		{
			std::cout << "Failed to get \"texSize\" uniform" << std::endl;
		}
	}
}
Text::~Text(void)
{
	if (m_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_VAO);
	}
}


void Text::generateText(const std::string& _text, Font *_font)
{
	if (_font == nullptr)
	{
		return;
	}

	m_Font = _font;

	if (m_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	std::vector<float> data;

	Vector2f penPos;

	for (unsigned int i = 0; i < _text.size(); i += 1)
	{
		FT_UInt index = m_Font->getGlyphIndex(static_cast<int>(_text.at(i)));

		FT_GlyphSlot glyph = m_Font->getGlyph(index);

		std::vector<float> verts = m_Font->getVertexData(static_cast<int>(_text.at(i)), penPos + Vector2f(glyph->bitmap_left, static_cast<float>(glyph->bitmap_top) - static_cast<float>(glyph->bitmap.rows)));

		for (unsigned int j = 0; j < verts.size(); j += 1)
		{
			data.push_back(verts.at(j));
		}

		penPos.x += glyph->advance.x >> 6;
	}

	m_Verticies = _text.size() * 6;
	
	glGenVertexArrays(1, &m_VAO);

	GLuint VBO;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Text::render(RenderData _data)
{
	zeno::ShaderManager::getInstance().getShader(_data.shader).bind();
	
	zeno::ShaderManager::getInstance().getShader(_data.shader).passUniform("colour", zeno::Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
	zeno::ShaderManager::getInstance().getShader(_data.shader).passUniform("texSize", _data.texture->getSize());
	zeno::ShaderManager::getInstance().getShader(_data.shader).passUniform("view", _data.transform);

	_data.texture->bind();

	glDrawArrays(GL_TRIANGLES, 0, m_Verticies);
}

} //~ namespace zeno