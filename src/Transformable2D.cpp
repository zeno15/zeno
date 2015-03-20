#include <Transformable2D.hpp>

namespace zeno {

void Transformable2D::setPosition(const Vector2f& _position)
{
	m_Position = _position;
}

const Vector2f& Transformable2D::getPosition(void) const
{
	return m_Position;
}

} //~ namespace zeno