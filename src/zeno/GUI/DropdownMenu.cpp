#include <zeno/GUI/DropdownMenu.hpp>

#include <zeno/Graphics.hpp>
#include <zeno/GUI/Desktop.hpp>
#include <zeno/GUI/GUIEvent.hpp>
#include <zeno/GUI/Label.hpp>

#include <GL/glew.h>

#include <iostream>

#define NUM_VERTEXES 27
#define TRIANGLE_OFFSET 18
#define BACKGROUND_OFFSET 21
#define CHOICE_BOX_OFFSET 27
#define THICKNESS 1.0f

namespace zeno {

DropdownMenu::DropdownMenu(const std::string& _id, GuiBase *_parent, Desktop& _desktop) :
GuiBase(_id, _parent, _desktop),
m_BoxSize(250.0f, 40.0f),
m_Extended(false),
m_Options(0),
m_CurrentChoice(-1)
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

    createBoxPositions();
    createBoxColours();

    setTrianglePositions();
    setTriangleColours();

    setBackgroundPositions();
    setBackgroundColours();
}

DropdownMenu::~DropdownMenu(void)
{
    glDeleteBuffers(1, &m_PositionVBO);
    glDeleteBuffers(1, &m_ColourVBO);

    glDeleteVertexArrays(1, &m_VAO);
}


DropdownMenu *DropdownMenu::createElement(const std::string& _id, GuiBase *_parent, Desktop& _desktop)
{
    return new DropdownMenu(_id, _parent, _desktop);
}

bool DropdownMenu::processEvent(const GUIEvent& _event)
{
    if (_event.type == GUIEvent::EventType::LeftClick)
    {
        Vector2f pos(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y));

        FloatRect bounds = FloatRect(Vector2f(getPosition().x + m_BoxSize.x, getPosition().y), Vector2f(m_BoxSize.y, m_BoxSize.y));

        if (bounds.contains(pos))
        {
            m_Extended = !m_Extended;

            for (const std::string& choice : m_OptionStrings)
            {
                m_Desktop.getElement<Label>(getId() + choice).setActive(m_Extended);
            }

            setTrianglePositions();

            return true;
        }

        bounds = FloatRect(Vector2f(getPosition().x, getPosition().y - m_BoxSize.y * m_Options), Vector2f(m_BoxSize.x + m_BoxSize.y, m_BoxSize.y * m_Options));

        if (bounds.contains(pos))
        {
            float relativeDepth = getPosition().y - pos.y;

            m_CurrentChoice = static_cast<int>(relativeDepth / m_BoxSize.y);

            m_Desktop.getElement<Label>(std::string(getId() + "SelectedChoice")).setLabel(m_OptionStrings.at(m_CurrentChoice));

            m_Extended = false;

            for (const std::string& choice : m_OptionStrings)
            {
                m_Desktop.getElement<Label>(getId() + choice).setActive(m_Extended);
            }

            return true;
        }
    }

    return false;
}

void DropdownMenu::render(Mat4x4 _transform) const
{
    Shader& shader = ShaderManager::getInstance().getShader("GUI");

    Mat4x4 trans = _transform * getTransform();

    shader.bind();
    shader.passUniform("View", trans);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, BACKGROUND_OFFSET + (m_Extended ? zenoGLEWDefinitions::VERTEXES_IN_QUAD + zenoGLEWDefinitions::VERTEXES_IN_QUAD * m_Options : 0));
    glBindVertexArray(0);

    shader.unbind();


    for (const GuiBase *child : m_Children)
    {
        child->render(_transform * getTransform());
    }
}

void DropdownMenu::addChoice(const std::string& _choice)
{
    m_Options += 1;

    m_OptionStrings.push_back(_choice);

    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (NUM_VERTEXES + zenoGLEWDefinitions::VERTEXES_IN_QUAD * m_Options) * zenoGLEWDefinitions::FLOATS_IN_POSITION, nullptr, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (NUM_VERTEXES + zenoGLEWDefinitions::VERTEXES_IN_QUAD * m_Options) * zenoGLEWDefinitions::FLOATS_IN_COLOUR, nullptr, GL_STATIC_DRAW);

    createBoxPositions();
    createBoxColours();

    setTrianglePositions();
    setTriangleColours();

    setBackgroundPositions();
    setBackgroundColours();

    setOptionBoxPositions();
    setOptionBoxColours();

    m_Desktop.addToElement<Label>(std::string(getId() + _choice), getId());

    m_Desktop.getElement<Label>(std::string(getId() + _choice)).setFont(m_Desktop.getGUIFont());
    m_Desktop.getElement<Label>(std::string(getId() + _choice)).setLabel(_choice);
    m_Desktop.getElement<Label>(std::string(getId() + _choice)).setLabelColour(Colour::Black);
    m_Desktop.getElement<Label>(std::string(getId() + _choice)).setPosition(Vector3f(4.0f, 8.0f - m_BoxSize.y * m_Options, 0.2f));
    m_Desktop.getElement<Label>(std::string(getId() + _choice)).setActive(false);
}

void DropdownMenu::setSize(const zeno::Vector2f& _size)
{
    m_BoxSize = _size;

    createBoxPositions();
    createBoxColours();

    setTrianglePositions();
    setTriangleColours();

    setBackgroundPositions();
    setBackgroundColours();
}

void DropdownMenu::createBoxPositions(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    std::vector<float> data = {
            0.0f,                           0.0f,                           0.0f,
            m_BoxSize.x,                    0.0f,                           0.0f,
            m_BoxSize.x,                    m_BoxSize.y,                    0.0f,

            0.0f,                           0.0f, 0.0f,
            m_BoxSize.x,                    m_BoxSize.y,                    0.0f,
            0.0f,                           m_BoxSize.y,                    0.0f,

            THICKNESS,                      THICKNESS,                      0.1f,
            m_BoxSize.x - THICKNESS,        THICKNESS,                      0.1f,
            m_BoxSize.x - THICKNESS,        m_BoxSize.y - THICKNESS,        0.1f,

            THICKNESS,                      THICKNESS,                      0.1f,
            m_BoxSize.x - THICKNESS,        m_BoxSize.y - THICKNESS,        0.1f,
            THICKNESS,                      m_BoxSize.y - THICKNESS,        0.1f,

            m_BoxSize.x,                    0.0f,                           0.2f,
            m_BoxSize.x + m_BoxSize.y,      0.0f,                           0.2f,
            m_BoxSize.x + m_BoxSize.y,      m_BoxSize.y,                    0.2f,

            m_BoxSize.x,                    0.0f,                           0.2f,
            m_BoxSize.x + m_BoxSize.y,      m_BoxSize.y,                    0.2f,
            m_BoxSize.x,                    m_BoxSize.y,                    0.2f,

    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}
void DropdownMenu::createBoxColours(void)
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

            0.4f,       0.4f,       0.4f,       1.0f,
            0.4f,       0.4f,       0.4f,       1.0f,
            0.4f,       0.4f,       0.4f,       1.0f,

            0.4f,       0.4f,       0.4f,       1.0f,
            0.4f,       0.4f,       0.4f,       1.0f,
            0.4f,       0.4f,       0.4f,       1.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * data.size(), data.data());
}

void DropdownMenu::setTrianglePositions(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);


    std::vector<float> data = {
            m_BoxSize.x + m_BoxSize.y / 4.0f,           m_BoxSize.y / 2.0f + (m_Extended ? - m_BoxSize.y / 4.0f : m_BoxSize.y / 4.0f),    0.3f,
            m_BoxSize.x + m_BoxSize.y * 3.0f / 4.0f,    m_BoxSize.y / 2.0f + (m_Extended ? - m_BoxSize.y / 4.0f : m_BoxSize.y / 4.0f),    0.3f,
            m_BoxSize.x + m_BoxSize.y / 2.0f,           m_BoxSize.y / 2.0f + (m_Extended ? m_BoxSize.y / 4.0f : - m_BoxSize.y / 4.0f),    0.3f
    };


    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * TRIANGLE_OFFSET * zenoGLEWDefinitions::FLOATS_IN_POSITION, sizeof(GLfloat) * data.size(), data.data());
}
void DropdownMenu::setTriangleColours(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    std::vector<float> data = {
            0.3f,       0.3f,       0.2f,       1.0f,
            0.3f,       0.3f,       0.2f,       1.0f,
            0.3f,       0.3f,       0.2f,       1.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * TRIANGLE_OFFSET * zenoGLEWDefinitions::FLOATS_IN_COLOUR, sizeof(GLfloat) * data.size(), data.data());
}

void DropdownMenu::setBackgroundPositions(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    float multiple = static_cast<float>(m_Options == 0 ? 1 : m_Options);

    std::vector<float> data = {
            0.0f,                           0.0f,                               0.0f,
            m_BoxSize.x + m_BoxSize.y,      0.0f,                               0.0f,
            m_BoxSize.x + m_BoxSize.y,      - m_BoxSize.y * multiple + 2.0f,    0.0f,

            0.0f,                           0.0f,                               0.0f,
            m_BoxSize.x + m_BoxSize.y,      - m_BoxSize.y * multiple + 2.0f,    0.0f,
            0.0f,                           - m_BoxSize.y * multiple + 2.0f,    0.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * BACKGROUND_OFFSET * zenoGLEWDefinitions::FLOATS_IN_POSITION, sizeof(GLfloat) * data.size(), data.data());
}
void DropdownMenu::setBackgroundColours(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    std::vector<float> data = {
            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,

            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f,
            0.0f,       0.0f,       0.0f,       1.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * BACKGROUND_OFFSET * zenoGLEWDefinitions::FLOATS_IN_COLOUR, sizeof(GLfloat) * data.size(), data.data());
}
void DropdownMenu::setOptionBoxPositions(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    std::vector<float> data;

    for (int i = 0; i < static_cast<int>(m_Options); i += 1)
    {
        data.push_back(THICKNESS);
        data.push_back(-i * m_BoxSize.y - THICKNESS);
        data.push_back(0.1f);

        data.push_back(m_BoxSize.x + m_BoxSize.y - THICKNESS);
        data.push_back(-i * m_BoxSize.y - THICKNESS);
        data.push_back(0.1f);

        data.push_back(m_BoxSize.x + m_BoxSize.y - THICKNESS);
        data.push_back(-(i + 1) * m_BoxSize.y + THICKNESS);
        data.push_back(0.1f);


        data.push_back(THICKNESS);
        data.push_back(-i * m_BoxSize.y - THICKNESS);
        data.push_back(0.1f);

        data.push_back(m_BoxSize.x + m_BoxSize.y - THICKNESS);
        data.push_back(-(i + 1) * m_BoxSize.y + THICKNESS);
        data.push_back(0.1f);

        data.push_back(THICKNESS);
        data.push_back(-(i + 1) * m_BoxSize.y + THICKNESS);
        data.push_back(0.1f);
    }

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * CHOICE_BOX_OFFSET * zenoGLEWDefinitions::FLOATS_IN_POSITION, sizeof(GLfloat) * data.size(), data.data());
}
void DropdownMenu::setOptionBoxColours(void)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    std::vector<float> data;

    for (unsigned int i = 0; i < m_Options; i += 1)
    {
        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);
        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);
        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);

        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);
        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);
        data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);data.push_back(1.0f);
    }

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * CHOICE_BOX_OFFSET * zenoGLEWDefinitions::FLOATS_IN_COLOUR, sizeof(GLfloat) * data.size(), data.data());
}

void DropdownMenu::initialise(void)
{
    m_Desktop.addToElement<Label>(std::string(getId() + "SelectedChoice"), getId());

    m_Desktop.getElement<Label>(std::string(getId() + "SelectedChoice")).setFont(m_Desktop.getGUIFont());
    m_Desktop.getElement<Label>(std::string(getId() + "SelectedChoice")).setLabel("");
    m_Desktop.getElement<Label>(std::string(getId() + "SelectedChoice")).setLabelColour(Colour::Black);
    m_Desktop.getElement<Label>(std::string(getId() + "SelectedChoice")).setPosition(Vector3f(4.0f, 8.0f , 0.2f));
}

std::string DropdownMenu::getCurrentChoice(void) const
{
    if (m_CurrentChoice == -1)
    {
        return std::string();
    }

    return m_OptionStrings.at(m_CurrentChoice);
}

} //~ namespace zeno