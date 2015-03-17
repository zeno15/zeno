#include <Font.hpp>

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

	m_Atlas.getAtlas().saveToFile("Resources/AtlasFor-" + _string + "-.png");
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


	if (!m_Loader.renderGlyph(image))
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

} //~ namespace zeno