#ifndef INCLUDED_ZENO_SYSTEM_TRANSFORMABLE_3D_HPP
#define INCLUDED_ZENO_SYSTEM_TRANSFORMABLE_3D_HPP

#include <zeno/System/Mat4x4.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief	Class that represents a 3D transformation
///
////////////////////////////////////////////////////////////
class Transformable3D
{
public:
	////////////////////////////////////////////////////////////
	///
	///	\brief		Default constructor
	///
	///	Initialises the internal transformation to the identity
	///	matrix
	///
	////////////////////////////////////////////////////////////
	Transformable3D(void);

	
	////////////////////////////////////////////////////////////
	///
	///	\brief		Resets the internal transformation to the
	///				identity matrix
	///
	////////////////////////////////////////////////////////////
	void resetTransformation(void);


	////////////////////////////////////////////////////////////
	///
	///	\brief		Gets a read only reference to the transform
	///
	///	\return		Mat4x4 read only reference
	///
	////////////////////////////////////////////////////////////
	const Mat4x4& getTransform(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Returns read/write reference to the transformation
	//
	////////////////////////////////////////////////////////////
	Mat4x4& getTransform(void);
	

	////////////////////////////////////////////////////////////
	//
	//	Translates the transformation by the given offset
	//
	////////////////////////////////////////////////////////////
	void move(const Vector3f& _offset);
	////////////////////////////////////////////////////////////
	//
	//	Sets the translation of the transformation to the given
	//	position
	//
	////////////////////////////////////////////////////////////
	void setPosition(const Vector3f& _position);
	////////////////////////////////////////////////////////////
	//
	//	Gets the translation of the transformation
	//
	////////////////////////////////////////////////////////////
	Vector3f getPosition(void) const;

private:
	////////////////////////////////////////////////////////////
	//
	//	Internal representation of the transformation
	//
	////////////////////////////////////////////////////////////
	Mat4x4				m_Transform;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_TRANSFORMABLE_3D_HPP