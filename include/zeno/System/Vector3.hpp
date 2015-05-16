#ifndef INCLUDED_ZENO_SYSTEM_VECTOR_3_HPP
#define INCLUDED_ZENO_SYSTEM_VECTOR_3_HPP

#include <ostream>

#include <cmath>

////////////////////////////////////////////////////////////
///
///	\namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief	Template class for 3D Vectors
///
////////////////////////////////////////////////////////////
template <typename T>
class Vector3
{
public:
	////////////////////////////////////////////////////////////
	///
	///	\brief	Default constructor
	///
	///	Creates a Vector3 with x, y and z equal to 0
	///
	////////////////////////////////////////////////////////////
	Vector3();

	////////////////////////////////////////////////////////////
	///
	///	\brief	Initialises x, y and z to the given values
	///
	///	\param	_x		value that x is set to
	///
	///	\param	_y		value that y is set to
	///
	///	\param	_z		value that z is set to
	///
	////////////////////////////////////////////////////////////
	Vector3(T _x, T _y, T _z);

	////////////////////////////////////////////////////////////
	///
	///	\brief	Copy constructor
	///
	///	Initialises the vector to have the same values as that
	///	of the parameter 
	///
	///	\param	_vec	Vector3 that is used to initialise this
	///					Vector3
	///
	////////////////////////////////////////////////////////////
	template <typename U>
	Vector3(const Vector3<U>& _vec);

public:
	T x;	///<	x component

	T y;	///<	y component

	T z;	///<	z component
};

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of negate operator
///
///	\param		_right		Vector3 to negate
///
///	\return		Component-wise negated version of the Vector3
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> operator -(const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of minus-equals operator
///
///	\param		_left		Vector3 to be modified
///
///	\param		_right		Vector3 to subtract
///
///	\return		Reference to \a _left Vector3
//
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T>& operator -=(Vector3<T>& _left, const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of minus operator
///
///	\param		_left		Vector3 to be subtracted from
///
///	\param		_right		Vector3 to subtract
///
///	\return		Vector3 which is component-wise subtraction 
///				of \a _right from \a _left
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> operator -(const Vector3<T>& _left, const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of plus-equals operator
///
///	\param		_left		Vector3 to be added to
///
///	\param		_right		Vector3 to add
///
///	\return		Reference to \a _left Vector3
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> operator +=(Vector3<T>& _left, const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of plus operator
///
///	\param		_left		Left Vector3 to add
///
///	\param		_right		Right Vector3 to add
///
///	\return		Vector3 which is component-wise addition of
///				\a _left and \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> operator +(const Vector3<T>& _left, const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of divide-equals operator
///
///	\param		_left		Vector3 to be divided
///
///	\param		_right		Value to divide the Vector3 by
///
///	\return		Reference to \a _left Vector3
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T>& operator /=(Vector3<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of divide operator
///
///	\param		_left		Vector3 to be divided
///
///	\param		_right		Value to divide Vector3 by
///
///	\return		Vector3 which is the component-wise division
///				of \a _left by \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> operator /(const Vector3<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of multiply-equal operator
///
///	\param		_left		Vector3 to be multiplied
///
///	\param		_right		Value to multiply Vector3 by
///
///	\return		Reference to \a _left which is a componen-
///				wise multiplication of \a _left by \a _right\
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> operator *=(Vector3<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of multiply operator
///
///	\param		_left		Vector3 to be multiplied
///
///	\param		_right		Value to multiply Vector3 by
///
///	\return		Vector3 which is a component-wise 
///				multiplication of \a _left by \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> operator *(const Vector3<T>& _left, T _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
/// \brief		Overload of multiply operator
///
///	\param		_left		Value to multiply Vector3 by
///
///	\param		_right		Vector3 to be multiplied
///
///	\return		Vector3 which is a component-wise
///				multiplication of \a _right by \a _left
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> operator *(T _left, const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of boolean equals operator
///
///	\param		_left		Vector3 to be compared
///
///	\param		_right		Vector3 to be compared
///
///	\return		Boolean value representing whether or not
///				all of the components of \a _left are equal
///				to those of \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator ==(const Vector3<T>& _left, const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of boolean not-equals operator
///
///	\param		_left		Vector3 to be compared
///
///	\param		_right		Vector3 to be compared
///
///	\return		Boolean value representing whether or not
///				any of the components of \a _left are not 
///				equal to those of \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator !=(const Vector3<T>& _left, const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Vector3
///
///	\brief		Overload of << operator
///
///	\param		os			std::ostream reference
///
///	\param		_vec		Vector3 to be output
///
///	\return		std::ostream reference with formatted Vector3
///				output insertted into it
///
////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator <<(std::ostream& os, zeno::Vector3<T> const& _vec);




#include "Vector3.inl"

typedef Vector3<int>				Vector3i;
typedef Vector3<unsigned int>			Vector3u;
typedef Vector3<float>				Vector3f;
typedef Vector3<double>				Vector3d;

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_VECTOR_3_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Vector3
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code 
///	zeno::Vector3<float> vec = zeno::Vector3<float>();
///	\endcode
///
////////////////////////////////////////////////////////////