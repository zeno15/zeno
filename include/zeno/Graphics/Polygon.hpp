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
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_CONVEX_POLYGON_HPP