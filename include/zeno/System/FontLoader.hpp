#ifndef INCLUDED_FONT_LOADER_HPP
#define INCLUDED_FONT_LOADER_HPP

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace zeno {

class Image;

////////////////////////////////////////////////////////////
//
//	Xlass to load fonts to image glyphs
//
////////////////////////////////////////////////////////////
class FontLoader
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor
	//
	////////////////////////////////////////////////////////////
	FontLoader(void);

	////////////////////////////////////////////////////////////
	//
	//	Destructor
	//
	////////////////////////////////////////////////////////////
	~FontLoader(void);

	////////////////////////////////////////////////////////////
	//
	//	Loads a font face given by the file path
	//
	////////////////////////////////////////////////////////////
	bool loadFont(const std::string& _filepath);

	////////////////////////////////////////////////////////////
	//
	//
	//
	////////////////////////////////////////////////////////////
	bool loadGlyph(int _c, unsigned int _size);

	////////////////////////////////////////////////////////////
	//
	//
	//
	////////////////////////////////////////////////////////////
	bool renderGlyph(Image& _image);

private:
	////////////////////////////////////////////////////////////
	//
	//	Freetype library handle
	//
	////////////////////////////////////////////////////////////
	FT_Library				m_Library;

	////////////////////////////////////////////////////////////
	//
	//	Freetype face handle
	//
	////////////////////////////////////////////////////////////
	FT_Face					m_Face;
};

} //~ namespace zeno

#endif //~ INCLUDED_FONT_LOADER_HPP