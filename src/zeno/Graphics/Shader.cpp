#include <zeno/Graphics/Shader.hpp>

#include <GL/glew.h>

#include <iostream>
#include <fstream>


namespace zeno {

Shader::Shader(void) :
m_UsingGeometry(false),
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
void Shader::loadGeometryShader(const std::string& _geometryPath)
{
	m_UsingGeometry = true;

	std::ifstream input;
	input.open(_geometryPath);
	
	if (!input.good())
	{
 		return;
	}

	input.seekg(0, std::ios::end);   
	m_GeometryShaderSource.reserve(static_cast<unsigned int>(input.tellg()));
	input.seekg(0, std::ios::beg);

	m_GeometryShaderSource.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
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

void Shader::loadVGFShaders(const std::string& _vertexPath, const std::string& _geometryPath, const std::string& _fragmentPath)
{
	loadVertexShader(_vertexPath);
	loadGeometryShader(_geometryPath);
	loadFragmentShader(_fragmentPath);
}

bool Shader::compileShader(void)
{
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint geomShader = 0;
	if (m_UsingGeometry)
	{
		geomShader = glCreateShader(GL_GEOMETRY_SHADER);
	}
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	char *vertSrc = &m_VertexShaderSource[0];
	char *geomSrc = nullptr;
	if (m_UsingGeometry)
	{
		geomSrc = &m_GeometryShaderSource[0];
	}
	char *fragSrc = &m_FragmentShaderSource[0];
	
	GLint result = GL_FALSE;
    int logLength;
	
	//~ -----------------------VERTEX
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

	//~ -----------------------GEOMETRY
	if (m_UsingGeometry)
	{
		// Compile geometry shader
		glShaderSource(geomShader, 1, &geomSrc, NULL);
		glCompileShader(geomShader);

		// Checking geometry shader
		glGetShaderiv(geomShader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(geomShader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> geomShaderError((logLength > 1) ? logLength : 1);
		glGetShaderInfoLog(geomShader, logLength, NULL, &geomShaderError[0]);

		if (result != 1)
		{
			m_Error = std::string(&geomShaderError[0]);
			return false;
		}
	}	

	//~ -----------------------FRAGMENT
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



	//~ Creating shader program
	
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
	if (m_UsingGeometry)
	{
		glAttachShader(program, geomShader);
	}
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
	if (m_UsingGeometry)
	{
		glDeleteShader(geomShader);
	}
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

void Shader::passUniform(const std::string& _name, const Vector2<float>& _uniform)
{
	for (unsigned int i = 0; i < m_UniformLocations.size(); i += 1)
	{
		if (m_UniformLocations.at(i).first == _name)
		{
			glUniform2f(m_UniformLocations.at(i).second, _uniform.x, _uniform.y);
			return;
		}
	}
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
void Shader::passUniform(const std::string& _name, const Vector4<float>& _uniform)
{
	for (unsigned int i = 0; i < m_UniformLocations.size(); i += 1)
	{
		if (m_UniformLocations.at(i).first == _name)
		{
			glUniform4f(m_UniformLocations.at(i).second, _uniform.x, _uniform.y, _uniform.z, _uniform.w);
			return;
		}
	}
}

} //~ namespace zeno