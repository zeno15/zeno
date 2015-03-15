#include <FontAtlasImage.hpp>

#include <Glyph.hpp>

#include <iostream>
#include <algorithm>

namespace zeno {

FontAtlasImage::FontAtlasImage(void) :
m_CurrentHeightFromBase(0),
m_CurrentHorizontal(0),
m_NextHeightFromBase(0)
{
	m_Image.create(512, 512, Colour::Magenta);
}


Image& FontAtlasImage::getAtlas(void)
{
	return m_Image;
}

void FontAtlasImage::addGlyph(const Image& _image, Glyph& _glyph)
{
	std::cout << "Need to complete glyph and modify still" << std::endl;

	unsigned int currentY = m_Image.getSize().y - m_CurrentHeightFromBase;
	unsigned int currentX = m_CurrentHorizontal;

	m_NextHeightFromBase = std::max(m_NextHeightFromBase, m_CurrentHeightFromBase + _image.getSize().y);

	if (m_NextHeightFromBase >= m_Image.getSize().y)
	{
		Image tempImage;
		tempImage.create(m_Image.getSize().x, m_Image.getSize().y, Colour::Magenta);

		for (unsigned int i = 0; i < m_Image.getSize().y; i += 1)
		{
			for (unsigned int j = 0; j < m_Image.getSize().x; j += 1)
			{
				tempImage.setPixel(j, i, m_Image.getPixel(j, i));
			}
		}

		m_Image.create(m_Image.getSize().x, m_Image.getSize().y * 2, Colour::Magenta);

		for (unsigned int i = 0; i < tempImage.getSize().y; i += 1)
		{
			for (unsigned int j = 0; j < tempImage.getSize().x; j += 1)
			{
				m_Image.setPixel(j, i + tempImage.getSize().y, tempImage.getPixel(j, i));
			}
		}

		addGlyph(_image, _glyph);
		return;
	}

	if (m_CurrentHorizontal + _image.getSize().x >= m_Image.getSize().x)
	{
		//~ Need to go up a row.
		m_CurrentHorizontal = 0;
		m_CurrentHeightFromBase = m_NextHeightFromBase;
		addGlyph(_image, _glyph);
		return;
	}

	//~ If we get here then there is room to place the glyph starting from bottom
	//~ left coords of currentX, currentY

	for (unsigned int i = 0; i < _image.getSize().y; i += 1)
	{
		for (unsigned int j = 0; j < _image.getSize().x; j += 1)
		{
			unsigned int x = j + currentX;
			unsigned int y = currentY - _image.getSize().y + i;

			Colour glyphColour = _image.getPixel(j, i);

			m_Image.setPixel(x, y, glyphColour);
		}
	}

	//~ Increment the horizontal index
	m_CurrentHorizontal += _image.getSize().x;
}

} //~ namespace zeno