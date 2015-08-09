#include <cmath>

template <typename T>
T length(const Vector2<T>& _vec)
{
    return static_cast<T>(sqrt(_vec.x * _vec.x + _vec.y * _vec.y));
}

template <typename T>
T length(const Vector3<T>& _vec)
{
    return static_cast<T>(sqrt(_vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z));
}

template <typename T>
T length(const Vector4<T>& _vec)
{
    return static_cast<T>(sqrt(_vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z));
}

template <typename T>
T distance(const Vector2<T>& _vec1, const Vector2<T>& _vec2)
{
    return length(_vec2 - _vec1);
}

template <typename T>
T distance(const Vector3<T>& _vec1, const Vector3<T>& _vec2)
{
    return length(_vec2 - _vec1);
}


template <typename T>
T lengthSquared(const Vector2<T>& _vec)
{
    return _vec.x * _vec.x + _vec.y * _vec.y;
}

template <typename T>
T lengthSquared(const Vector3<T>& _vec)
{
    return _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z;
}

template <typename T>
T lengthSquared(const Vector4<T>& _vec)
{
    return _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z;
}


template <typename T>
inline Vector2<T>& normalise(Vector2<T>& _vec)
{
    _vec /= length(_vec);

    return _vec;
}

template <typename T>
inline Vector3<T>& normalise(Vector3<T>& _vec)
{
    _vec /= length(_vec);

    return _vec;
}

template <typename T>
inline Vector4<T>& normalise(Vector4<T>& _vec)
{
    _vec /= length(_vec);

    return _vec;
}


template <typename T>
inline Vector3<T> cross(const Vector3<T>& _left, const Vector3<T>& _right)
{
    return Vector3<T>(_left.y * _right.z - _left.z * _right.y,
                      _left.z * _right.x - _left.x * _right.z,
                      _left.x * _right.y - _left.y * _right.x);
}

template <typename T>
inline Vector4<T> cross(const Vector4<T>& _left, const Vector4<T>& _right)
{
    return Vector4<T>(_left.y * _right.z - _left.z * _right.y,
                      _left.z * _right.x - _left.x * _right.z,
                      _left.x * _right.y - _left.y * _right.x,
                      static_cast<T>(1));
}


template <typename T>
inline T dot(const Vector2<T>& _left, const Vector2<T>& _right)
{
    return _left.x * _right.x + _left.y * _right.y;
}

template <typename T>
inline T dot(const Vector3<T>& _left, const Vector3<T>& _right)
{
    return _left.x * _right.x + _left.y * _right.y + _left.z * _right.z;
}