#include <zeno/Graphics/Font.hpp>

#include <iostream>
#include <algorithm>

namespace zeno {

Font::Font(void) :
m_FontSize(0),
m_Face(0),
m_AtlasTextureNeedsUpdating(false),
m_CurrentX(0),
m_CurrentY(0),
m_NextY(0)
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

	m_CurrentX = 0;
	m_CurrentY = 0;
	m_NextY = 0;

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

	m_Atlas.create(512, 512, Colour::Magenta);

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


bool Font::addGlyphToAtlas(int _character, Image& _atlas)
{
	FT_GlyphSlot glyph = getGlyph(getGlyphIndex(_character));

	if (m_CurrentX + glyph->bitmap.width >= _atlas.getSize().x)
	{
		m_CurrentY = m_NextY;
		m_CurrentX = 0;
	}

	if (m_CurrentY + glyph->bitmap.rows >= _atlas.getSize().y)
	{
		if (_atlas.getSize().y >= 2048)
		{
			std::cout << "Texture atlas too big, cannot expand." << std::endl;
			return false;
		}
		
		_atlas.expandVertically(_atlas.getSize().y, Colour::Magenta);
	}

	m_Glyphs.push_back(Glyph());
	m_Glyphs.back().character = _character;
	m_Glyphs.back().sizeX = glyph->bitmap.width;
	m_Glyphs.back().sizeY = glyph->bitmap.rows;
	m_Glyphs.back().texX = m_CurrentX;
	m_Glyphs.back().texY = m_CurrentY;
	
	for (unsigned int y = 0; y < glyph->bitmap.rows; y += 1)
	{
		for (unsigned int x = 0; x < glyph->bitmap.width; x += 1)
		{
			unsigned int atlasPosX = m_CurrentX + x;
			unsigned int atlasPosY = m_CurrentY + y;

			_atlas.setPixel(atlasPosX, atlasPosY, zeno::Colour(static_cast<float>(glyph->bitmap.buffer[y * glyph->bitmap.width + x]) / 255.0f, 0.0f, 0.0f));
		}
	}

	m_NextY = std::max(m_NextY, m_CurrentY + glyph->bitmap.rows);
	m_CurrentX += glyph->bitmap.width;

	m_AtlasTextureNeedsUpdating = true;
	
	return true;
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

	if (addGlyphToAtlas(_character, m_Atlas))
	{
		return getGlyph(_character);
	}
	else
	{
		Glyph g = Glyph();

		g.character = -1;

		return g;
	}
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

Image& Font::getAtlas(void)
{
	return m_Atlas;
}

Texture& Font::getTextureAtlas(void)
{
	return m_AtlasTexture;
}

void Font::updateTextureIfNeeded(void)
{
	if (m_AtlasTextureNeedsUpdating)
	{
		m_AtlasTextureNeedsUpdating = false;

		m_AtlasTexture.loadFromImage(m_Atlas);

		//~ TODO, remove this when texture options are persistant
		m_AtlasTexture.setWrapMode(Texture::TextureWrap::CLAMP, Texture::TextureWrap::CLAMP);
	}
}

} //~ namespace zeno