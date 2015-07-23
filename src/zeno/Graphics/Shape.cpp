#include <zeno/Graphics/Shape.hpp>

#include <zeno/Graphics/ShaderManager.hpp>
#include <zeno/System/VectorMath.hpp>

#include <GL/glew.h>

#include <limits>

namespace zeno {

Shape::Shape(void) :
m_InternalColour(Colour::Black),
m_OutlineColour(Colour::White),
m_OutlineThickness(0.0f),
m_PointsToRender(0),
m_OutlinePointsToRender(0)
{
    glGenVertexArrays(1, &m_InternalVAO);
    glGenVertexArrays(1, &m_OutlineVAO);

    glGenBuffers(1, &m_InternalPositionVBO);
    glGenBuffers(1, &m_OutlinePositionVBO);
    glGenBuffers(1, &m_InternalColourVBO);
    glGenBuffers(1, &m_OutlineColourVBO);
}

Shape::~Shape(void)
{
    glDeleteBuffers(1, &m_InternalPositionVBO);
    glDeleteBuffers(1, &m_OutlinePositionVBO);
    glDeleteBuffers(1, &m_InternalColourVBO);
    glDeleteBuffers(1, &m_OutlineColourVBO);

    glDeleteVertexArrays(1, &m_InternalVAO);
    glDeleteVertexArrays(1, &m_OutlineVAO);
}

void Shape::render(zeno::Mat4x4& _transform) const
{
    ShaderManager::getInstance().getShader("Zenos_Default_Shader").bind();

    ShaderManager::getInstance().getShader("Zenos_Default_Shader").passUniform("View", _transform * getTransform());

    glBindVertexArray(m_InternalVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_PointsToRender);
    glBindVertexArray(0);

    if (m_OutlineThickness > 0.0f)
    {
        glBindVertexArray(m_OutlineVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, m_OutlinePointsToRender);
        glBindVertexArray(0);
    }

    ShaderManager::getInstance().getShader("Zenos_Default_Shader").unbind();
}

void Shape::setInternalColour(const Colour& _colour)
{
    m_InternalColour = _colour;

    updateInternalColours();
}
void Shape::setOutlineColour(const Colour& _colour)
{
    m_OutlineColour = _colour;

    updateOutlineColours();
}

void Shape::setOutlineThickness(float _thickness)
{
    m_OutlineThickness = _thickness;

    updateOutlinePositions();
}

void Shape::updateInternalPositions(void)
{
    if (m_Points.size() < 3)
    {
        m_PointsToRender = 0;
        return;
    }

    std::vector<float> data((m_Points.size() + 2) * 3, 0.0f);

    float minX = std::numeric_limits<float>().max();
    float maxX = std::numeric_limits<float>().min();
    float minY = std::numeric_limits<float>().max();
    float maxY = std::numeric_limits<float>().min();

    for (unsigned int i = 0; i < m_Points.size(); i += 1)
    {
        data[(i + 1) * 3 + 0] = m_Points[i].x;
        data[(i + 1) * 3 + 1] = m_Points[i].y;
        data[(i + 1) * 3 + 2] = 0.0f;

        minX = std::min(minX, m_Points[i].x);
        maxX = std::max(maxX, m_Points[i].x);

        minY = std::min(minY, m_Points[i].y);
        maxY = std::max(maxY, m_Points[i].y);
    }

    data[0] = (minX + maxX) / 2.0f;
    data[1] = (minY + maxY) / 2.0f;

    data[(m_Points.size() + 1) * 3 + 0] = m_Points.front().x;
    data[(m_Points.size() + 1) * 3 + 1] = m_Points.front().y;

    m_PointsToRender = m_Points.size() + 2;

    glBindVertexArray(m_InternalVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_InternalPositionVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

}
void Shape::updateOutlinePositions(void)
{
    std::vector<float> data((m_Points.size() + 1) * 2 * 3, 0.01f);

    for (unsigned int i = 0; i < m_Points.size(); i += 1)
    {
        Vector2f prevPoint = (i == 0) ? m_Points.back() : m_Points[i - 1];
        Vector2f currPoint = m_Points[i];
        Vector2f nextPoint = (i == m_Points.size() - 1) ? m_Points.front() : m_Points[i + 1];

        Vector2f normal1(currPoint.y - prevPoint.y, prevPoint.x - currPoint.x);
        normalise(normal1);
        Vector2f normal2(nextPoint.y - currPoint.y, currPoint.x - nextPoint.x);
        normalise(normal2);

        float extrusionFactor = 1.0f + normal1.x * normal2.x + normal1.y * normal2.y;

        Vector2f extrusion = Vector2f(normal1 + normal2) / extrusionFactor;

        data[i * 6 + 0] = currPoint.x;
        data[i * 6 + 1] = currPoint.y;
        data[i * 6 + 3] = currPoint.x + extrusion.x * m_OutlineThickness;
        data[i * 6 + 4] = currPoint.y + extrusion.y * m_OutlineThickness;
    }

    data[m_Points.size() * 2 * 3 + 0] = data[0];
    data[m_Points.size() * 2 * 3 + 1] = data[1];
    data[m_Points.size() * 2 * 3 + 3] = data[3];
    data[m_Points.size() * 2 * 3 + 4] = data[4];

    m_OutlinePointsToRender = (m_Points.size() + 1) * 2;

    glBindVertexArray(m_OutlineVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_OutlinePositionVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    updateOutlineColours();
}

void Shape::updateInternalColours(void)
{
    std::vector<float> data((m_Points.size() + 2) * 4, 0.0f);

    for (unsigned int i = 0; i < data.size(); i += 4)
    {
        data[i + 0] = m_InternalColour.r;
        data[i + 1] = m_InternalColour.g;
        data[i + 2] = m_InternalColour.b;
        data[i + 3] = m_InternalColour.a;
    }

    glBindVertexArray(m_InternalVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_InternalColourVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Shape::updateOutlineColours(void)
{
    std::vector<float> data(((m_Points.size() + 1) * 2) * 4, 0.0f);

    for (unsigned int i = 0; i < data.size(); i += 4)
    {
        data[i + 0] = m_OutlineColour.r;
        data[i + 1] = m_OutlineColour.g;
        data[i + 2] = m_OutlineColour.b;
        data[i + 3] = m_OutlineColour.a;
    }

    glBindVertexArray(m_OutlineVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_OutlineColourVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
}

} //~ namespace zeno