#include <zeno/System/Transformable2D.hpp>

namespace zeno {

void Transformable2D::setPosition(const Vector2f& _position)
{
	m_Position = _position;
}
void Transformable2D::move(const Vector2f& _offset)
{
	setPosition(_offset + getPosition());
}

const Vector2f& Transformable2D::getPosition(void) const
{
	return m_Position;
}

Mat4x4 Transformable2D::getTransform(void) const
{
	return Mat4x4::createTranslation(Vector3f(m_Position.x, m_Position.y, 0.0f));
}

} //~ namespace zenocd ze