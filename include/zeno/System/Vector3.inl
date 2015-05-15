template <typename T>
inline Vector3<T>::Vector3() :
x(0),
y(0),
z(0)
{
}

template <typename T>
inline Vector3<T>::Vector3(T _x, T _y, T _z) :
x(_x),
y(_y),
z(_z)
{
}

template <typename T>
template <typename U>
inline Vector3<T>::Vector3(const Vector3<U>& _vec) :
x(static_cast<T>(_vec.x)),
y(static_cast<T>(_vec.y)),
z(static_cast<T>(_vec.z))
{
}



template <typename T>
inline Vector3<T> operator -(const Vector3<T>& _right)
{
	return Vector3<T>(- _right.x, - _right.y, - _right.z);
}

template <typename T>
inline Vector3<T>& operator -=(Vector3<T>& _left, const Vector3<T>& _right)
{
	_left.x -= _right.x;
	_left.y -= _right.y;
	_left.z -= _right.z;

	return _left;
}

template <typename T>
inline Vector3<T> operator -(const Vector3<T>& _left, const Vector3<T>& _right)
{
	return Vector3<T>(_left.x - _right.x, _left.y - _right.y, _left.z - _right.z);
}

template <typename T>
inline Vector3<T> operator +=(Vector3<T>& _left, const Vector3<T>& _right)
{
	_left.x += _right.x;
	_left.y += _right.y;
	_left.z += _right.z;

	return _left;
}

template <typename T>
inline Vector3<T> operator +(const Vector3<T>& _left, const Vector3<T>& _right)
{
	return Vector3<T>(_left.x + _right.x, _left.y + _right.y, _left.z + _right.z);
}

template <typename T>
inline Vector3<T>& operator /=(Vector3<T>& _left, T _right)
{
	_left.x /= _right;
	_left.y /= _right;
	_left.z /= _right;

	return _left;
}

template <typename T>
inline Vector3<T> operator /(const Vector3<T>& _left, T _right)
{
	return Vector3<T>(_left.x / _right, _left.y / _right, _left.z / _right);
}

template <typename T>
inline Vector3<T> operator *=(Vector3<T>& _left, T _right)
{
	_left.x *= _right;
	_left.y *= _right;
	_left.z *= _right;

	return _left;
}

template <typename T>
inline Vector3<T> operator *(const Vector3<T>& _left, T _right)
{
	return Vector3<T>(_left.x * _right, _left.y * _right, _left.z * _right);
}

template <typename T>
inline Vector3<T> operator *(T _left, const Vector3<T>& _right)
{
	return Vector3<T>(_left * _right.x, _left * _right.y, _left * _right.z);
}

template <typename T>
inline bool operator ==(const Vector3<T>& _left, const Vector3<T>& _right)
{
	return (_left.x == _right.x &&
		_left.y == _right.y &&
		_left.z == _right.z);
}

template <typename T>
inline bool operator !=(const Vector3<T>& _left, const Vector3<T>& _right)
{
	return (!(_left == _right));
}

template <typename T>
std::ostream& operator <<(std::ostream& os, zeno::Vector3<T> const& _vec)
{
	os << "x: " << _vec.x << ", y: " << _vec.y << ", z: " << _vec.z;
	return os;
}
