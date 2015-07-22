#ifndef INCLUDED_ZENO_GRAPHICS_RECTANGLE_HPP
#define INCLUDED_ZENO_GRAPHICS_RECTANGLE_HPP

#include <zeno/Graphics/Shape.hpp>

namespace zeno {

class Rectangle : public Shape
{
public:
    Rectangle(const zeno::Vector2f& _size, const zeno::Vector2f& _position = zeno::Vector2f());

    void setSize(const zeno::Vector2f& _size);
private:


};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_RECTANGLE_HPP