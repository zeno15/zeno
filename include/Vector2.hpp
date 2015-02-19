#ifndef INCLUDED_VECTOR_2_HPP
#define INCLUDED_VECTOR_2_HPP

#include <ostream>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Template class for 2D Vectors
//
////////////////////////////////////////////////////////////
template <typename T>
class Vector2
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor, initialises x and y to zero
	//
	////////////////////////////////////////////////////////////
	Vector2();

	////////////////////////////////////////////////////////////
	//
	//	Initialises x and y to the given values
	//
	////////////////////////////////////////////////////////////
	Vector2(T _x, T _y);

	////////////////////////////////////////////////////////////
	//
	//	Copy constructor, initialises x and y to the same 
	//	values the _vec has
	//
	////////////////////////////////////////////////////////////
	template <typename U>
	Vector2(const Vector2<U>& _vec);

public:
	////////////////////////////////////////////////////////////
	//
	//	Member variable, x coordinate
	//
	////////////////////////////////////////////////////////////
	T x;
	////////////////////////////////////////////////////////////
	//
	//	Member variable, y coordinate
	//	
	////////////////////////////////////////////////////////////
	T y;
};

////////////////////////////////////////////////////////////
//
//	Overload of - operator
//	returns negated vector
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator -(const Vector2<T>& _right);

////////////////////////////////////////////////////////////
//
//	Overload of -= operator
//	Modifies _left by subtracting _right from it
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& operator -=(Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
//
//	Overload of - operator
//	returns subtraction of _right from _left
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator -(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
//
//	Overlaod of += operator
//	Modifies _left by adding _right to it
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator +=(Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
//
//	Overload of + operator
//	returns addition of _left and _right
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator +(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
//
//	Overload of /= operator
//	Modifies _left by dividing by _right per value
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& operator /=(Vector2<T>& _left, T _right);

////////////////////////////////////////////////////////////
//
//	Overload of / operator
//	returns component wise division of _left by _right
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator /(const Vector2<T>& _left, T _right);

////////////////////////////////////////////////////////////
//
//	Overload of *= operator
//	modifies _left by multiplying by _right per value
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator *=(Vector2<T>& _left, T _right);

////////////////////////////////////////////////////////////
//
//	Overload of * operator
//	returns component wise multiplication of _left by _right
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator *(const Vector2<T>& _left, T _right);

////////////////////////////////////////////////////////////
//
//	Overload of * operator
//	returns component wise multiplication of _right by _left
//
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator *(T _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
//
//	Overload of == operator
//	returns boolean on whether the components of both
//	vectors are the same (no tolerance)
//
////////////////////////////////////////////////////////////
template <typename T>
bool operator ==(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
//
//	Overload of != operator
//	returns boolean on whether the components of both
//	vectors are not the same (no tolerance)
//
////////////////////////////////////////////////////////////
template <typename T>
bool operator !=(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
//
//	Overload of << operator for std::ostream
//
////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator <<(std::ostream& os, zeno::Vector2<T> const& _vec);



#include "Vector2.inl"

typedef Vector2<int>				Vector2i;
typedef Vector2<unsigned int>		Vector2u;
typedef Vector2<float>				Vector2f;
typedef Vector2<double>				Vector2d;

} //~ namespace zeno

#endif //~ INCLUDED_VECTOR_2_HPP
