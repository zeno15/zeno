#ifndef INCLUDED_ZENO_GRAPHICS_SHAPE_HPP
#define INCLUDED_ZENO_GRAPHICS_SHAPE_HPP

#include <zeno/Graphics/Colour.hpp>

#include <zeno/System/Mat4x4.hpp>
#include <zeno/System/Rect.hpp>
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
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Constructor
    ///
    ////////////////////////////////////////////////////////////
    Shape(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief Deconstructor
    ///
    ////////////////////////////////////////////////////////////
    ~Shape(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief Renders the shape
    ///
    /// \param  _transform  Mat4x4 transformation to apply to
    ///                     the shape
    ///
    ////////////////////////////////////////////////////////////
    void render(const zeno::Mat4x4& _transform) const;

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the colour for the internal section
    ///
    /// \param  _colour Colour to be used for the internal section
    ///
    ////////////////////////////////////////////////////////////
    void setInternalColour(const Colour& _colour);
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the colour for the outline
    ///
    /// \param  _colour Colour to be used for the outline
    ///
    ////////////////////////////////////////////////////////////
    void setOutlineColour(const Colour& _colour);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the thickness of the outline
    ///
    /// \param  _thickness  The desired thickness of the outline,
    //          if set to 0, no outline will be drawn
    ///
    ////////////////////////////////////////////////////////////
    void setOutlineThickness(float _thickness);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the bounding box of the Shape
    ///
    /// \return FloatRect Rect representing bounding box of shape
    ///
    ////////////////////////////////////////////////////////////
    FloatRect getBounds(void) const;

protected:
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Internal method that updates the positions of
    ///         the internal section of the shape
    ///
    ////////////////////////////////////////////////////////////
    void updateInternalPositions(void);
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Internal method that updates the positions of
    ///         the outline of the shape
    ///
    ////////////////////////////////////////////////////////////
    void updateOutlinePositions(void);

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Internal method that updates the colours of
    ///         the internal section of the shape
    ///
    ////////////////////////////////////////////////////////////
    void updateInternalColours(void);
    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Internal method that updates the colours of
    ///         the outline of the shape
    ///
    ////////////////////////////////////////////////////////////
    void updateOutlineColours(void);

protected:
    std::vector<zeno::Vector2f> m_Points;       ///<    vector of 2D points the shape is made up of

    Colour m_InternalColour;                    ///<    Colour of the internal section of the shape
    Colour m_OutlineColour;                     ///<    Colour of the outline of the shape

    float m_OutlineThickness;                   ///<    Thickness of the outline

    FloatRect m_InternalBounds;                 ///<    Bounding box of the internal points of the shape
    FloatRect m_OutlineBounds;                  ///<    Bounding box of the outline points of the shape

    unsigned int m_PointsToRender;              ///<    Number of points that need to be rendered for the internal section
    unsigned int m_OutlinePointsToRender;       ///<    Number of points that need to be rendered for the outline

    unsigned int m_InternalVAO;                 ///<    VAO of the internal section
    unsigned int m_InternalPositionVBO;         ///<    VBO representing positions of the internal section
    unsigned int m_InternalColourVBO;           ///<    VBO representing colours of the internal section

    unsigned int m_OutlineVAO;                  ///<    VAO of the outline
    unsigned int m_OutlinePositionVBO;          ///<    VBO representing positions of the outline
    unsigned int m_OutlineColourVBO;            ///<    VBO representing colours of the outline
};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_SHAPE_HPP