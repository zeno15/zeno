#include <zeno/Graphics/Shape.hpp>

#include <zeno/Graphics/ShaderManager.hpp>

#include <GL/glew.h>

#include <limits>
#include <iostream>

namespace zeno {

Shape::Shape(void) :
m_PointsToRender(0),
m_OutlineThickness(0.0f),
m_InternalColour(Colour::Black),
m_OutlineColour(Colour::Black)
{
    glGenVertexArrays(1, &m_VAO);

    glGenBuffers(1, &m_PositionVBO);
    glGenBuffers(1, &m_ColourVBO);
}

Shape::~Shape(void)
{
    glDeleteBuffers(1, &m_PositionVBO);
    glDeleteBuffers(1, &m_ColourVBO);

    glDeleteVertexArrays(1, &m_VAO);
}

void Shape::render(zeno::Mat4x4& _transform) const
{
    ShaderManager::getInstance().getShader("Zenos_Default_Shader").bind();

    ShaderManager::getInstance().getShader("Zenos_Default_Shader").passUniform("View", _transform * getTransform());

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_PointsToRender);
    glBindVertexArray(0);

    ShaderManager::getInstance().getShader("Zenos_Default_Shader").unbind();
}

void Shape::setInternalColour(const Colour& _colour)
{
    m_InternalColour = _colour;

    updateInternalColours();
}

void Shape::updatePositions(void)
{
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

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

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

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
}

} //~ namespace zeno