#ifndef INCLUDED_ZENO_GRAPHICS_SHAPE_HPP
#define INCLUDED_ZENO_GRAPHICS_SHAPE_HPP

#include <zeno/Graphics/Colour.hpp>
#include <zeno/System/Mat4x4.hpp>
#include <zeno/System/Transformable2D.hpp>
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
/// \brief Base class for simple 2D outlined shapes
///
////////////////////////////////////////////////////////////
class Shape : public Transformable2D
{
public:
    Shape(void);

    ~Shape(void);

    void render(zeno::Mat4x4& _transform) const;

    void setInternalColour(const Colour& _colour);

protected:
    void updatePositions(void);

    void updateInternalColours(void);

protected:
    std::vector<zeno::Vector2f> m_Points;

    Colour m_InternalColour;
    Colour m_OutlineColour;

    float m_OutlineThickness;

    unsigned int m_VAO;
    unsigned int m_PositionVBO;
    unsigned int m_ColourVBO;

    unsigned int m_PointsToRender;
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_SHAPE_HPP