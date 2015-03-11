#include "ShaderManager.hpp"

#include <iostream>

namespace zeno {

ShaderManager::ShaderManager(void)
{
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
	return Shader();
}

} //~ namespace zeno