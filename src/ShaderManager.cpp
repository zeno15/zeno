#include "ShaderManager.hpp"

#include <iostream>

#define DEFAULT_SHADER_NAME "Zenos_Default_Shader"

namespace {

	const std::string vertexSource = std::string(	"#version 430\n" \
													"\n" \
													"layout(location = 0) in vec3 in_Position;\n" \
													"layout(location = 1) in vec4 in_Colour;\n" \
													"layout(location = 2) in vec2 in_TexUV;\n" \
													"\n" \
													"\n" \
													"varying vec4 fragColour;\n" \
													"\n" \
													"uniform mat4 View = mat4(1.0f);\n" \
													"\n" \
													"void main(void) \n" \
													"{\n" \
													"	gl_Position = View * vec4(in_Position, 1.0f);\n" \
													"   fragColour  = in_Colour;\n" \
													"	gl_TexCoord[0].xy = in_TexUV;\n" \
													"}\n");


	const std::string fragmentSource = std::string(	"#version 430\n" \
													"\n" \
													"varying vec4 fragColour;\n" \
													"\n" \
													"uniform sampler2D tex;\n" \
													"\n" \
													"void main(void)\n" \
													"{\n" \
													"	gl_FragColor = texture(tex, gl_TexCoord[0].xy) * fragColour;\n" \
													"}\n");

} //~ namespace anonymous

namespace zeno {

ShaderManager::ShaderManager(void)
{
	addShaderFromSource(DEFAULT_SHADER_NAME, vertexSource, fragmentSource);
	getShader(DEFAULT_SHADER_NAME).getLocationOfUniform("View");
}
ShaderManager::~ShaderManager(void)
{
}
	
	
ShaderManager& ShaderManager::getInstance(void)
{
	static ShaderManager manager;
	
	return manager;
}

bool ShaderManager::addShader(const std::string& _name, const std::string& _vertexPath, const std::string& _fragmentPath)
{
	for(unsigned int i = 0; i < m_Shaders.size(); i += 1)
	{
		if (m_Shaders.at(i).first == _name)
		{
			return true;
		}
	}
	
	m_Shaders.push_back(std::pair<std::string, Shader>(_name, Shader()));
	
	m_Shaders.back().second.loadVertexShader(_vertexPath);
	m_Shaders.back().second.loadFragmentShader(_fragmentPath);
	
	if (!m_Shaders.back().second.compileShader())
	{
		std::cout << m_Shaders.back().second.getCompileError() << std::endl;
		
		m_Shaders.erase(m_Shaders.end());
		
		return false;
	}
	
	return true;
}
bool ShaderManager::addShaderFromSource(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource)
{
	for (unsigned int i = 0; i < m_Shaders.size(); i += 1)
	{
		if (m_Shaders.at(i).first == _name)
		{
			return true;
		}
	}

	m_Shaders.push_back(std::pair<std::string, Shader>(_name, Shader()));

	m_Shaders.back().second.loadShadersFromStrings(_vertexSource, _fragmentSource);

	if (!m_Shaders.back().second.compileShader())
	{
		std::cout << m_Shaders.back().second.getCompileError() << std::endl;

		m_Shaders.erase(m_Shaders.begin() + m_Shaders.size() - 1);

		return false;
	}

	return true;
}

Shader& ShaderManager::getShader(const std::string& _name)
{
	for(unsigned int i = 0; i < m_Shaders.size(); i += 1)
	{
		if (m_Shaders.at(i).first == _name)
		{
			return m_Shaders.at(i).second;
		}
	}
	//~ Shader not found
	return getShader(DEFAULT_SHADER_NAME);
}

} //~ namespace zeno