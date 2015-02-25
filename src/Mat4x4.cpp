#include <Mat4x4.hpp>

#include <iostream>
#include <sstream>
#include <algorithm>

namespace zeno {

Mat4x4::Mat4x4(void) :
Mat4x4(0.0f, 0.0f, 0.0f, 0.0f,
       0.0f, 0.0f, 0.0f, 0.0f,
       0.0f, 0.0f, 0.0f, 0.0f,
       0.0f, 0.0f, 0.0f, 0.0f)

{
}

Mat4x4::Mat4x4(float _val) :
Mat4x4(_val, 0.0f, 0.0f, 0.0f,
       0.0f, _val, 0.0f, 0.0f,
       0.0f, 0.0f, _val, 0.0f,
       0.0f, 0.0f, 0.0f, _val)
{
}

Mat4x4::Mat4x4(Vector3<float> _x, Vector3<float> _y, Vector3<float> _z) :
Mat4x4(_x.x, _y.x, _z.x, 0.0f,
       _x.y, _y.y, _z.y, 0.0f,
       _x.z, _y.z, _z.z, 0.0f,
       0.0f, 0.0f, 0.0f, 1.0f)
{
}
//~ To change column/row major change this constructor
Mat4x4::Mat4x4(float _1, float _5, float _9, float _13,
	       float _2, float _6, float _10, float _14,
	       float _3, float _7, float _11, float _15,
	       float _4, float _8, float _12, float _16)
{
	values = std::vector<float>(16);

	values[0] = _1;
	values[1] = _2;
	values[2] = _3;
	values[3] = _4;

	values[4] = _5;
	values[5] = _6;
	values[6] = _7;
	values[7] = _8;

	values[8] = _9;
	values[9] = _10;
	values[10] = _11;
	values[11] = _12;

	values[12] = _13;
	values[13] = _14;
	values[14] = _15;
	values[15] = _16;
}

Mat4x4::Mat4x4(const Mat4x4& _mat)
{
	values = std::vector<float>(16);
	
	for (unsigned int i = 0; i < 16; i += 1)
	{
		values[i] = _mat.values[i];
	}
}


const float *Mat4x4::pointer(void) const
{
	return values.data();
}

Mat4x4& Mat4x4::transpose(void)
{
	
	for (unsigned int i = 0; i < 4; i += 1)
	{
		for (unsigned int j = 0; j < 4; j += 1)
		{
			if (i <= j) continue;
			
			std::swap(values[i * 4 + j], values[j * 4 + i]);
		}
	}
	return *this;
}

Mat4x4& Mat4x4::inverse(void)
{
	float inv[16], det;
	
	inv[0] = values[5]  * values[10] * values[15] - 
             values[5]  * values[11] * values[14] - 
             values[9]  * values[6]  * values[15] + 
             values[9]  * values[7]  * values[14] +
             values[13] * values[6]  * values[11] - 
             values[13] * values[7]  * values[10];

    inv[4] = -values[4]  * values[10] * values[15] + 
              values[4]  * values[11] * values[14] + 
              values[8]  * values[6]  * values[15] - 
              values[8]  * values[7]  * values[14] - 
              values[12] * values[6]  * values[11] + 
              values[12] * values[7]  * values[10];

    inv[8] = values[4]  * values[9] * values[15] - 
             values[4]  * values[11] * values[13] - 
             values[8]  * values[5] * values[15] + 
             values[8]  * values[7] * values[13] + 
             values[12] * values[5] * values[11] - 
             values[12] * values[7] * values[9];

    inv[12] = -values[4]  * values[9] * values[14] + 
               values[4]  * values[10] * values[13] +
               values[8]  * values[5] * values[14] - 
               values[8]  * values[6] * values[13] - 
               values[12] * values[5] * values[10] + 
               values[12] * values[6] * values[9];

    inv[1] = -values[1]  * values[10] * values[15] + 
              values[1]  * values[11] * values[14] + 
              values[9]  * values[2] * values[15] - 
              values[9]  * values[3] * values[14] - 
              values[13] * values[2] * values[11] + 
              values[13] * values[3] * values[10];

    inv[5] = values[0]  * values[10] * values[15] - 
             values[0]  * values[11] * values[14] - 
             values[8]  * values[2] * values[15] + 
             values[8]  * values[3] * values[14] + 
             values[12] * values[2] * values[11] - 
             values[12] * values[3] * values[10];

    inv[9] = -values[0]  * values[9] * values[15] + 
              values[0]  * values[11] * values[13] + 
              values[8]  * values[1] * values[15] - 
              values[8]  * values[3] * values[13] - 
              values[12] * values[1] * values[11] + 
              values[12] * values[3] * values[9];

    inv[13] = values[0]  * values[9] * values[14] - 
              values[0]  * values[10] * values[13] - 
              values[8]  * values[1] * values[14] + 
              values[8]  * values[2] * values[13] + 
              values[12] * values[1] * values[10] - 
              values[12] * values[2] * values[9];

    inv[2] = values[1]  * values[6] * values[15] - 
             values[1]  * values[7] * values[14] - 
             values[5]  * values[2] * values[15] + 
             values[5]  * values[3] * values[14] + 
             values[13] * values[2] * values[7] - 
             values[13] * values[3] * values[6];

    inv[6] = -values[0]  * values[6] * values[15] + 
              values[0]  * values[7] * values[14] + 
              values[4]  * values[2] * values[15] - 
              values[4]  * values[3] * values[14] - 
              values[12] * values[2] * values[7] + 
              values[12] * values[3] * values[6];

    inv[10] = values[0]  * values[5] * values[15] - 
              values[0]  * values[7] * values[13] - 
              values[4]  * values[1] * values[15] + 
              values[4]  * values[3] * values[13] + 
              values[12] * values[1] * values[7] - 
              values[12] * values[3] * values[5];

    inv[14] = -values[0]  * values[5] * values[14] + 
               values[0]  * values[6] * values[13] + 
               values[4]  * values[1] * values[14] - 
               values[4]  * values[2] * values[13] - 
               values[12] * values[1] * values[6] + 
               values[12] * values[2] * values[5];

    inv[3] = -values[1] * values[6] * values[11] + 
              values[1] * values[7] * values[10] + 
              values[5] * values[2] * values[11] - 
              values[5] * values[3] * values[10] - 
              values[9] * values[2] * values[7] + 
              values[9] * values[3] * values[6];

    inv[7] = values[0] * values[6] * values[11] - 
             values[0] * values[7] * values[10] - 
             values[4] * values[2] * values[11] + 
             values[4] * values[3] * values[10] + 
             values[8] * values[2] * values[7] - 
             values[8] * values[3] * values[6];

    inv[11] = -values[0] * values[5] * values[11] + 
               values[0] * values[7] * values[9] + 
               values[4] * values[1] * values[11] - 
               values[4] * values[3] * values[9] - 
               values[8] * values[1] * values[7] + 
               values[8] * values[3] * values[5];

    inv[15] = values[0] * values[5] * values[10] - 
              values[0] * values[6] * values[9] - 
              values[4] * values[1] * values[10] + 
              values[4] * values[2] * values[9] + 
              values[8] * values[1] * values[6] - 
              values[8] * values[2] * values[5];
			  
	det = values[0] * inv[0] + values[1] * inv[4] + values[2] * inv[8] + values[3] * inv[12];
	
	if (det == 0.0f)
	{
		return *this;
	}
	
	det = 1.0f / det;
	
	for (unsigned int i = 0; i < 16; i += 1)
	{
		values[i] = inv[i] * det;
	}
	
	return *this;
}
//~ https://github.com/g-truc/glm/blob/master/glm/gtc/matrix_transform.inl
Mat4x4 Mat4x4::Orthographic2D(const float& _left, const float& _right, const float& _top, const float& _bottom)
{
	Mat4x4 mat(1.0f);
	
	mat[0] = 2.0f / (_right - _left);
	mat[5] = 2.0f / (_top - _bottom);
	mat[10] = -1.0f;
	
	mat[12] = -(_right + _left) / (_right - _left);
	mat[13] = -(_top + _bottom) / (_top - _bottom);
	
	return mat;
}
	
Mat4x4 Mat4x4::Orthographic3D(const float& _left, const float& _right, const float& _top, const float& _bottom, const float& _near, const float& _far)
{
	Mat4x4 mat(1.0f);
	
	mat[0] = 2.0f / (_right - _left);
	mat[5] = 2.0f / (_top - _bottom);
	mat[10] = 2.0f / (_far - _near);

	mat[12] = -(_right + _left) / (_right - _left);
	mat[13] = -(_top + _bottom) / (_top - _bottom);
	mat[14] = -(_far + _near) / (_far - _near);
	
	return mat;
}

Mat4x4 Mat4x4::lookat(const Vector3<float>& _eye, const Vector3<float>& _pos, const Vector3<float>& _up)
{
	Mat4x4 mat = Mat4x4(1.0f);
	
	return mat;
}

Mat4x4 Mat4x4::perspective(float _fov, float _aspectRatio, float _near, float _far)
{
	Mat4x4 mat = Mat4x4(1.0f);
	
	return mat;
}

std::ostream& operator<<(std::ostream& os, const Mat4x4& _mat)
{
	os << 
	_mat.values[0] << " " << _mat.values[4] << " " << _mat.values[8]	<< " " << _mat.values[12] << std::endl <<
	_mat.values[1] << " " << _mat.values[5] << " " << _mat.values[9]	<< " " << _mat.values[13] << std::endl <<
	_mat.values[2] << " " << _mat.values[6] << " " << _mat.values[10]	<< " " << _mat.values[14] << std::endl <<
	_mat.values[3] << " " << _mat.values[7] << " " << _mat.values[11]	<< " " << _mat.values[15] << std::endl;

	return os;
}

bool operator ==(const Mat4x4& _left, const Mat4x4& _right)
{
	return (_left.values[0] == _right.values[0] &&
		_left.values[1] == _right.values[1] &&
		_left.values[2] == _right.values[2] &&
		_left.values[3] == _right.values[3] &&

		_left.values[4] == _right.values[4] &&
		_left.values[5] == _right.values[5] &&
		_left.values[6] == _right.values[6] &&
		_left.values[7] == _right.values[7] &&

		_left.values[8] == _right.values[8] &&
		_left.values[9] == _right.values[9] &&
		_left.values[10] == _right.values[10] &&
		_left.values[11] == _right.values[11] &&

		_left.values[12] == _right.values[12] &&
		_left.values[13] == _right.values[13] &&
		_left.values[14] == _right.values[14] &&
		_left.values[15] == _right.values[15]);
}

bool operator !=(const Mat4x4& _left, const Mat4x4& _right)
{
	return !(_left == _right);
}

Vector4<float> operator*(const Mat4x4& _left, const Vector4<float>& _right)
{
	return Vector4<float>(	_left.values[0] * _right.x + _left.values[4] * _right.y + _left.values[8] * _right.z + _left.values[12] * _right.w,
							_left.values[1] * _right.x + _left.values[5] * _right.y + _left.values[9] * _right.z + _left.values[13] * _right.w,
							_left.values[2] * _right.x + _left.values[6] * _right.y + _left.values[10] * _right.z + _left.values[14] * _right.w,
							_left.values[3] * _right.x + _left.values[7] * _right.y + _left.values[11] * _right.z + _left.values[15] * _right.w);
}

Vector3<float> operator*(const Mat4x4& _left, const Vector3<float>& _right)
{
	Vector4<float> result = _left * Vector4<float>(_right, 1.0f);
	
	return Vector3<float>(result.x, result.y, result.z);
}

Mat4x4 operator*(const Mat4x4& _left, const Mat4x4& _right)
{
	Mat4x4 result;
	
	for (unsigned int i = 0; i < 4; i += 1)
	{
		for (unsigned int j = 0; j < 4; j += 1)
		{
			result.values[j * 4 + i] = 	_left.values[0 + i] * 	_right.values[0 + 4 * j] +
										_left.values[4 + i] * 	_right.values[1 + 4 * j] +
										_left.values[8 + i] * 	_right.values[2 + 4 * j] +
										_left.values[12 + i] * 	_right.values[3 + 4 * j];
		}
	}
	
	return result;
}

float& Mat4x4::operator[](int _right)
{
	return values[_right];
}

const float& Mat4x4::operator[](int _right) const
{
	return values[_right];
}

void Mat4x4::operator=(const Mat4x4& _right)
{
	for (unsigned int i = 0; i < 16; i += 1)
	{
		values[i] = _right.values[i];
	}
}

} //~ namespace zeno
