#include <FontLoader.hpp>

#include <Image.hpp>

namespace zeno {

bool FontLoader::loadFont(const std::string& _filepath)
{
	return (FT_New_Face(m_Library, _filepath.c_str(), 0, &m_Face) == 0);
}

bool FontLoader::loadGlyph(int _c, unsigned int _size)
{
	FT_Set_Char_Size(m_Face, 0, _size * 64, 300, 0);

	FT_UInt glyph_index = FT_Get_Char_Index(m_Face, _c);

	return (FT_Load_Glyph(m_Face, glyph_index, FT_LOAD_DEFAULT) == 0);
}

bool FontLoader::renderGlyph(Image& _image)
{
	if (FT_Render_Glyph(m_Face->glyph, FT_RENDER_MODE_NORMAL) != 0)
	{
		return false;
	}

	_image.create(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows);

	for (unsigned int i = 0; i < _image.getSize().y; i += 1)
	{
		for (unsigned int j = 0; j < _image.getSize().x; j += 1)
		{
			uint8_t val = m_Face->glyph->bitmap.buffer[i * m_Face->glyph->bitmap.width + j];

			_image.setPixel(j, i, zeno::Colour(static_cast<float>(val) / 255.0f, static_cast<float>(val) / 255.0f, static_cast<float>(val) / 255.0f));
		}
	}

	return true;
}



FontLoader::FontLoader(void) :
m_Library(nullptr),
m_Face(nullptr)
{
	FT_Init_FreeType(&m_Library);
}

FontLoader::~FontLoader(void)
{
	if (m_Library != nullptr)
	{
		FT_Done_FreeType(m_Library);
	}
}

} //~ namespace zeno