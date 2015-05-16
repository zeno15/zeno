#ifndef INCLUDED_ZENO_SYSTEM_VECTOR_4_HPP
#define INCLUDED_ZENO_SYSTEM_VECTOR_4_HPP

#include <ostream>

#include <zeno/System/Vector3.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief	Template class for 4D Vectors
///
////////////////////////////////////////////////////////////
template <typename T>
class Vector4
{
public:
	////////////////////////////////////////////////////////////
	///
	///	\brief	Default constructor
	///
	///	Creates a Vector4 with x, y, z and w equal to 0
	///
	////////////////////////////////////////////////////////////
	Vector4();

	////////////////////////////////////////////////////////////
	///
	///	\brief	Initialises x and y and z and w to the given 
	///			values
	///	\param	_x		value that x is set to
	///
	///	\param	_y		value that y is set to
	///
	///	\param	_z		value that z is set to
	///
	///	\param	_w		value that q is set to
	///
	////////////////////////////////////////////////////////////
	Vector4(T _x, T _y, T _z, T _w);

	////////////////////////////////////////////////////////////
	///
	///	\brief	Copy constructor
	///
	///	Initialises the vector to have the same values as that
	///	of the parameter
	///
	///	\param	_vec	Vector4 that is used to initialise this
	///					Vector4
	///
	////////////////////////////////////////////////////////////
	template <typename U>
	Vector4(const Vector4<U>& _vec);

	////////////////////////////////////////////////////////////
	///
	///	\brief	Constructor from Vector3 and Value
	///
	///	Creates a Vector4 from the x, y and z values of the
	///	Vector3 and w from the value
	///
	///	\param	_vec	Vector3 that is used to initialise x, y
	///					and z of this Vector4
	///
	///	\param	_w		Value that is used to initialise w
	///
	////////////////////////////////////////////////////////////
	Vector4(const Vector3<T>& _vec, T _w);

public:

	T x;	///<	x component

	T y;	///<	y component

	T z;	///<	z component

	T w;	///<	w component
};

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of negate operator
///
///	\param		_right		Vector4 to negate
///
///	\return		Component-wise negated version of the Vector4
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> operator -(const Vector4<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of minus-equals operator
///
///	\param		_left		Vector4 to be modified
///
///	\param		_right		Vector4 to subtract
///
///	\return		Reference to \a _left Vector4
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T>& operator -=(Vector4<T>& _left, const Vector4<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of minus operator
///
///	\param		_left		Vector4 to be subtracted from
///
///	\param		_right		Vector4 to subtract
///
///	\return		Vector4 which is component-wise subtraction 
///				of \a _right from \a _left
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> operator -(const Vector4<T>& _left, const Vector4<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of plus-equals operator
///
///	\param		_left		Vector4 to be added to
///
///	\param		_right		Vector4 to add
///
///	\return		Reference to \a _left Vector4
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> operator +=(Vector4<T>& _left, const Vector4<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of plus operator
///
///	\param		_left		Left Vector4 to add
///
///	\param		_right		Right Vector4 to add
///
///	\return		Vector4 which is component-wise addition of
///				\a _left and \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> operator +(const Vector4<T>& _left, const Vector4<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of divide-equals operator
///
///	\param		_left		Vector4 to be divided
///
///	\param		_right		Value to divide the Vector4 by
///
///	\return		Reference to \a _left Vector4
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T>& operator /=(Vector4<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of divide operator
///
///	\param		_left		Vector4 to be divided
///
///	\param		_right		Value to divide Vector2 by
///
///	\return		Vector4 which is the component-wise division
///				of \a _left by \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> operator /(const Vector4<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of multiply-equal operator
///
///	\param		_left		Vector4 to be multiplied
///
///	\param		_right		Value to multiply Vector4 by
///
///	\return		Reference to \a _left which is a componen-
///				wise multiplication of \a _left by \a _right\
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> operator *=(Vector4<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of multiply operator
///
///	\param		_left		Vector4 to be multiplied
///
///	\param		_right		Value to multiply Vector4 by
///
///	\return		Vector4 which is a component-wise 
///				multiplication of \a _left by \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> operator *(const Vector4<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
/// \brief		Overload of multiply operator
///
///	\param		_left		Value to multiply Vector2 by
///
///	\param		_right		Vector4 to be multiplied
///
///	\return		Vector4 which is a component-wise
///				multiplication of \a _right by \a _left
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> operator *(T _left, const Vector4<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of boolean equals operator
///
///	\param		_left		Vector4 to be compared
///
///	\param		_right		Vector4 to be compared
///
///	\return		Boolean value representing whether or not
///				all of the components of \a _left are equal
///				to those of \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator ==(const Vector4<T>& _left, const Vector4<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of boolean not-equals operator
///
///	\param		_left		Vector4 to be compared
///
///	\param		_right		Vector4 to be compared
///
///	\return		Boolean value representing whether or not
///				any of the components of \a _left are not 
///				equal to those of \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator !=(const Vector4<T>& _left, const Vector4<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector4
///
///	\brief		Overload of << operator
///
///	\param		os			std::ostream reference
///
///	\param		_vec		Vector4 to be output
///
///	\return		std::ostream reference with formatted Vector4
///				output insertted into it
///
////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator <<(std::ostream& os, zeno::Vector4<T> const& _vec);


#include "Vector4.inl"

typedef Vector4<int>				Vector4i;
typedef Vector4<unsigned int>		Vector4u;
typedef Vector4<float>				Vector4f;
typedef Vector4<double>				Vector4d;

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_VECTOR_4_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Vector4
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code 
///	zeno::Vector4<float> vec = zeno::Vector4<float>();
///	\endcode
///
////////////////////////////////////////////////////////////