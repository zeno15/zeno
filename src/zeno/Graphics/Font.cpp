#include <zeno/Graphics/Font.hpp>

#include <zeno/Graphics/Texture.hpp>

#include <iostream>

#define FONT_SIZE 20

namespace zeno {

Font::Font(void)
{
}

Font::Font(const std::string& _font)
{
	loadFont(_font);
}

Font::~Font(void)
{

}


bool Font::loadFont(const std::string& _font)
{
	//~ Need to load empty glyph here

	return m_Loader.loadFont(_font);
}

void Font::renderString(const std::string& _string, Image& _image)
{
	unsigned int currentX = FONT_SIZE;
	unsigned int currentY = FONT_SIZE;
	_image.create((_string.size() + 1) * FONT_SIZE * 2, FONT_SIZE * 5, Colour::Black);

	Glyph currentGlyph;

	for (unsigned int i = 0; i < _string.size(); i += 1)
	{
		int index = getGlyphIndex(_string.at(i));

		if (index == -1)
		{
			std::cout << "Need to add: " << _string.at(i) << " to atlas" << std::endl;
			index = createGlyph(_string.at(i));
		}
		currentGlyph = m_Glyphs.at(index);


		for (unsigned int imageY = 0; imageY < currentGlyph.height; imageY += 1)
		{
			for (unsigned int imageX = 0; imageX < currentGlyph.width; imageX += 1)
			{
				Colour col = m_Atlas.getAtlas().getPixel(currentGlyph.x + imageX, currentGlyph.y - imageY);


				_image.setPixel(currentX + imageX, _image.getSize().y - (currentY + imageY), col);
			}
		}

		currentX += (currentGlyph.width + 2);
	}
}

std::vector<Vertex> Font::createVerticies(const std::string& _string)
{
	std::vector<Vertex> verticies;

	Vector2f position;
	m_Texture.loadFromImage(m_Atlas.getAtlas());

	for (unsigned int i = 0; i < _string.size(); i += 1)
	{
		if (_string.at(i) == '\n')
		{
			position.x = 0.0f;
			position.y -= FONT_SIZE * 4;
		}
		else
		{
			createCharVertexes(verticies, static_cast<int>(_string.at(i)), position);
		}
	}
	
	m_Texture.loadFromImage(m_Atlas.getAtlas());

	return verticies;
}

Texture *Font::getTexture(void)
{
	return &m_Texture;
}

int Font::createGlyph(int _charCode)
{
	//~ Need to return empty glyph on failure
	Glyph glyph;
	Image image;

	if (!m_Loader.loadGlyph(_charCode, FONT_SIZE))
	{
		std::cout << "Failed to load glyph" << std::endl;
		return -1;
	}

	glyph.character = _charCode;


	if (!m_Loader.renderGlyph(image, glyph))
	{
		std::cout << "Failed to render glyph" << std::endl;
		return -1;
	}


	m_Atlas.addGlyph(image, glyph);

	m_Glyphs.push_back(glyph);
	return m_Glyphs.size() - 1;
}

int Font::getGlyphIndex(int _charCode)
{
	for (unsigned int i = 0; i < m_Glyphs.size(); i += 1)
	{
		if (m_Glyphs.at(i).character == _charCode)
		{
			return i;
		}
	}

	return -1;
}

void Font::createCharVertexes(std::vector<Vertex>& _verticies, int _character, Vector2f& _drawPosition)
{
	Glyph currentGlyph;

	int index = getGlyphIndex(_character);

	if (index == -1)
	{
		index = createGlyph(_character);
	}
	currentGlyph = m_Glyphs.at(index);

	Vector2f textureSize = m_Texture.getSize();

	float texXleft =		static_cast<float>(currentGlyph.x);
	float texXright =		static_cast<float>(currentGlyph.x + currentGlyph.width);
	float texYbottom =		static_cast<float>(textureSize.y - currentGlyph.y - 1);
	float texYtop =			static_cast<float>(textureSize.y - currentGlyph.y - 1 + currentGlyph.height);

	Vector2f offset;

	offset.x = 0.0f;//static_cast<float>(currentGlyph.bearing_x);
	offset.y = static_cast<float>(currentGlyph.bearing_y) - static_cast<float>(currentGlyph.height);

	Vertex v1 = Vertex(	Vector3f(_drawPosition.x + offset.x, _drawPosition.y + offset.y, 0.0f), 
						Colour::White, 
						Vector2f(texXleft, texYbottom));

	Vertex v2 = Vertex( Vector3f(_drawPosition.x + offset.x + currentGlyph.width, _drawPosition.y + offset.y, 0.0f), 
						Colour::White, 
						Vector2f(texXright, texYbottom));

	Vertex v3 = Vertex( Vector3f(_drawPosition.x + offset.x + currentGlyph.width,	_drawPosition.y + offset.y + currentGlyph.height,	0.0f), 
						Colour::White, 
						Vector2f(texXright, texYtop));



	Vertex v4 = Vertex( Vector3f(_drawPosition.x + offset.x, _drawPosition.y + offset.y, 0.0f), 
						Colour::White, 
						Vector2f(texXleft, texYbottom));

	Vertex v5 = Vertex( Vector3f(_drawPosition.x + offset.x + currentGlyph.width,	_drawPosition.y + offset.y + currentGlyph.height, 0.0f), 
						Colour::White, 
						Vector2f(texXright, texYtop));

	Vertex v6 = Vertex( Vector3f(_drawPosition.x + offset.x, _drawPosition.y + offset.y + currentGlyph.height, 0.0f), 
						Colour::White, 
						Vector2f(texXleft, texYtop));

	_verticies.push_back(v1);
	_verticies.push_back(v2);
	_verticies.push_back(v3);

	_verticies.push_back(v4);
	_verticies.push_back(v5);
	_verticies.push_back(v6);
	
	_drawPosition.x += currentGlyph.advance;
}

void Font::saveTexture(const std::string& _filename)
{
	m_Atlas.getAtlas().saveToFile(_filename);
}

} //~ namespace zeno