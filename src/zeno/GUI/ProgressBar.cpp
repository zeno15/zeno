#include  <zeno/GUI/ProgressBar.hpp>

#include <zeno/GUI/GUIEvent.hpp>

#include <GL/glew.h>
#include <iostream>

namespace zeno {

ProgressBar::ProgressBar(void)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	static const GLfloat g_vertex_buffer_data[] = {
		100.0f, 100.0f, 0.0f,
		200.0f, 100.0f, 0.0f,
		200.0f, 200.0f, 0.0f,
		100.0f, 100.0f, 0.0f,
		200.0f, 200.0f, 0.0f,
		100.0f, 200.0f, 0.0f,
	};

	

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &progressBarVBO);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, progressBarVBO);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data) * 2, g_vertex_buffer_data, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, progressBarVBO);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		nullptr             // array buffer offset
		);

	resendData(0.0f);
}

ProgressBar::~ProgressBar(void)
{
}


bool ProgressBar::processEvent(const GUIEvent& _event)
{
	if (_event.type == GUIEvent::ProgressUpdate)
	{
		std::cout << "Progress bar updated, " << static_cast<int>(_event.progress.progress * 100.0f) << "%" << std::endl;
		
		resendData(_event.progress.progress);
		return true;
	}
	return false;
}

void ProgressBar::render(void) const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6 * 2); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glBindVertexArray(0);
}

void ProgressBar::resendData(float _percent)
{

	int m_Start = 0;
	int m_End = 100;

	float left = static_cast<float>(m_Start);
	float right = static_cast<float>(m_End) * _percent;

	GLfloat g_vertex_buffer_data[] = {
		200.0f, 200.0f, 0.0f,
		200.0f + _percent * 500.0f, 200.0f, 0.0f,
		200.0f + _percent * 500.0f, 500.0f, 0.0f,

		200.0f, 200.0f, 0.0f,
		200.0f + _percent * 500.0f, 500.0f, 0.0f,
		200.0f, 500.0f, 0.0f,
	};
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, progressBarVBO);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), sizeof(g_vertex_buffer_data), g_vertex_buffer_data);
	/*
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, progressBarVBO);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		nullptr            // array buffer offset
		);*/
}

} //~ namespace zeno