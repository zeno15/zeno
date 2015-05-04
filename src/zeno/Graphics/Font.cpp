#include <zeno/Graphics/Font.hpp>

#include <iostream>
#include <algorithm>

namespace zeno {

Font::Font(void) :
m_FontSize(0),
m_Face(0)
{
	FT_Init_FreeType(&m_Library);
}
Font::~Font(void)
{
	FT_Done_FreeType(m_Library);
}


bool Font::loadFromFile(const std::string& _filename, unsigned int _fontSize)
{
	m_FontSize = _fontSize;

	FT_Error newFaceError = FT_New_Face(m_Library, _filename.c_str(), 0, &m_Face);

	if (newFaceError != 0)
	{
		std::cout << "Failed to set pixel size: " << newFaceError << std::endl;
	}

	FT_Error setPixelError = FT_Set_Pixel_Sizes(m_Face, 0, m_FontSize);

	if (setPixelError != 0)
	{
		std::cout << "Failed to set pixel size: " << setPixelError << std::endl;
	}

	return (newFaceError == 0 && setPixelError == 0);
}

FT_UInt Font::getGlyphIndex(int _character)
{
	return FT_Get_Char_Index(m_Face, _character);
}

FT_GlyphSlot Font::getGlyph(FT_UInt _glyphIndex)
{
	FT_Error error = FT_Load_Glyph(m_Face, _glyphIndex, FT_LOAD_RENDER);
	if (error != 0)
	{
		std::cout << "Failed to load glyph: " << error << std::endl;
	}
	
	return m_Face->glyph;
}


void Font::addGlyphToAtlas(int _character, Image& _atlas)
{
	static unsigned int currentX = 0;
	static unsigned int currentY = 0;
	static unsigned int nextY = 0;

	for (Glyph glyph : m_Glyphs)
	{
		if (glyph.character == _character)
		{
			return;
		}
	}

	FT_GlyphSlot glyph = getGlyph(getGlyphIndex(_character));

	if (currentX + glyph->bitmap.width >= _atlas.getSize().x)
	{
		currentY = nextY;
		currentX = 0;
	}

	if (currentY + glyph->bitmap.rows >= _atlas.getSize().y)
	{
		if (_atlas.getSize().y >= 2048)
		{
			std::cout << "Texture atlas too big, cannot expand." << std::endl;
			return;
		}
		
		_atlas.expandVertically(_atlas.getSize().y, Colour::Magenta);
	}

	m_Glyphs.push_back(Glyph());
	m_Glyphs.back().character = _character;
	m_Glyphs.back().sizeX = glyph->bitmap.width;
	m_Glyphs.back().sizeY = glyph->bitmap.rows;
	m_Glyphs.back().texX = currentX;
	m_Glyphs.back().texY = currentY;
	
	for (unsigned int y = 0; y < glyph->bitmap.rows; y += 1)
	{
		for (unsigned int x = 0; x < glyph->bitmap.width; x += 1)
		{
			unsigned int atlasPosX = currentX + x;
			unsigned int atlasPosY = currentY + y;

			_atlas.setPixel(atlasPosX, atlasPosY, zeno::Colour(static_cast<float>(glyph->bitmap.buffer[y * glyph->bitmap.width + x]) / 255.0f, 0.0f, 0.0f));
		}
	}

	nextY = std::max(nextY, currentY + glyph->bitmap.rows);
	currentX += glyph->bitmap.width;
	
}

Glyph Font::getGlyph(int _character)
{
	for (Glyph glyph : m_Glyphs)
	{
		if (_character == glyph.character)
		{
			return glyph;
		}
	}

	Glyph g = Glyph();

	g.character = -1;

	return g;
}

std::vector<float> Font::getVertexData(int _character, const Vector2f& _penPosition)
{
	Glyph g = getGlyph(_character);

	std::vector<float> verticies;

	if (g.character == -1)
	{
		return verticies;
	}

	
	//~ Bottom Left
		//~ Position
	verticies.push_back(static_cast<float>(_penPosition.x + 0.0f));			verticies.push_back(static_cast<float>(_penPosition.y + 0.0f));
		//~ Texture
	verticies.push_back(static_cast<float>(g.texX));						verticies.push_back(static_cast<float>(g.texY + g.sizeY));

	//~ Bottom Right
		//~ Position
	verticies.push_back(static_cast<float>(_penPosition.x + g.sizeX));		verticies.push_back(static_cast<float>(_penPosition.y + 0.0f));
		//~ Texture
	verticies.push_back(static_cast<float>(g.texX + g.sizeX));				verticies.push_back(static_cast<float>(g.texY + g.sizeY));

	//~ Top Right
		//~ Position
	verticies.push_back(static_cast<float>(_penPosition.x + g.sizeX));		verticies.push_back(static_cast<float>(_penPosition.y + g.sizeY));
		//~ Texture
	verticies.push_back(static_cast<float>(g.texX + g.sizeX));				verticies.push_back(static_cast<float>(g.texY));




	//~ Bottom Left
		//~ Position
	verticies.push_back(static_cast<float>(_penPosition.x + 0.0f));			verticies.push_back(static_cast<float>(_penPosition.y + 0.0f));
		//~ Texture
	verticies.push_back(static_cast<float>(g.texX));						verticies.push_back(static_cast<float>(g.texY + g.sizeY));

	//~ Top Right
		//~ Position
	verticies.push_back(static_cast<float>(_penPosition.x + g.sizeX));		verticies.push_back(static_cast<float>(_penPosition.y + g.sizeY));
		//~ Texture
	verticies.push_back(static_cast<float>(g.texX + g.sizeX));				verticies.push_back(static_cast<float>(g.texY));

	//~ Top Left
		//~ Position
	verticies.push_back(static_cast<float>(_penPosition.x + 0.0f));			verticies.push_back(static_cast<float>(_penPosition.y + g.sizeY));
		//~ Texture
	verticies.push_back(static_cast<float>(g.texX));						verticies.push_back(static_cast<float>(g.texY));

	return verticies;
}

FT_Vector Font::getKerning(int _previous, int _current)
{
	FT_Vector kerning;

	FT_Get_Kerning(m_Face, getGlyphIndex(_previous), getGlyphIndex(_current), FT_KERNING_DEFAULT, &kerning);

	return kerning;
}

} //~ namespace zeno