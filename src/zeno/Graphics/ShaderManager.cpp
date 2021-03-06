#include <zeno/Graphics/ShaderManager.hpp>

#include <iostream>
#include <stdexcept>

#define DEFAULT_SHADER_NAME		"Zenos_Default_Shader"
#define DEFAULT_TEX_SHADER_NAME	"Zenos_Default_Tex_Shader"
#define TEXT_SHADER_NAME		"Zenos_Text_Shader"

//~ Default shaders that are needed for vertex arrays and text rendering
namespace {

    const std::string vertexTexSource = std::string(	"#version 430\n" \
													"\n" \
													"layout (location = 0) in vec3 in_Position;\n" \
													"layout (location = 1) in vec4 in_Colour;\n" \
													"layout (location = 2) in vec2 in_TexUV;\n" \
													"\n" \
													"out vec4 fragColour;\n" \
													"out vec2 texCoord;\n" \
													"\n" \
													"uniform mat4 View = mat4(1.0f);\n" \
													"\n" \
													"void main(void) \n" \
													"{\n" \
													"	gl_Position = View * vec4(in_Position, 1.0f);\n" \
													"   fragColour  = in_Colour;\n" \
													"	texCoord = in_TexUV;\n" \
													"}\n");


    const std::string fragmentTexSource = std::string(	"#version 430\n" \
													"\n" \
													"in vec4 fragColour;\n" \
													"in vec2 texCoord;\n" \
													"\n" \
													"uniform sampler2D tex;\n" \
													"out vec4 col;\n" \
													"void main(void)\n" \
													"{\n" \
													"	col = texture(tex, texCoord) * fragColour;\n" \
													"}\n");

    const std::string vertexSource = std::string(	"#version 330\n" \
													"\n" \
													"layout (location = 0) in vec3 in_Position;\n" \
													"layout (location = 1) in vec4 in_Colour;\n" \
													"\n" \
													"out vec4 fragColour;\n" \
													"\n" \
													"uniform mat4 View = mat4(1.0f);\n" \
													"\n" \
													"void main(void) \n" \
													"{\n" \
													"	gl_Position = View * vec4(in_Position, 1.0f);\n" \
													"   fragColour  = in_Colour;\n" \
													"}\n");


    const std::string fragmentSource = std::string(	"#version 330\n" \
													"\n" \
													"in vec4 fragColour;\n" \
													"out vec4 fragOutput;\n" \
													"\n" \
													"void main(void)\n" \
													"{\n" \
													"	fragOutput = fragColour;\n" \
													"}\n");

    const std::string vertexTextSource = std::string(	"#version 330\n"\
                                                        "\n"\
                                                        "uniform vec2 texSize = vec2(1.0f, 1.0f);\n"\
                                                        "uniform vec4 colour;\n"\
													    "out vec2 texCoord;\n" \
                                                        "uniform mat4 view = mat4(1.0f);\n"\
                                                        "\n"\
                                                        "layout(location = 0) in vec4 in_Position;\n"\
                                                        "\n"\
                                                        "void main()\n"\
                                                        "{\n"\
                                                        "    gl_Position = view * vec4(in_Position.xy, 0.0f, 1.0f);\n"\
                                                        "\n"\
                                                        "    texCoord.x = in_Position.z / texSize.x;\n"\
                                                        "    texCoord.y = (texSize.y - in_Position.w) / texSize.y;\n"\
                                                        "}\n");


	const std::string fragmentTextSource = std::string(	"#version 330\n" \
														"\n" \
														"uniform vec4 colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n" \
													    "in vec2 texCoord;\n" \
														"\n" \
														"uniform sampler2D tex;\n" \
													    "out vec4 fragOutput;\n" \
														"\n" \
														"void main(void)\n" \
														"{\n" \
														"	fragOutput = vec4(colour.xyz, texture(tex, texCoord).r * colour.w);\n" \
														"}\n");	



} //~ namespace anonymous

namespace zeno {

ShaderManager::ShaderManager(void)
{
    addShaderFromSource(DEFAULT_SHADER_NAME, vertexSource, fragmentSource);
    getShader(DEFAULT_SHADER_NAME).getLocationOfUniform("View");

    addShaderFromSource(DEFAULT_TEX_SHADER_NAME, vertexTexSource, fragmentTexSource);
    getShader(DEFAULT_TEX_SHADER_NAME).getLocationOfUniform("View");

	addShaderFromSource(TEXT_SHADER_NAME, vertexTextSource, fragmentTextSource);
	getShader(TEXT_SHADER_NAME).getLocationOfUniform("view");
    getShader(TEXT_SHADER_NAME).getLocationOfUniform("colour");
	getShader(TEXT_SHADER_NAME).getLocationOfUniform("texSize");
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
		
		m_Shaders.erase(m_Shaders.begin() + m_Shaders.size() - 1);
		
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
bool ShaderManager::addVGFShader(const std::string& _name, const std::string& _vertexPath, const std::string& _geometryPath, const std::string& _fragmentPath)
{
	for(unsigned int i = 0; i < m_Shaders.size(); i += 1)
	{
		if (m_Shaders.at(i).first == _name)
		{
			return true;
		}
	}
	
	m_Shaders.push_back(std::pair<std::string, Shader>(_name, Shader()));
	
	
	m_Shaders.back().second.loadVGFShaders(_vertexPath, _geometryPath, _fragmentPath);

	if (!m_Shaders.back().second.compileShader())
	{
		std::cout << "Shader failed to load: " << std::endl;
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

    throw std::runtime_error(std::string("Shader \"" + _name + "\" not present in ShaderManager."));
}

} //~ namespace zeno
