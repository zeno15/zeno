#ifndef INCLUDED_GLYPH_HPP
#define INCLUDED_GLYPH_HPP

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Describes a glyph and its location in the font atlas,
//	also describes how to render it
//
////////////////////////////////////////////////////////////
struct Glyph {
	int		character;
	unsigned int	x;
	unsigned int	y;
	unsigned int	width;
	unsigned int	height;
};

} //~ namespace zeno

#endif //~ INCLUDED_GLYPH_HPP