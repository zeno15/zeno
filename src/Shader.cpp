#include "Shader.hpp"

#include <iostream>
#include <fstream>

#include <GL/glew.h>


namespace zeno {

Shader::Shader(void) :
m_ProgramId(0)
{
}
Shader::Shader(const std::string& _vertexPath, const std::string& _fragmentPath) :
m_ProgramId(0)
{
	loadVertexShader(_vertexPath);
	loadFragmentShader(_fragmentPath);
}
Shader::~Shader(void)
{
}


void Shader::loadVertexShader(const std::string& _vertexPath)
{
	std::ifstream input;
	input.open(_vertexPath);

	m_VertexShaderSource.clear();
	
	if (!input.good())
	{
 		return;
	}

	input.seekg(0, std::ios::end);   
	m_VertexShaderSource.reserve(static_cast<unsigned int>(input.tellg()));
	input.seekg(0, std::ios::beg);

	m_VertexShaderSource.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

	return;
}
void Shader::loadFragmentShader(const std::string& _fragmentPath)
{
	std::ifstream input;
	input.open(_fragmentPath);
	
	if (!input.good())
	{
 		return;
	}

	input.seekg(0, std::ios::end);   
	m_FragmentShaderSource.reserve(static_cast<unsigned int>(input.tellg()));
	input.seekg(0, std::ios::beg);

	m_FragmentShaderSource.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

	return;
}
void Shader::loadShaders(const std::string& _vertexPath, const std::string& _fragmentPath)
{
	loadVertexShader(_vertexPath);
	loadFragmentShader(_fragmentPath);
}
void Shader::loadShadersFromStrings(const std::string& _vertexSource, const std::string& _fragmentSource)
{
	m_VertexShaderSource = _vertexSource;
	m_FragmentShaderSource = _fragmentSource;
}

bool Shader::compileShader(void)
{
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	const char *vertSrc = m_VertexShaderSource.c_str();
	const char *fragSrc = m_FragmentShaderSource.c_str();
	
	GLint result = GL_FALSE;
    int logLength;
	
	// Compile vertex shader
    glShaderSource(vertShader, 1, &vertSrc, NULL);
    glCompileShader(vertShader);

    // Checking vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
	
	if (result != 1)
	{
		m_Error = std::string(&vertShaderError[0]);
		return false;
	}
	
	// Compile fragment shader
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);

    // Checking fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
	
	if (result != 1)
	{
		m_Error = std::string(&fragShaderError[0]);
		return false;
	}
	
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    
	if (result != 1)
	{
		m_Error = std::string(&programError[0]);
		return false;
	}

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
	
	m_ProgramId = program;
	
	return true;
}
std::string Shader::getCompileError(void)
{
	return m_Error;
}

void Shader::bind(void)
{
	glUseProgram(m_ProgramId);
}
void Shader::unbind(void)
{
	glUseProgram(0);
}

unsigned int Shader::getId(void)
{
	return m_ProgramId;
}

bool Shader::getLocationOfUniform(const std::string& _uniform)
{
	bind();
	
	GLint loc = glGetUniformLocation(m_ProgramId, _uniform.c_str());
	
	if (loc == -1)
	{
		std::cout << "glGetUniformLocation failed" << std::endl;
		return false;
	}
	
	
	for (unsigned int i = 0; i < m_UniformLocations.size(); i += 1)
	{
		if (m_UniformLocations.at(i).first == _uniform)
		{
			return true;
		}
	}
	
	m_UniformLocations.push_back(std::pair<std::string, int>(_uniform, loc));
	
	unbind();
	
	return true;
}

void Shader::passUniform(const std::string& _name, const Vector3<float>& _uniform)
{
	for (unsigned int i = 0; i < m_UniformLocations.size(); i += 1)
	{
		if (m_UniformLocations.at(i).first == _name)
		{
			glUniform3f(m_UniformLocations.at(i).second, _uniform.x, _uniform.y, _uniform.z);
			return;
		}
	}
}
void Shader::passUniform(const std::string& _name, const Mat4x4& _uniform)
{
	for (unsigned int i = 0; i < m_UniformLocations.size(); i += 1)
	{
		if (m_UniformLocations.at(i).first == _name)
		{
			glUniformMatrix4fv(m_UniformLocations.at(i).second, 1, false, _uniform.pointer());
			return;
		}
	}
}

} //~ namespace zeno