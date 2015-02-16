#ifndef INCLUDED_COLOUR_HPP
#define INCLUDED_COLOUR_HPP

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Class for manipulating 4 part colours, ranging from 0.0 - 1.0
//
////////////////////////////////////////////////////////////
class Colour
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor, creates a Black colour
	//
	////////////////////////////////////////////////////////////
	Colour(void);
	////////////////////////////////////////////////////////////
	//
	//	Constructor, creates colour based on given parameters
	//
	////////////////////////////////////////////////////////////
	Colour(float _r, float _g, float _b, float _a = 1.0f);
	
	////////////////////////////////////////////////////////////
	//
	//	Predefined Black colour
	//
	////////////////////////////////////////////////////////////
	static const Colour Black;
	////////////////////////////////////////////////////////////
	//
	//	Predefined White colour
	//
	////////////////////////////////////////////////////////////
	static const Colour White;
	////////////////////////////////////////////////////////////
	//
	//	Predefined Red colour
	//
	////////////////////////////////////////////////////////////
	static const Colour Red;
	////////////////////////////////////////////////////////////
	//
	//	Predefined Green colour
	//
	////////////////////////////////////////////////////////////
	static const Colour Green;
	////////////////////////////////////////////////////////////
	//
	//	Predefined Blue colour
	//
	////////////////////////////////////////////////////////////
	static const Colour Blue;
	////////////////////////////////////////////////////////////
	//
	//	Predefined Yellow colour
	//
	////////////////////////////////////////////////////////////
	static const Colour Yellow;
	////////////////////////////////////////////////////////////
	//
	//	Predefined Magenta colour
	//
	////////////////////////////////////////////////////////////
	static const Colour Magenta;
	////////////////////////////////////////////////////////////
	//
	//	Predefined Cyan colour
	//
	////////////////////////////////////////////////////////////
	static const Colour Cyan;
	////////////////////////////////////////////////////////////
	//
	//	Predefined Transparent colour
	//
	////////////////////////////////////////////////////////////
	static const Colour Transparent;
	
public:
	////////////////////////////////////////////////////////////
	//
	//	Red component of the colour
	//
	////////////////////////////////////////////////////////////
	float r;
	////////////////////////////////////////////////////////////
	//
	//	Green component of the colour
	//
	////////////////////////////////////////////////////////////
	float g;
	////////////////////////////////////////////////////////////
	//
	//	Blue component of the colour
	//
	////////////////////////////////////////////////////////////
	float b;
	////////////////////////////////////////////////////////////
	//
	//	Alpha component of the colour
	//
	////////////////////////////////////////////////////////////
	float a;
};

////////////////////////////////////////////////////////////
//
//	Overload of == operator
//
////////////////////////////////////////////////////////////
bool operator ==(const Colour& _left, const Colour& _right);
////////////////////////////////////////////////////////////
//
//	Overload of != operator
//
////////////////////////////////////////////////////////////
bool operator != (const Colour& _left, const Colour& _right);

////////////////////////////////////////////////////////////
//
//	Overload of + operator, component-wise
//
////////////////////////////////////////////////////////////
Colour operator +(const Colour& _left, const Colour& _right);
////////////////////////////////////////////////////////////
//
//	Overload of += operator, component-wise
//
////////////////////////////////////////////////////////////
Colour& operator +=(Colour& _left, const Colour& _right);

////////////////////////////////////////////////////////////
//
//	Overload of - operator, component-wise
//
////////////////////////////////////////////////////////////
Colour operator -(const Colour& _left, const Colour& _right);
////////////////////////////////////////////////////////////
//
//	Overload of -= operator, component-wise
//
////////////////////////////////////////////////////////////
Colour& operator -=(Colour& _left, const Colour& _right);

////////////////////////////////////////////////////////////
//
//	Overload of * operator, component-wise by constant
//
////////////////////////////////////////////////////////////
Colour operator *(const Colour& _left, float _right);
////////////////////////////////////////////////////////////
//
//	Overload of * operator, component-wise
//	
//
////////////////////////////////////////////////////////////
Colour operator *(const Colour& _left, const Colour& _right);
////////////////////////////////////////////////////////////
//
//	Overload of *= operator, component-wise by constant
//
////////////////////////////////////////////////////////////
Colour& operator *=(Colour& _left, float _val);
////////////////////////////////////////////////////////////
//
//	Overload of *= operator, component-wise
//
////////////////////////////////////////////////////////////
Colour& operator *=(Colour& _left, const Colour& _right);

} //~ namespace zeno

#endif //~ INCLUDED_COLOUR_HPP
