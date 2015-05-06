#include <zeno/System/Transformable3D.hpp>

namespace zeno {

Transformable3D::Transformable3D(void) :
m_Transform(1.0f)
{
}


void Transformable3D::resetTransformation(void)
{
	m_Transform = Mat4x4(1.0f);
}


const Mat4x4& Transformable3D::getTransform(void) const
{
	return m_Transform;
}

Mat4x4& Transformable3D::getTransform(void)
{
	return m_Transform;
}


void Transformable3D::move(const Vector3f& _offset)
{
	setPosition(getPosition() + _offset);
}

void Transformable3D::setPosition(const Vector3f& _position)
{
	m_Transform[12] = _position.x;
	m_Transform[13] = _position.y;
	m_Transform[14] = _position.z;
}

Vector3f Transformable3D::getPosition(void) const
{
	return Vector3f(m_Transform[12], m_Transform[13], m_Transform[14]);
}

} //~ namespace zeno