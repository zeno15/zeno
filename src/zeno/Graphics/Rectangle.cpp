#include <zeno/Graphics/Rectangle.hpp>

namespace zeno {

Rectangle::Rectangle(const zeno::Vector2f& _size, const zeno::Vector2f& _position /*= zeno::Vector2f()*/) :
Shape()
{
    setPosition(_position);
    setSize(_size);
    updateInternalColours();
}


void Rectangle::setSize(const zeno::Vector2f& _size)
{
    m_Points.clear();

    m_Points.push_back(Vector2f(0.0f,    0.0f));
    m_Points.push_back(Vector2f(_size.x, 0.0f));
    m_Points.push_back(Vector2f(_size.x, _size.y));
    m_Points.push_back(Vector2f(0.0f,    _size.y));

    updatePositions();
}

} //~ namespace zeno