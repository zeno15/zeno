#ifndef INCLUDED_ZENO_SYSTEM_MAT_4_X_4_HPP
#define INCLUDED_ZENO_SYSTEM_MAT_4_X_4_HPP

#include <string>
#include <vector>
#include <ostream>

#include <zeno/System/Vector3.hpp>
#include <zeno/System/Vector4.hpp>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief  4x4 Matrix class for 3D point manipulation
///
///	When accessing at an index the values are arranged as follows;
///
///	0	4	8	12
///	1	5	9	13
///	2	6	10	14
///	3	7	11	15
///
///	ie, column major, for OpenGL.
///
////////////////////////////////////////////////////////////
class Mat4x4
{
public:
	////////////////////////////////////////////////////////////
	///
    /// \brief  Default constructor
    ///
    /// Initialises all values of Mat4x4 to 0
    ///
	////////////////////////////////////////////////////////////
	Mat4x4(void);

	////////////////////////////////////////////////////////////
	///
    /// \brief  Constructor
    ///
	///	Initialises matrix to I * \a _val
	///
    /// \param  _val    float value to multiply I by
    ///
	////////////////////////////////////////////////////////////
	Mat4x4(float _val);

	////////////////////////////////////////////////////////////
	///
    /// \brief  Constructor
    ///
	///	Initialises the uppermost left-hand 3x3 corner to
	///	the values of the given column vectors
    ///
    /// \param  _x  Vector3 to initialise \a _1, \a _2 and \a _3
    ///
    /// \param  _y  Vector3 to initialise \a _5, \a _6 and \a _7
    ///
    /// \param  _z  Vector3 to initialise \a _9, \a _10 and \a _11
	///
	////////////////////////////////////////////////////////////
	Mat4x4(Vector3<float> _x, Vector3<float> _y, Vector3<float> _z);

	////////////////////////////////////////////////////////////
	///
	/// \brief  Constructor
    ///
    /// Initialises the Mat4x4 from 16 values
    ///
    /// \param  _1  float value to init Mat4x4 value
    ///
    /// \param  _2  float value to init Mat4x4 value
    ///
    /// \param  _3  float value to init Mat4x4 value
    ///
    /// \param  _4  float value to init Mat4x4 value
    ///
    /// \param  _5  float value to init Mat4x4 value
    ///
    /// \param  _6  float value to init Mat4x4 value
    ///
    /// \param  _7  float value to init Mat4x4 value
    ///
    /// \param  _8  float value to init Mat4x4 value
    ///
    /// \param  _9  float value to init Mat4x4 value
    ///
    /// \param  _10 float value to init Mat4x4 value
    ///
    /// \param  _11 float value to init Mat4x4 value
    ///
    /// \param  _12 float value to init Mat4x4 value
    ///
    /// \param  _13 float value to init Mat4x4 value
    ///
    /// \param  _14 float value to init Mat4x4 value
    ///
    /// \param  _15 float value to init Mat4x4 value
    ///
	////////////////////////////////////////////////////////////
	Mat4x4(float _1, float _5, float _9, float _13,
	       float _2, float _6, float _10, float _14,
	       float _3, float _7, float _11, float _15,
	       float _4, float _8, float _12, float _16);
	
	////////////////////////////////////////////////////////////
	///
    ///\brief   Copy constructor
    ///
    /// Initialises the Mat4x4 to have the same values as \a _mat
    ///
    /// \param  _mat    Mat4x4 to init using
    ///
	////////////////////////////////////////////////////////////
	Mat4x4(const Mat4x4& _mat);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief	Overload of assignment (=) operator
    ///
    /// \param  _right  Mat4x4 to copy values from
    ///
    ////////////////////////////////////////////////////////////
    void operator=(const Mat4x4& _right);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief Gets read/write reference to Mat4x4 value at given index
    ///
    /// \param  _right  Index value
    ///
    /// \return read/write reference to value at given index
    ///
    ////////////////////////////////////////////////////////////
    float& operator[](int _right);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief Gets read only reference to Mat4x4 value at given index
    ///
    /// \param  _right  Index value
    ///
    /// \return read only reference to value at given index
    ///
    ////////////////////////////////////////////////////////////
    const float& operator[](int _right) const;
	
	////////////////////////////////////////////////////////////
	///
    /// \brief  Gets a pointer to the float data
    ///
    /// \return const pointer to 16 float values of this Mat4x4
    ///
	////////////////////////////////////////////////////////////
	const float *pointer(void) const;
	
	////////////////////////////////////////////////////////////
	///
	/// \brief	Modifies the matrix so it become the transpose
	///
    /// \return Reference to this Mat4x4 to allow chaining
    ///
	////////////////////////////////////////////////////////////
	Mat4x4& transpose(void);
	
	////////////////////////////////////////////////////////////
	///
	/// \brief	Modifies the matrix so it becomes the inverse
    ///
    /// \return Reference to this Mat4x4 to allow chaining
	///
	////////////////////////////////////////////////////////////
	Mat4x4& inverse(void);
	
	////////////////////////////////////////////////////////////
	///
	///	\brief  Creates a matrix representing an orthographic view
	///	        for use in 2D space
    ///
    /// \param  _left   Coordinates for the left edge of the 2D
    ///                 view area
    ///
    /// \param  _right  Coordinates for the right edge of the 2D
    ///                 view area
    ///
    /// \param  _top    Coordinates for the top edge of the 2D
    ///                 view area
    ///
    /// \param  _bottom Coordinates for the bottom edge of the 2D
    ///                 view area
    ///
    /// \return Mat4x4 representing an Orthographic view matrix
    ///         created from the given parameters
	///
	////////////////////////////////////////////////////////////
	static Mat4x4 Orthographic2D(const float& _left, const float& _right, const float& _top, const float& _bottom);
	
	////////////////////////////////////////////////////////////
    ///
    ///	\brief  Creates a matrix representing an orthographic view
    ///	        for use in 3D space
    ///
    /// \param  _left   Coordinates for the left edge of the 3D
    ///                 view area
    ///
    /// \param  _right  Coordinates for the right edge of the 3D
    ///                 view area
    ///
    /// \param  _top    Coordinates for the top edge of the 3D
    ///                 view area
    ///
    /// \param  _bottom Coordinates for the bottom edge of the 3D
    ///                 view area
    ///
    /// \param  _bottom Coordinates for the near edge of the 3D
    ///                 view area
    ///
    /// \param  _bottom Coordinates for the far edge of the 3D
    ///                 view area
    ///
    /// \return Mat4x4 representing an Orthographic view matrix
    ///         created from the given parameters
    ///
	////////////////////////////////////////////////////////////
	static Mat4x4 Orthographic3D(const float& _left, const float& _right, const float& _top, const float& _bottom, const float& _near, const float& _far);
	
	////////////////////////////////////////////////////////////
	///
    /// \brief  Creates a look-at matrix representing the view matrix
    ///
    /// \param  _eye    Vector3 representing the eye position of
    ///                 the camera
    ///
    /// \param  _pos    Vector3 representing the focus point of
    ///                 the camera
    ///
    /// \param  _up     Vector3 representing the vertical direction
    ///                 from the camera
    ///
    /// \return Mat4x4 look-at matrix
    ///
	////////////////////////////////////////////////////////////
	static Mat4x4 lookat(const Vector3<float>& _eye, const Vector3<float>& _pos, const Vector3<float>& _up);
	
	////////////////////////////////////////////////////////////
	//
	//	Creates the perspective projection matrix
	//
	////////////////////////////////////////////////////////////
	static Mat4x4 perspective(float _fov, float _aspectRatio, float _near, float _far);

	////////////////////////////////////////////////////////////
	///
	///	\brief  Translates the current matrix by the given vector
    ///
    /// \param  _vec    Vector3 representing the desired translation
    ///
    /// \return Reference to this Mat4x4 to allow chaining
	///
	////////////////////////////////////////////////////////////
	Mat4x4& translate(const Vector3f& _vec);
	////////////////////////////////////////////////////////////
	///
    /// \brief  Creates a translation matrix from the given Vector3
    ///
    /// \param  _vec    Vector3 representing the desired translation
    ///
    /// \return Mat4x4 translation matrix
    ///
	////////////////////////////////////////////////////////////
	static Mat4x4 createTranslation(const Vector3f& _vec);
	
	////////////////////////////////////////////////////////////
	///
    /// \brief  Create a rotation matrix around the x axis
    ///
    /// \param  _angle  Desired rotation in radians
    ///
    /// \return Mat4x4 rotation matrix
    ///
	////////////////////////////////////////////////////////////
	static Mat4x4 createRotationX(float _angle);
	////////////////////////////////////////////////////////////
    ///
    /// \brief  Create a rotation matrix around the y axis
    ///
    /// \param  _angle  Desired rotation in radians
    ///
    /// \return Mat4x4 rotation matrix
    ///
	////////////////////////////////////////////////////////////
	static Mat4x4 createRotationY(float _angle);
	////////////////////////////////////////////////////////////
    ///
    /// \brief  Create a rotation matrix around the z axis
    ///
    /// \param  _angle  Desired rotation in radians
    ///
    /// \return Mat4x4 rotation matrix
    ///
	////////////////////////////////////////////////////////////
	static Mat4x4 createRotationZ(float _angle);
	////////////////////////////////////////////////////////////
	///
    /// \brief  Create a scale matrix
    ///
    /// \param  _scale  Vector3 representing the desired scale
    ///
    /// \return Mat4x4 scale matrix
    ///
	////////////////////////////////////////////////////////////
	static Mat4x4 createScale(const Vector3f & _scale);

private:
	std::vector<float> values;  ///<    vector containing the 16 floats
};

////////////////////////////////////////////////////////////
//
//	Overload of << operator
//	Allows you to directly print contents of matrix
//
////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Mat4x4& _mat);

////////////////////////////////////////////////////////////
//
//	Overload of != operator
//	Checks if two matrices are different, no tolerance
//
////////////////////////////////////////////////////////////
bool operator !=(const Mat4x4& _left, const Mat4x4& _right);

////////////////////////////////////////////////////////////
//
//	Overload of == operator
//
////////////////////////////////////////////////////////////
bool operator ==(const Mat4x4& _left, const Mat4x4& _right);

////////////////////////////////////////////////////////////
//
//	Returns the resultant vector when multiplying a matrix by a vector
//
////////////////////////////////////////////////////////////
Vector4<float> operator*(const Mat4x4& _left, const Vector4<float>& _right);
////////////////////////////////////////////////////////////
//
//	Returns the resultant vector when multiplying a matrix by a vector
//
////////////////////////////////////////////////////////////
Vector3<float> operator*(const Mat4x4& _left, const Vector3<float>& _right);
////////////////////////////////////////////////////////////
//
//	Returns the resultant matrix when multiplying one by another
//
////////////////////////////////////////////////////////////
Mat4x4 operator*(const Mat4x4& _left, const Mat4x4& _right);
////////////////////////////////////////////////////////////
//
//	Modifies _left by performing matrix multiplication by
//	_right
//
////////////////////////////////////////////////////////////
Mat4x4 operator*=(Mat4x4& _left, const Mat4x4& _right);

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_MAT_4_X_4_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Mat4x4
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code
///	zeno::Mat4x4 mat = zeno::Mat4x4(1.0f);
///	\endcode
///
////////////////////////////////////////////////////////////