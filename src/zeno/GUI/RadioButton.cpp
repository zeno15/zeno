#include <zeno/GUI/RadioButton.hpp>

#include <zeno/Graphics.hpp>
#include <zeno/GUI/GUIEvent.hpp>

#include <zeno/System/VectorMath.hpp>

#include <GL/glew.h>
#include <iostream>

#define MAX_RADIUS 8.0f
#define POINTS_IN_CIRCLE 16
#define NUM_VERTEXES (POINTS_IN_CIRCLE * 3 * 3)
namespace zeno {

RadioButton::RadioButton(const std::string& _id, GuiBase *_parent, Desktop& _desktop) :
GuiBase(_id, _parent, _desktop),
m_Checked(false)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //~ Positions
    glGenBuffers(1, &m_PositionVBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NUM_VERTEXES * zenoGLEWDefinitions::FLOATS_IN_POSITION, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, zenoGLEWDefinitions::FLOATS_IN_POSITION, GL_FLOAT, GL_FALSE, 0, nullptr);

    //~ Colours
    glGenBuffers(1, &m_ColourVBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NUM_VERTEXES * zenoGLEWDefinitions::FLOATS_IN_COLOUR, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, zenoGLEWDefinitions::FLOATS_IN_COLOUR, GL_FLOAT, GL_FALSE, 0, nullptr);

    initialisePositions();
    initialiseColours();
}

RadioButton::~RadioButton(void)
{
    glDeleteBuffers(1, &m_PositionVBO);
    glDeleteBuffers(1, &m_ColourVBO);

    glDeleteVertexArrays(1, &m_VAO);
}

RadioButton *RadioButton::createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop)
{
    return new RadioButton(_id, _parent, _desktop);
}


bool RadioButton::processEvent(const GUIEvent& _event)
{
    if (_event.type == GUIEvent::EventType::LeftClick)
    {
        Vector2f pos(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y));

        Vector2f center(getPosition().x, getPosition().y);

        if (distance(pos, center) < MAX_RADIUS)
        {
            m_Checked = !m_Checked;
            return true;
        }
    }

    return false;
}

void RadioButton::render(Mat4x4 _transform) const
{
    Shader& shader = ShaderManager::getInstance().getShader("GUI");

    shader.bind();
    shader.passUniform("View", _transform * getTransform());

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXES - (m_Checked ? 0 : POINTS_IN_CIRCLE * 3));
    glBindVertexArray(0);

    shader.unbind();
}

void RadioButton::unset(void)
{
    m_Checked = false;
}

void RadioButton::initialisePositions(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    std::vector<float> data;

    float radius = MAX_RADIUS;
    const float delta = 360.0f / POINTS_IN_CIRCLE * 3.14159265f / 180.0f;

    for (unsigned int i = 0; i < POINTS_IN_CIRCLE; i += 1)
    {
        data.push_back(radius * std::sin(delta * (0 + i)));
        data.push_back(radius * std::cos(delta * (0 + i)));
        data.push_back(0.0f);

        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);

        data.push_back(radius * std::sin(delta * (1 + i)));
        data.push_back(radius * std::cos(delta * (1 + i)));
        data.push_back(0.0f);
    }
    radius -= 1.0f;
    for (unsigned int i = 0; i < POINTS_IN_CIRCLE; i += 1)
    {
        data.push_back(radius * std::sin(delta * (0 + i)));
        data.push_back(radius * std::cos(delta * (0 + i)));
        data.push_back(0.1f);

        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.1f);

        data.push_back(radius * std::sin(delta * (1 + i)));
        data.push_back(radius * std::cos(delta * (1 + i)));
        data.push_back(0.1f);
    }
    radius = MAX_RADIUS / 2.0f;
    for (unsigned int i = 0; i < POINTS_IN_CIRCLE; i += 1)
    {
        data.push_back(radius * std::sin(delta * (0 + i)));
        data.push_back(radius * std::cos(delta * (0 + i)));
        data.push_back(0.3f);

        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.3f);

        data.push_back(radius * std::sin(delta * (1 + i)));
        data.push_back(radius * std::cos(delta * (1 + i)));
        data.push_back(0.3f);
    }
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}
void RadioButton::initialiseColours(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    std::vector<float> data;

    for (unsigned int i = 0; i < POINTS_IN_CIRCLE; i += 1)
    {
        data.push_back(0.0f);data.push_back(0.0f);data.push_back(0.0f);data.push_back(1.0f);
        data.push_back(0.0f);data.push_back(0.0f);data.push_back(0.0f);data.push_back(1.0f);
        data.push_back(0.0f);data.push_back(0.0f);data.push_back(0.0f);data.push_back(1.0f);
    }
    for (unsigned int i = 0; i < POINTS_IN_CIRCLE; i += 1)
    {
        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);
        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);
        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);
    }
    for (unsigned int i = 0; i < POINTS_IN_CIRCLE; i += 1)
    {
        data.push_back(0.0f);data.push_back(0.0f);data.push_back(0.0f);data.push_back(1.0f);
        data.push_back(0.0f);data.push_back(0.0f);data.push_back(0.0f);data.push_back(1.0f);
        data.push_back(0.0f);data.push_back(0.0f);data.push_back(0.0f);data.push_back(1.0f);
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}

} //~ namespace zeno