#ifndef INCLUDED_ZENO_SYSTEM_VECTOR_MATH_HPP
#define INCLUDED_ZENO_SYSTEM_VECTOR_MATH_HPP

#include <zeno/System/Vector2.hpp>
#include <zeno/System/Vector3.hpp>
#include <zeno/System/Vector4.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {


////////////////////////////////////////////////////////////
///
///	\brief  Returns the length of a Vector2
///
/// \param  _vec    Vector2 object
///
/// \return T length of Vector2
///
////////////////////////////////////////////////////////////
template <typename T>
T length(const Vector2<T>& _vec);

////////////////////////////////////////////////////////////
///
///	\brief  Returns the length of a Vector3
///
/// \param  _vec    Vector3 object
///
/// \return T length of Vector3
///
////////////////////////////////////////////////////////////
template <typename T>
T length(const Vector3<T>& _vec);

////////////////////////////////////////////////////////////
///
///	\brief  Returns the length of a Vector4
///
/// \param  _vec    Vector4 object
///
/// \return T length of Vector4
///
////////////////////////////////////////////////////////////
template <typename T>
T length(const Vector4<T>& _vec);


////////////////////////////////////////////////////////////
///
///	\brief  Returns the length squared of a Vector2
///
/// \param  _vec    Vector2 object
///
/// \return T length squared of Vector2
///
////////////////////////////////////////////////////////////
template <typename T>
T lengthSquared(const Vector2<T>& _vec);

////////////////////////////////////////////////////////////
///
///	\brief  Returns the length squared of a Vector3
///
/// \param  _vec    Vector3 object
///
/// \return T length squared of Vector3
///
////////////////////////////////////////////////////////////
template <typename T>
T lengthSquared(const Vector3<T>& _vec);

////////////////////////////////////////////////////////////
///
///	\brief  Returns the length squared of a Vector4
///
/// \param  _vec    Vector4 object
///
/// \return T length squared of Vector4
///
////////////////////////////////////////////////////////////
template <typename T>
T lengthSquared(const Vector4<T>& _vec);


////////////////////////////////////////////////////////////
///
///	\brief  Normalises the given Vector2
///
/// \param  _vec    Vector2 object
///
/// \return Vector2 reference to \a _vec which has been normalised
///
////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>& normalise(Vector2<T>& _vec);

////////////////////////////////////////////////////////////
///
///	\brief  Normalises the given Vector3
///
/// \param  _vec    Vector3 object
///
/// \return Vector3 reference to \a _vec which has been normalised
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T>& normalise(Vector3<T>& _vec);

////////////////////////////////////////////////////////////
///
///	\brief  Normalises the given Vector2
///
/// \param  _vec    Vector4 object
///
/// \return Vector4 reference to \a _vec which has been normalised
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T>& normalise(Vector4<T>& _vec);


////////////////////////////////////////////////////////////
///
///	\brief  Generates the cross product of 2 Vector3's
///
/// \param  _left   Vector3 object
///
/// \param  _right  Vector3 object
///
/// \return Vector3 representing cross product of \a _left
///         and \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> cross(const Vector3<T>& _left, const Vector3<T>& _right);

////////////////////////////////////////////////////////////
///
///	\brief  Generates the cross product of 2 Vector4's
///
/// \param  _left   Vector4 object
///
/// \param  _right  Vector4 object
///
/// \return Vector4 representing cross product of \a _left
///         and \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> cross(const Vector4<T>& _left, const Vector4<T>& _right);


////////////////////////////////////////////////////////////
///
///	\brief  Generates the dot product of 2 Vector2's
///
/// \param  _left   Vector2 object
///
/// \param  _right  Vector2 object
///
/// \return T representing dot product of \a _left and \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
T dot(const Vector2<T>& _left, const Vector2<T>& _right);

////////////////////////////////////////////////////////////
///
///	\brief  Generates the dot product of 2 Vector3's
///
/// \param  _left   Vector3 object
///
/// \param  _right  Vector3 object
///
/// \return T representing dot product of \a _left and \a _right
///
////////////////////////////////////////////////////////////
template <typename T>
T dot(const Vector3<T>& _left, const Vector3<T>& _right);


#include <zeno/System/VectorMath.inl>

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_VECTOR_MATH_HPP

////////////////////////////////////////////////////////////
///
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code
///	\endcode
///
////////////////////////////////////////////////////////////