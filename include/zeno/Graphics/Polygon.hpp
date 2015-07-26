#ifndef INCLUDED_ZENO_GRAPHICS_CONVEX_POLYGON_HPP
#define INCLUDED_ZENO_GRAPHICS_CONVEX_POLYGON_HPP

#include <zeno/Graphics/Shape.hpp>
#include <zeno/System/Vector2.hpp>

#include <vector>

////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
/// \brief  Class extending Shape allowing for drawing of
///         arbitrary convex shapes
///
////////////////////////////////////////////////////////////
class Polygon : public Shape
{
public:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Adds a single point to the shape
    ///
    /// \param  _point Vector2f position of the point
    ///
    /// \param  _update Boolean whether or not to construct the
    ///                 shape or not
    ///
    ////////////////////////////////////////////////////////////
    void addPoint(const Vector2f& _point, bool _update = true);
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Adds a vector of points to the shape
    ///
    /// \param  _points std::vector<Vector2f> positions to add
    ///
    ////////////////////////////////////////////////////////////
    void addPoints(const std::vector<Vector2f>& _points);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief Clears all points so new ones can be added
    ///
    ////////////////////////////////////////////////////////////
    void clearPoints(void);
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_CONVEX_POLYGON_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Polygon
///	\ingroup Graphics
///
///	Explanation of how this all works
///
///	\code
///
///	zeno::Polygon p;
///	p.addPoint(zeno::Vector2f(-50.0f, -50.0f), false);
///	p.addPoint(zeno::Vector2f(0.0f, -20.0f), false);
///	p.addPoint(zeno::Vector2f(50.0f, -50.0f), false);
///	p.addPoint(zeno::Vector2f(0.0f, 50.0f));
///	p.setOutlineThickness(4.0f);
///
/// p.render(zeno::Mat4x4::Orthographic2D(0.0f, 600.0f, 800.0f, 0.0f);
///
///	\endcode
///
////////////////////////////////////////////////////////////