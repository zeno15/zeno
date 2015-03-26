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
	unsigned int	x;
	unsigned int	y;
	unsigned int	width;
	unsigned int	height;
	unsigned int	advance;
	unsigned int	bearing_x;
	unsigned int	bearing_y;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_GLYPH_HPP