#include <zeno/GUI/Desktop.hpp>

#include <zeno/System/Event.hpp>
#include <zeno/System/Time.hpp>

#include <GL/glew.h>

#include <iostream>

//~ Anonymous namespace containing the gui shader
namespace {

	const std::string GUIVertexSource = std::string(	"#version 330\n" \
														"\n" \
														"layout (location = 0) in vec3 in_Position;\n" \
														"layout (location = 1) in vec4 in_Colour;\n" \
														"\n" \
														"uniform mat4 View = mat4(1.0f);\n" \
														"\n" \
														"out vec4 col;\n" \
														"\n" \
														"void main(void) \n" \
														"{\n" \
														"	gl_Position = View * vec4(in_Position, 1.0f);\n" \
														"   col = in_Colour;\n" \
														"}\n");


	const std::string GUIFragmentSource = std::string(	"#version 330\n" \
														"\n" \
														"in vec4 col;\n" \
                                                        "out vec4 fragColour;\n"\
														"\n" \
														"void main(void)\n" \
														"{\n" \
														"	fragColour = col;\n" \
														"}\n");




} //~ anonymous namespace

const std::string zeno::Desktop::m_DesktopPaneId = "ZENO_DEFAULT_DESKTOP_PANE_ID";

namespace zeno {

Desktop::Desktop(void) :
m_DesktopPane(m_DesktopPaneId, nullptr)
{
	ShaderManager::getInstance().addShaderFromSource("GUI", GUIVertexSource, GUIFragmentSource);
	Shader& guiShader = ShaderManager::getInstance().getShader("GUI");

	if (!guiShader.getLocationOfUniform("View"))
	{
		std::cout << "Failed to get location of uniform: View" << std::endl;
	}

    m_DesktopPane.setColour(Colour::Transparent);
}


void Desktop::processEvent(const Event& _event)
{
	GUIEvent event;

	if (!translateEvent(_event, event)) return;

    m_DesktopPane.processEvent(event);
}
void Desktop::render(void)
{
    Mat4x4 ortho = Mat4x4::Orthographic2D(0.0f, static_cast<float>(m_Resolution.x), static_cast<float>(m_Resolution.y), 0.0f);

	m_DesktopPane.render(ortho);
}

void Desktop::setResolution(const Vector2u& _resolution)
{
	m_Resolution = _resolution;

    m_DesktopPane.setBounds(FloatRect(0.0f, 0.0f, _resolution.x, _resolution.y));
}

void Desktop::throwEvent(const GUIEvent& _guiEvent)
{
	m_ThrownEvents.push_back(_guiEvent);
}

bool Desktop::translateEvent(const Event& _event, GUIEvent& _guiEvent) const
{
	switch (_event.type)
	{
	case (Event::EventType::MouseButtonPressed) :
		if (_event.mouseButton.button == Mouse::Button::Left)
		{
			_guiEvent.type = GUIEvent::EventType::LeftClick;
			_guiEvent.mouseButton.button = Mouse::Button::Left;
			_guiEvent.mouseButton.x = _event.mouseButton.x;
			_guiEvent.mouseButton.y = m_Resolution.y - _event.mouseButton.y;
			return true;
		}
		return false;
	case (Event::EventType::MouseButtonReleased) :
		if (_event.mouseButton.button == Mouse::Button::Left)
		{
			_guiEvent.type = GUIEvent::EventType::LeftRelease;
			_guiEvent.mouseButton.button = Mouse::Button::Left;
			_guiEvent.mouseButton.x = _event.mouseButton.x;
			_guiEvent.mouseButton.y = m_Resolution.y - _event.mouseButton.y;
			return true;
		}
		return false;
	case (Event::EventType::MouseMoved):
		_guiEvent.type = GUIEvent::EventType::MouseMove;
		_guiEvent.mouseMove.x = static_cast<unsigned int>(_event.position.x);
		_guiEvent.mouseMove.y = m_Resolution.y - _event.position.y;
		return true;
	case (Event::EventType::TextEntered):
		_guiEvent.type = GUIEvent::EventType::TextEntered;
		_guiEvent.text.character = _event.text.character;
		return true;
	case (Event::EventType::KeyDown):
		_guiEvent.type = GUIEvent::EventType::KeyDown;
		_guiEvent.key.key		= _event.key.key;
		_guiEvent.key.shift		= _event.key.shift;
		_guiEvent.key.alt		= _event.key.alt;
		_guiEvent.key.control	= _event.key.control;
		_guiEvent.key.system	= _event.key.system;
		return true;
	case (Event::EventType::KeyUp):
		_guiEvent.type = GUIEvent::EventType::KeyUp;
		_guiEvent.key.key		= _event.key.key;
		_guiEvent.key.shift		= _event.key.shift;
		_guiEvent.key.alt		= _event.key.alt;
		_guiEvent.key.control	= _event.key.control;
		_guiEvent.key.system	= _event.key.system;
		return true;
	default:
		return false;
	}
}

void Desktop::processThrown(void)
{
    for (unsigned int i = 0; i < m_ThrownEvents.size(); i += 1)
	{
		m_DesktopPane.processEvent(m_ThrownEvents.at(i));
	}

	m_ThrownEvents.clear();
}

bool Desktop::loadGUIFont(const std::string& _filename, unsigned int _fontSize /*= 32*/)
{
	return m_GUIFont.loadFromFile(_filename, _fontSize);
}

Font *Desktop::getGUIFont(void)
{
	return &m_GUIFont;
}


} //~ namespace zeno
