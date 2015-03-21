template <typename T>
inline Vector2<T>::Vector2() :
x(0),
y(0)
{
}

template <typename T>
inline Vector2<T>::Vector2(T _x, T _y) :
x(_x),
y(_y)
{
}

template <typename T>
template <typename U>
inline Vector2<T>::Vector2(const Vector2<U>& _vec) :
x(static_cast<T>(_vec.x)),
y(static_cast<T>(_vec.y))
{
}


template <typename T>
inline Vector2<T> operator -(const Vector2<T>& _right)
{
	return Vector2<T>(- _right.x, - _right.y);
}

template <typename T>
inline Vector2<T>& operator -=(Vector2<T>& _left, const Vector2<T>& _right)
{
	_left.x -= _right.x;
	_left.y -= _right.y;

	return _left;
}

template <typename T>
inline Vector2<T> operator -(const Vector2<T>& _left, const Vector2<T>& _right)
{
	return Vector2<T>(_left.x - _right.x, _left.y - _right.y);
}

template <typename T>
inline Vector2<T> operator +=(Vector2<T>& _left, const Vector2<T>& _right)
{
	_left.x += _right.x;
	_left.y += _right.y;

	return _left;
}

template <typename T>
inline Vector2<T> operator +(const Vector2<T>& _left, const Vector2<T>& _right)
{
	return Vector2<T>(_left.x + _right.x, _left.y + _right.y);
}

template <typename T>
inline Vector2<T>& operator /=(Vector2<T>& _left, T _right)
{
	_left.x /= _right;
	_left.y /= _right;

	return _left;
}

template <typename T>
inline Vector2<T> operator /(const Vector2<T>& _left, T _right)
{
	return Vector2<T>(_left.x / _right, _left.y / _right);
}

template <typename T>
inline Vector2<T> operator *=(Vector2<T>& _left, T _right)
{
	_left.x *= _right;
	_left.y *= _right;

	return _left;
}

template <typename T>
inline Vector2<T> operator *(const Vector2<T>& _left, T _right)
{
	return Vector2<T>(_left.x * _right, _left.y * _right);
}

template <typename T>
inline Vector2<T> operator *(T _left, const Vector2<T>& _right)
{
	return Vector2<T>(_left * _right.x, _left * _right.y);
}

template <typename T>
inline bool operator ==(const Vector2<T>& _left, const Vector2<T>& _right)
{
	return (_left.x == _right.x && _left.y == _right.y);
}

template <typename T>
inline bool operator !=(const Vector2<T>& _left, const Vector2<T>& _right)
{
	return !(_left == _right);
}

template <typename T>
std::ostream& operator <<(std::ostream& os, zeno::Vector2<T> const& _vec)
{
	os << "x: " << _vec.x << ", y: " << _vec.y;
	return os;
}
