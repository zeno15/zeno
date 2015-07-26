#ifndef INCLUDED_ZENO_GRAPHICS_CIRCLE_HPP
#define INCLUDED_ZENO_GRAPHICS_CIRCLE_HPP

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
///         circles
///
////////////////////////////////////////////////////////////
class Circle : public Shape
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Constructor
    ///
    /// \param  _radius Desired radius of the circle
    ///
    /// \param  _points Desired number of points to make the
    ///                 circle from
    ///
    ////////////////////////////////////////////////////////////
    Circle(float _radius, unsigned int _points = 30);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the radius of the circle
    ///
    /// \param  _radius Desired radius size
    ///
    ////////////////////////////////////////////////////////////
    void setRadius(float _radius);
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the number of points to make the circle from
    ///
    /// \param  _points Desired number of points to make the
    ///                 circle from
    ///
    ////////////////////////////////////////////////////////////
    void setPoints(unsigned int _points);

private:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Internal method to regenerate the points
    ///
    ////////////////////////////////////////////////////////////
    void regeneratePoints(void);

private:
    unsigned int m_CirclePoints;        ///<    Number of points the circle is made from

    float m_Radius;                     ///<    Radius of the circle
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_CIRCLE_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Circle
///	\ingroup Graphics
///
///	Explanation of how this all works
///
///	\code
///
/// zeno::Circle c(64.0f);
/// c.setPosition(zeno::Vector2f(96.0f, 96.0f));
/// c.setOutlineColour(zeno::Colour::Magenta);
/// c.setOutlineThickness(14.0f);
///
/// p.render(zeno::Mat4x4::Orthographic2D(0.0f, 600.0f, 800.0f, 0.0f);
///
///	\endcode
///
////////////////////////////////////////////////////////////