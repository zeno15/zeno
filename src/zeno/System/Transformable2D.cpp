#include <zeno/System/Transformable2D.hpp>

namespace zeno {

Transformable2D::Transformable2D(void) :
m_Transform(1.0f)
{
}


void Transformable2D::resetTransformation(void)
{
    m_Transform = Mat4x4(1.0f);
}


const Mat4x4& Transformable2D::getTransform(void) const
{
    return m_Transform;
}

Mat4x4& Transformable2D::getTransform(void)
{
    return m_Transform;
}


void Transformable2D::move(const Vector2f& _offset)
{
    m_Transform[12] += _offset.x;
    m_Transform[13] += _offset.y;
}

void Transformable2D::setPosition(const Vector2f& _position)
{
    m_Transform[12] = _position.x;
    m_Transform[13] = _position.y;
}

Vector2f Transformable2D::getPosition(void) const
{
    return Vector2f(m_Transform[12], m_Transform[13]);
}

} //~ namespace zeno