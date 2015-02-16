template <typename T>
inline Vector4<T>::Vector4() :
x(0),
y(0),
z(0),
w(0)
{
}

template <typename T>
inline Vector4<T>::Vector4(T _x, T _y, T _z, T _w) :
x(_x),
y(_y),
z(_z),
w(_w)
{
}

template <typename T>
template <typename U>
inline Vector4<T>::Vector4(const Vector4<U>& _vec) :
x(static_cast<T>(_vec.x)),
y(static_cast<T>(_vec.y)),
z(static_cast<T>(_vec.z)),
w(static_cast<T>(_vec.w))
{
}

template <typename T>
inline Vector4<T>::Vector4(const Vector3<T>& _vec, T _w) :
x(static_cast<T>(_vec.x)),
y(static_cast<T>(_vec.y)),
z(static_cast<T>(_vec.z)),
w(static_cast<T>(_w))
{
}


template <typename T>
inline Vector4<T> operator -(const Vector4<T>& _right)
{
	return Vector4<T>(- _right.x, - _right.y, - _right.z, _right.w);
}

template <typename T>
inline Vector4<T>& operator -=(Vector4<T>& _left, const Vector4<T>& _right)
{
	_left.x -= _right.x;
	_left.y -= _right.y;
	_left.z -= _right.z;

	return _left;
}

template <typename T>
inline Vector4<T> operator -(const Vector4<T>& _left, const Vector4<T>& _right)
{
	return Vector4<T>(_left.x - _right.x, _left.y - _right.y, _left.z - _right.z, _left.w);
}

template <typename T>
inline Vector4<T> operator +=(Vector4<T>& _left, const Vector4<T>& _right)
{
	_left.x += _right.x;
	_left.y += _right.y;
	_left.z += _right.z;

	return _left;
}

template <typename T>
inline Vector4<T> operator +(const Vector4<T>& _left, const Vector4<T>& _right)
{
	return Vector4<T>(_left.x + _right.x, _left.y + _right.y, _left.z + _right.z, _left.w);
}

template <typename T>
inline Vector4<T>& operator /=(Vector4<T>& _left, T _right)
{
	_left.x /= _right;
	_left.y /= _right;
	_left.z /= _right;

	return _left;
}

template <typename T>
inline Vector4<T> operator /(const Vector4<T>& _left, T _right)
{
	return Vector4<T>(_left.x / _right, _left.y / _right, _left.z / _right, _left.w);
}

template <typename T>
inline Vector4<T> operator *=(Vector4<T>& _left, T _right)
{
	_left.x *= _right;
	_left.y *= _right;
	_left.z *= _right;

	return _left;
}

template <typename T>
inline Vector4<T> operator *(const Vector4<T>& _left, T _right)
{
	return Vector4<T>(_left.x * _right, _left.y * _right, _left.z * _right, _left.w);
}

template <typename T>
inline Vector4<T> operator *(T _left, const Vector4<T>& _right)
{
	return Vector4<T>(_left * _right.x, _left * _right.y, _left * _right.z, _right.w);
}

template <typename T>
inline bool operator ==(const Vector4<T>& _left, const Vector4<T>& _right)
{
	return (_left.x == _right.x &&
		_left.y == _right.y &&
		_left.z == _right.z &&
		_left.w == _right.w);
}

template <typename T>
inline bool operator !=(const Vector4<T>& _left, const Vector4<T>& _right)
{
	return (!(_left == _right));
}
