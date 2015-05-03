#ifndef INCLUDED_ZENO_GRAPHICS_GLYPH_HPP
#define INCLUDED_ZENO_GRAPHICS_GLYPH_HPP

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Describes a glyph and its location in the font atlas,
//	also describes how to render it
//
////////////////////////////////////////////////////////////
struct Glyph {
	int				character;
	unsigned int	texX;
	unsigned int	texY;
	unsigned int	sizeX;
	unsigned int	sizeY;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_GLYPH_HPP