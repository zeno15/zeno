#ifndef INCLUDED_ZENO_SYSTEM_VECTOR_2_HPP
#define INCLUDED_ZENO_SYSTEM_VECTOR_2_HPP

#include <ostream>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief Template class for 2D Vectors
///
////////////////////////////////////////////////////////////
template <typename T>
class Vector2
{
public:
	////////////////////////////////////////////////////////////
	///
	///	\brief	Default constructor
	///
	///	Creates a Vector2 with x and y equal to 0
	///
	////////////////////////////////////////////////////////////
	Vector2();

	////////////////////////////////////////////////////////////
	///
	///	\brief	Initialises x and y to the given values
	///
	///	\param	_x	value that x is set to
	///
	///	\param	_y	value that y is set to
	///
	////////////////////////////////////////////////////////////
	Vector2(T _x, T _y);

	////////////////////////////////////////////////////////////
	///
	///	\brief	Copy constructor
	///
	///	Initialises the vector to have the same values as that 
	///	of the parameter
	///
	///	\param	_vec	Vector2 that is used to initialise this
	///					Vector2
	///
	////////////////////////////////////////////////////////////
	template <typename U>
	Vector2(const Vector2<U>& _vec);

public:
	T x;	///<	x component

	T y;	///<	y component
};

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of negate operator
///
///	\param		_right		Vector2 to negate
///
///	\return		Component-wise negated version of the Vector2
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator -(const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of minus-equals operator
///
///	\param		_left		Vector2 to be modified
///
///	\param		_right		Vector2 to subtract
///
///	\return		Reference to \a _left Vector2
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& operator -=(Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of minus operator
///
///	\param		_left		Vector2 to be subtracted from
///
///	\param		_right		Vector2 to subtract
///
///	\return		Vector2 which is component-wise subtraction 
///				of \a _right from \a _left
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator -(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of plus-equals operator
///
///	\param		_left		Vector2 to be added to
///
///	\param		_right		Vector2 to add
///
///	\return		Reference to \a _left Vector2
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator +=(Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of plus operator
///
///	\param		_left		Left Vector2 to add
///
///	\param		_right		Right Vector2 to add
///
///	\return		Vector2 which is component-wise addition of
///				\a _left and \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator +(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of divide-equals operator
///
///	\param		_left		Vector2 to be divided
///
///	\param		_right		Value to divide the Vector2 by
///
///	\return		Reference to \a _left Vector2
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& operator /=(Vector2<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of divide operator
///
///	\param		_left		Vector2 to be divided
///
///	\param		_right		Value to divide Vector2 by
///
///	\return		Vector2 which is the component-wise division
///				of \a _left by \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator /(const Vector2<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of multiply-equal operator
///
///	\param		_left		Vector2 to be multiplied
///
///	\param		_right		Value to multiply Vector2 by
///
///	\return		Reference to \a _left which is a componen-
///				wise multiplication of \a _left by \a _right\
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& operator *=(Vector2<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of multiply operator
///
///	\param		_left		Vector2 to be multiplied
///
///	\param		_right		Value to multiply Vector2 by
///
///	\return		Vector2 which is a component-wise 
///				multiplication of \a _left by \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator *(const Vector2<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
/// \brief		Overload of multiply operator
///
///	\param		_left		Value to multiply Vector2 by
///
///	\param		_right		Vector2 to be multiplied
///
///	\return		Vector2 which is a component-wise
///				multiplication of \a _right by \a _left
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> operator *(T _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of boolean equals operator
///
///	\param		_left		Vector2 to be compared
///
///	\param		_right		Vector2 to be compared
///
///	\return		Boolean value representing whether or not
///				all of the components of \a _left are equal
///				to those of \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator ==(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of boolean not-equals operator
///
///	\param		_left		Vector2 to be compared
///
///	\param		_right		Vector2 to be compared
///
///	\return		Boolean value representing whether or not
///				any of the components of \a _left are not 
///				equal to those of \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator !=(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector2
///
///	\brief		Overload of << operator
///
///	\param		os			std::ostream reference
///
///	\param		_vec		Vector2 to be output
///
///	\return		std::ostream reference with formatted Vector2
///				output insertted into it
///
////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator <<(std::ostream& os, const Vector2<T>& _vec);



#include "Vector2.inl"

typedef Vector2<int>				Vector2i;
typedef Vector2<unsigned int>		Vector2u;
typedef Vector2<float>				Vector2f;
typedef Vector2<double>				Vector2d;

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_VECTOR_2_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Vector2
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code 
///	zeno::Vector2<float> vec = zeno::Vector2<float>();
///	\endcode
///
////////////////////////////////////////////////////////////