#include <GuiDesktop.hpp>

#include <Event.hpp>
#include <Time.hpp>
#include <GuiBase.hpp>
#include <ShaderManager.hpp>

#include <iostream>

//~ Anonymous namespace containing the gui shader
namespace {

	const std::string GUIVertexSource = std::string(	"#version 430\n" \
														"\n" \
														"layout(location = 0) in vec3 in_Position;\n" \
														"\n" \
														"uniform mat4 View = mat4(1.0f);\n" \
														"\n" \
														"void main(void) \n" \
														"{\n" \
														"	gl_Position = View * vec4(in_Position, 1.0f);\n" \
														"}\n");


	const std::string GUIFragmentSource = std::string(	"#version 430\n" \
														"\n" \
														"void main(void)\n" \
														"{\n" \
														"	gl_FragColor = vec4(1.0f, 0.0f, 0.5f, 1.0f);\n" \
														"}\n");




} //~ anonymous namespace

namespace zeno {

GuiDesktop::GuiDesktop(void)
{
	ShaderManager::getInstance().addShaderFromSource("GUI", GUIVertexSource, GUIFragmentSource);
	Shader& guiShader = ShaderManager::getInstance().getShader("GUI");

	if (!guiShader.getLocationOfUniform("View"))
	{
		std::cout << "Failed to get location of uniform: View" << std::endl;
	}
}
GuiDesktop::~GuiDesktop(void)
{

}


void GuiDesktop::processEvent(const Event& _event) const
{
	for (GuiBase *element : m_Children)
	{
		if (element->processEvent(_event))
		{
			return;
		}
	}
}
void GuiDesktop::render(void)
{
	Shader& guiShader = ShaderManager::getInstance().getShader("GUI");

	Mat4x4 ortho = Mat4x4::Orthographic2D(0.0f, static_cast<float>(m_Resolution.x), static_cast<float>(m_Resolution.y), 0.0f);
	

	guiShader.bind();
	guiShader.passUniform("View", ortho);

	for (GuiBase *element : m_Children)
	{
		element->render();
	}
	Shader::unbind();
}

void GuiDesktop::addChild(GuiBase *_child)
{
	m_Children.push_back(_child);
}

void GuiDesktop::setResolution(unsigned int _x, unsigned int _y)
{
	setResolution(Vector2u(_x, _y));
}

void GuiDesktop::setResolution(const Vector2u& _resolution)
{
	m_Resolution = _resolution;
}

} //~ namespace zeno