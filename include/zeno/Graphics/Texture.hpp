#ifndef INCLUDED_ZENO_GRAPHICS_TEXTURE_HPP
#define INCLUDED_ZENO_GRAPHICS_TEXTURE_HPP

#include <zeno/System/Vector2.hpp>

#include <vector>
#include <string>
#include <cstdint>

namespace zeno {

class Image;

////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////
class Texture
{
public:
	enum TextureWrap {
		CLAMP,
		REPEAT,
		MIRRORED_REPEAT
	};

	Texture(void);
	~Texture(void);

	bool loadFromFile(const std::string& _filename);
	bool loadFromImage(const Image& _image);

	void bind(void) const;
	static void unbind(void);

	Vector2<unsigned int> getSize(void) const;

	void setWrapMode(TextureWrap _xAxis, TextureWrap _yAxis);


private:
	unsigned int 				m_TextureHandle;

	std::vector<uint8_t> 		m_PixelData;

	Vector2<unsigned int>		m_Size;

	TextureWrap					m_XAxisWrap;
	TextureWrap					m_YAxisWrap;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_TEXTURE_HPP