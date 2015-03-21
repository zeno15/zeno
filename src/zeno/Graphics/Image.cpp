#include <zeno/Graphics/Image.hpp>

#include <zeno/Graphics/ImageLoader.hpp>

namespace zeno {

void Image::create(unsigned int _width, unsigned int _height, const Colour& _colour /*= Colour::Black*/)
{
	if (_width > 0 && _height > 0)
	{
		m_Size = Vector2<unsigned int>(_width, _height);
		
		m_Pixels.resize(_width * _height * 4);
		for (unsigned int i = 0; i < _height; i += 1)
		{
			for (unsigned int j = 0; j < _width; j += 1)
			{
				setPixel(j, i, _colour);
			}
		}
	}
	else
	{
		m_Pixels.clear();
		m_Size = Vector2<unsigned int>();
	}
}

bool Image::loadFromFile(const std::string& _filename)
{
	return ImageLoader::getInstance().loadImageFromFile(_filename, m_Pixels, m_Size);
}
bool Image::saveToFile(const std::string& _filename)
{
	return ImageLoader::getInstance().saveImageToFile(_filename, m_Pixels, m_Size);
}

Vector2<unsigned int> Image::getSize(void) const
{
	return m_Size;
}

Colour Image::getPixel(unsigned int _x, unsigned int _y) const
{
	unsigned int index = (_y * m_Size.x + _x) * 4;
	
	return Colour(	static_cast<float>(m_Pixels.at(index + 0)) / 255.0f,
					static_cast<float>(m_Pixels.at(index + 1)) / 255.0f,
					static_cast<float>(m_Pixels.at(index + 2)) / 255.0f,
					static_cast<float>(m_Pixels.at(index + 3)) / 255.0f);
}
void Image::setPixel(unsigned int _x, unsigned int _y, const Colour& _colour)
{
	unsigned int index = (_y * m_Size.x + _x) * 4;
	
	m_Pixels.at(index + 0) = static_cast<uint8_t>(_colour.r * 255.0f);
	m_Pixels.at(index + 1) = static_cast<uint8_t>(_colour.g * 255.0f);
	m_Pixels.at(index + 2) = static_cast<uint8_t>(_colour.b * 255.0f);
	m_Pixels.at(index + 3) = static_cast<uint8_t>(_colour.a * 255.0f);
}

const uint8_t *Image::getPixelPointer(void) const
{
	return &m_Pixels[0];
}

} //~ namespace zeno
