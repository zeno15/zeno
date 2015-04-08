#include <zeno/GUI/GuiButton.hpp>

#include <zeno/GUI/GUIEvent.hpp>

#include <GL/glew.h>

#include <iostream>

namespace zeno {


GuiButton::GuiButton(void) :
m_Depressed(false)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	static const GLfloat g_vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f,
		100.0f, 0.0f, 0.0f,
		100.0f, 100.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		100.0f, 100.0f, 0.0f,
		0.0f, 100.0f, 0.0f,
	};

	GLuint vertexbuffer;

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		nullptr            // array buffer offset
		);

	bounds = FloatRect(Vector2f(), Vector2f(100.0f, 100.0f));
}

GuiButton::~GuiButton(void)
{

}

bool GuiButton::processEvent(const GUIEvent& _event)
{
	if (_event.type == GUIEvent::EventType::LeftClick)
	{
		if (bounds.contains(Vector2f(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y))))
		{
			//~ Only call the function if it has been set
			if (m_PressFunction) m_PressFunction();
			m_Depressed = true;
			return true;
		}
	}
	if (_event.type == GUIEvent::EventType::LeftRelease)
	{
		if (bounds.contains(Vector2f(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y))))
		{
			if (m_Depressed)
			{
				//~ Only call the function if it has been set
				if (m_ReleaseFunction) m_ReleaseFunction();
				m_Depressed = false;
			}
			return true;
		}

		m_Depressed = false;
	}

	return false;
}

void GuiButton::render(void) const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glBindVertexArray(0);
}

void GuiButton::registerCallbackPress(std::function<void(void)> _function)
{
	m_PressFunction = _function;
}

void GuiButton::registerCallbackRelease(std::function<void(void)> _function)
{
	m_ReleaseFunction = _function;
}

} //~ namespace zeno