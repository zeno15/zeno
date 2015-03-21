#ifndef INCLUDED_FONT_HPP
#define INCLUDED_FONT_HPP

#include <zeno/System/FontLoader.hpp>
#include <zeno/System/FontAtlasImage.hpp>
#include <zeno/System/Glyph.hpp>

#include <string>
#include <vector>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Class that manages fonts, loads them, generates atlas'
//	and creates vertex/texture coordinates for text
//
////////////////////////////////////////////////////////////
class Font
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor
	//
	////////////////////////////////////////////////////////////
	Font(void);
	////////////////////////////////////////////////////////////
	//
	//	Specific font constructor
	//
	////////////////////////////////////////////////////////////
	Font(const std::string& _font);

	////////////////////////////////////////////////////////////
	//
	//	Destructor
	//
	////////////////////////////////////////////////////////////
	~Font(void);


	////////////////////////////////////////////////////////////
	//
	//	Loads a font from the given file name
	//
	////////////////////////////////////////////////////////////
	bool loadFont(const std::string& _font);

	///////////////////////////////////////////////////////////
	//
	//	Temporary function, renders the given string to the 
	//	given image
	//
	///////////////////////////////////////////////////////////
	void renderString(const std::string& _string, Image& _image);

private:
	////////////////////////////////////////////////////////////
	//
	//	Adds the character represented by the given character
	//	code to the font atlas and glyph vector.  Returns the 
	//	glyph location in the vector
	//
	////////////////////////////////////////////////////////////
	int createGlyph(int _charCode);

	////////////////////////////////////////////////////////////
	//
	//	Get the index in the glyph vector of the given character
	//	code, returns -1 if not present
	//
	////////////////////////////////////////////////////////////
	int getGlyphIndex(int _charCode);

private:
	////////////////////////////////////////////////////////////
	//
	//	Font loader
	//
	////////////////////////////////////////////////////////////
	FontLoader					m_Loader;

	////////////////////////////////////////////////////////////
	//
	//	Font Atlas
	//
	////////////////////////////////////////////////////////////
	FontAtlasImage				m_Atlas;

	////////////////////////////////////////////////////////////
	//
	//	Vector of glyphs that are present
	//
	////////////////////////////////////////////////////////////
	std::vector<Glyph>			m_Glyphs;
};

} //~ namespace zeno

#endif //~ INCLUDED_FONT_HPP