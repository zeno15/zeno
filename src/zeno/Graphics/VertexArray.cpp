#include <zeno/Graphics/VertexArray.hpp>

#include <zeno/Graphics/RenderData.hpp>
#include <zeno/Graphics/Texture.hpp>
#include <zeno/Graphics/ShaderManager.hpp>

#include <GL/glew.h>

#include <iostream>

namespace zeno {

VertexArray::VertexArray(void) :
m_VAO(0)
{
}


void VertexArray::appendVertex(const Vertex& _vertex)
{
	m_Verticies.push_back(_vertex);
}

std::size_t VertexArray::getCount(void) const
{
	return m_Verticies.size();
}

Vertex& VertexArray::operator [](std::size_t _index)
{
	return m_Verticies[_index];
}

const Vertex& VertexArray::operator [](std::size_t _index) const
{
	return m_Verticies[_index];
}


void VertexArray::create(void)
{
	float *data = reinterpret_cast<float *>(m_Verticies.data());

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * getCount(), data, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
}

void VertexArray::render(const RenderData& _data) const
{
	Shader& shader = ShaderManager::getInstance().getShader("Zenos_Default_Shader");
	shader.bind();
	if (_data.texture != nullptr)
	{
		_data.texture->bind();
	}



	shader.passUniform("View", _data.transform);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, getCount());
	glBindVertexArray(0);

	Shader::unbind();
	Texture::unbind();
}

} //~ namespace zeno