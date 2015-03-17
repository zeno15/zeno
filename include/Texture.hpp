#ifndef INCLUDED_TEXTURE_HPP
#define INCLUDED_TEXTURE_HPP

#include <Vector2.hpp>

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
	Texture(void);
	~Texture(void);

	bool loadFromFile(const std::string& _filename);
	bool loadFromImage(const Image& _image);

	void bind(void) const;
	static void unbind(void);

	Vector2<unsigned int> getSize(void) const;
private:
	unsigned int 				m_TextureHandle;

	std::vector<uint8_t> 		m_PixelData;

	Vector2<unsigned int>		m_Size;
};

} //~ namespace zeno

#endif //~ INCLUDED_TEXTURE_HPP