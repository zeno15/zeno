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

////////////////////////////////////////////////////////////
///
///	\class zeno::Rectangle
///	\ingroup Graphics
///
///	Explanation of how this all works
///
///	\code
///
/// zeno::Rectangle r(zeno::Vector2f(100.0f, 100.0f), zeno::Vector2f(250.0f, 50.0f));
/// r.setInternalColour(zeno::Colour::Magenta);
/// r.setOutlineThickness(4.0f);
///
/// p.render(zeno::Mat4x4::Orthographic2D(0.0f, 600.0f, 800.0f, 0.0f);
///
///	\endcode
///
////////////////////////////////////////////////////////////