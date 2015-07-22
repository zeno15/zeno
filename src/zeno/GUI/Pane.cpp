#include <zeno/GUI/Pane.hpp>

#include <iostream>
#include <GL/glew.h>

#define NUM_VERTEXES 6

namespace zeno {

Pane::Pane(const std::string& _id, GuiBase *_parent) :
GuiBase(_id, _parent),
m_Bounded(false),
m_VAO(0)
{
    m_IsPane = true;
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glGenBuffers(1, &m_PositionVBO);
    glGenBuffers(1, &m_ColourVBO);

    //~ Positions
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NUM_VERTEXES * 3, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //~ Colours
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NUM_VERTEXES * 4, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    setColour(Colour::Cyan);
}

Pane::~Pane(void)
{
    glDeleteVertexArrays(1, &m_VAO);
}


bool Pane::processEvent(const GUIEvent& _event)
{
	if (!m_Active)
    {
        return false;
    }

    //~ Need to ensure that mouse is within bounds if pane is bounded

	for (GuiBase *element : m_Children)
	{
        //~ Don't update inactive elements
        if (!element->getActive()) continue;

		if (element->processEvent(_event))
		{
			return true;
		}
	}

	return false;
}

void Pane::render(Mat4x4 _transform) const
{
    if (!m_Visible)
    {
        return;
    }

    glEnable(GL_SCISSOR_TEST);

    glScissor(static_cast<int>(m_Bounds.left),
              static_cast<int>(m_Bounds.bot),
              static_cast<int>(m_Bounds.width),
              static_cast<int>(m_Bounds.height));

    Shader& shader = ShaderManager::getInstance().getShader("GUI");

    Mat4x4 trans = _transform * getTransform();

    shader.bind();
    shader.passUniform("View", trans);

    if (m_Bounded)
    {

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXES);
        glBindVertexArray(0);

        _transform *= Mat4x4::createTranslation(Vector3f(0.0f, 0.0f, 0.1f));
    }

    shader.unbind();

	for (GuiBase *element : m_Children)
	{
		element->render(_transform);
	}

    glDisable(GL_SCISSOR_TEST);
}
    Pane *Pane::createElement(const std::string& _id, GuiBase *_parent)
{
    return new Pane(_id, _parent);
}

void Pane::setColour(const Colour& _col)
{
    std::vector<float> colData = {
        _col.r, _col.g, _col.b, _col.a,
        _col.r, _col.g, _col.b, _col.a,
        _col.r, _col.g, _col.b, _col.a,

        _col.r, _col.g, _col.b, _col.a,
        _col.r, _col.g, _col.b, _col.a,
        _col.r, _col.g, _col.b, _col.a
    };

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * colData.size(), colData.data());
}

void Pane::setBounds(const FloatRect& _bounds)
{
    if (_bounds == m_Bounds)
    {
        return;
    }

    m_Bounds = _bounds;
    m_Bounded = true;

    std::vector<float> posData = {
        m_Bounds.left,                      m_Bounds.bot,                       0.0f,
        m_Bounds.left + m_Bounds.width,     m_Bounds.bot,                       0.0f,
        m_Bounds.left + m_Bounds.width,     m_Bounds.bot + m_Bounds.height,     0.0f,

        m_Bounds.left,                      m_Bounds.bot,                       0.0f,
        m_Bounds.left + m_Bounds.width,     m_Bounds.bot + m_Bounds.height,     0.0f,
        m_Bounds.left,                      m_Bounds.bot + m_Bounds.height,     0.0f
    };

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * posData.size(), posData.data());
}

void Pane::removeBounds(void)
{
    m_Bounds = FloatRect();
    m_Bounded = false;
}

} //~ namespace zeno