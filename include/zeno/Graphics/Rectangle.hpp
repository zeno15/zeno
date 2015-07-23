#ifndef INCLUDED_ZENO_GRAPHICS_RECTANGLE_HPP
#define INCLUDED_ZENO_GRAPHICS_RECTANGLE_HPP

#include <zeno/Graphics/Shape.hpp>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief  Class extending Shape allowing for drawing of
///         rectangular shapes
///
////////////////////////////////////////////////////////////
class Rectangle : public Shape
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Constructor
    ///
    /// \param  _size   Vector2f representing the size of the
    ///                 rectangle
    ///
    /// \param  _position   Vector2f representing the position
    ///                     of the lower left corner
    ///
    ////////////////////////////////////////////////////////////
    Rectangle(const zeno::Vector2f& _size, const zeno::Vector2f& _position = zeno::Vector2f());

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the size of the rectangle
    ///
    /// \param  _size   New size of the rectangle
    ///
    ////////////////////////////////////////////////////////////
    void setSize(const zeno::Vector2f& _size);
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_RECTANGLE_HPP