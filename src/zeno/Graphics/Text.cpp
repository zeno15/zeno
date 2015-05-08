#include <zeno/Graphics/Text.hpp>

#include <zeno/Graphics/Font.hpp>
#include <zeno/Graphics/ShaderManager.hpp>

#include <GL/glew.h>

#include <iostream>

namespace zeno {

Text::Text(void) :
m_VAO(0),
m_Verticies(0),
m_TextColour(Colour::White),
m_UseKerning(false)
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
	glDeleteVertexArrays(1, &m_VAO);
}


void Text::generateText(const std::string& _text, Font *_font)
{
	if (_font == nullptr)
	{
		return;
	}

	m_Font = _font;

	glDeleteVertexArrays(1, &m_VAO);
	
	std::vector<float> data;

	Vector2f penPos;

	float top = 0.0f;
	float bottom = 0.0f;

	for (unsigned int i = 0; i < _text.size(); i += 1)
	{
		FT_UInt index = m_Font->getGlyphIndex(static_cast<int>(_text.at(i)));

		Vector2f kerning;

		if (m_UseKerning && i > 0)
		{
			FT_Vector k = m_Font->getKerning(_text.at(i - 1), _text.at(i));
			kerning.x = static_cast<float>(k.x >> 6);
		}

		FT_GlyphSlot glyph = m_Font->getGlyph(index);

		std::vector<float> verts = m_Font->getVertexData(static_cast<int>(_text.at(i)), penPos + Vector2f(static_cast<float>(glyph->bitmap_left + kerning.x), static_cast<float>(glyph->bitmap_top) - static_cast<float>(glyph->bitmap.rows)));
		
		for (unsigned int j = 0; j < verts.size(); j += 4)
		{
			data.push_back(verts.at(j + 0));	//~ x pos
			data.push_back(verts.at(j + 1));	//~ y pos
			data.push_back(verts.at(j + 2));	//~ x tex
			data.push_back(verts.at(j + 3));	//~ y tex

			top = std::max(top, verts.at(j + 1));
			bottom = std::min(bottom, verts.at(j + 1));
		}

		penPos.x += glyph->advance.x >> 6;
	}


	m_Verticies = (data.size() / 4);

	float left = 0.0f;
	float right = data.at(data.size() - 1 - 3);

	m_Bounds = FloatRect(left, bottom, right - left, top - bottom);
	
	
	glGenVertexArrays(1, &m_VAO);

	GLuint VBO;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	m_Font->updateTextureIfNeeded();
}

void Text::render(RenderData _data) const
{
	if (_data.shader == "Zenos_Default_Shader")
	{
		_data.shader = "TextShader";
	}

	zeno::ShaderManager::getInstance().getShader(_data.shader).bind();
	
	zeno::ShaderManager::getInstance().getShader(_data.shader).passUniform("colour", m_TextColour);
	zeno::ShaderManager::getInstance().getShader(_data.shader).passUniform("texSize", m_Font->getTextureAtlas().getSize());
	zeno::ShaderManager::getInstance().getShader(_data.shader).passUniform("view", _data.transform);

	m_Font->getTextureAtlas().bind();

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_Verticies);
}

void Text::setColour(const Colour& _colour)
{
	m_TextColour = _colour;
}

void Text::setKerning(bool _kerning /*= true*/)
{
	m_UseKerning = _kerning;
}

FloatRect Text::getBounds(void)
{
	return m_Bounds;
}

FloatRect Text::getTransformedBounds(void)
{
	//~ TODO need to inherit from Transformable2D and then add the translated offset

	return m_Bounds;
}

} //~ namespace zeno