#include <zeno/GUI/CheckBox.hpp>

#include <zeno/Graphics.hpp>
#include <zeno/GUI/GUIEvent.hpp>

#include <iostream>

#include <GL/glew.h>

#define NUM_VERTEXES 18

#define TOTAL_SIZE zeno::Vector2f(16.0f, 16.0f)
#define THICKNESS 1.0f
#define INNER_SIZE zeno::Vector2f(10.0f, 10.0f)

namespace zeno {

CheckBox::CheckBox(const std::string& _id, GuiBase *_parent) :
GuiBase(_id, _parent),
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

CheckBox::~CheckBox(void)
{
    glDeleteBuffers(1, &m_PositionVBO);
    glDeleteBuffers(1, &m_ColourVBO);

    glDeleteVertexArrays(1, &m_VAO);
}


CheckBox *CheckBox::createElement(const std::string& _id, GuiBase *_parent)
{
    return new CheckBox(_id, _parent);
}


bool CheckBox::processEvent(const GUIEvent& _event)
{
    if (_event.type == GUIEvent::EventType::LeftClick)
    {
        Vector2f pos(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y));

        FloatRect bounds = FloatRect(Vector2f(getPosition().x, getPosition().y), Vector2f(TOTAL_SIZE));

        if (bounds.contains(pos))
        {
            m_Checked = !m_Checked;

            return true;
        }
    }

    return false;
}

void CheckBox::render(Mat4x4 _transform) const
{
    Shader& shader = ShaderManager::getInstance().getShader("GUI");

    Mat4x4 trans = _transform * getTransform();

    shader.bind();
    shader.passUniform("View", trans);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 12 + (m_Checked ? 6 : 0));
    glBindVertexArray(0);

    shader.unbind();
}

void CheckBox::initialisePositions(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    Vector2f innerOffset((TOTAL_SIZE.x - INNER_SIZE.x) / 2.0f, (TOTAL_SIZE.y - INNER_SIZE.y) / 2.0f);

    std::vector<float> data = {
            0.0f,                           0.0f,                           0.0f,
            TOTAL_SIZE.x,                   0.0f,                           0.0f,
            TOTAL_SIZE.x,                   TOTAL_SIZE.y,                   0.0f,

            0.0f,                           0.0f,                           0.0f,
            TOTAL_SIZE.x,                   TOTAL_SIZE.y,                   0.0f,
            0.0f,                           TOTAL_SIZE.y,                   0.0f,

            THICKNESS,                      THICKNESS,                      0.1f,
            TOTAL_SIZE.x - THICKNESS,       THICKNESS,                      0.1f,
            TOTAL_SIZE.x - THICKNESS,       TOTAL_SIZE.y - THICKNESS,       0.1f,

            THICKNESS,                      THICKNESS,                      0.1f,
            TOTAL_SIZE.x - THICKNESS,       TOTAL_SIZE.y - THICKNESS,       0.1f,
            THICKNESS,                      TOTAL_SIZE.y - THICKNESS,       0.1f,

            innerOffset.x,                  innerOffset.y,                  0.2f,
            TOTAL_SIZE.x - innerOffset.x,   innerOffset.y,                  0.2f,
            TOTAL_SIZE.x - innerOffset.x,   TOTAL_SIZE.y - innerOffset.y,   0.2f,

            innerOffset.x,                  innerOffset.y,                  0.2f,
            TOTAL_SIZE.x - innerOffset.x,   TOTAL_SIZE.y - innerOffset.y,   0.2f,
            innerOffset.x,                  TOTAL_SIZE.y - innerOffset.y,   0.2f,
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}
void CheckBox::initialiseColours(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    std::vector<float> data = {
            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,

            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,

            1.0f,       1.0f,       1.0f,       1.0f,
            1.0f,       1.0f,       1.0f,       1.0f,
            1.0f,       1.0f,       1.0f,       1.0f,

            1.0f,       1.0f,       1.0f,       1.0f,
            1.0f,       1.0f,       1.0f,       1.0f,
            1.0f,       1.0f,       1.0f,       1.0f,

            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,

            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}

bool CheckBox::isChecked(void) const
{
    return m_Checked;
}

} //~ namespace zeno