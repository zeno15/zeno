#include <zeno/GUI/GuiDesktop.hpp>

#include <zeno/System/Event.hpp>
#include <zeno/System/Time.hpp>

#include <iostream>

//~ Anonymous namespace containing the gui shader
namespace {

	const std::string GUIVertexSource = std::string(	"#version 130\n" \
														"\n" \
														"in vec3 in_Position;\n" \
														"in vec4 in_Colour;\n" \
														"\n" \
														"uniform mat4 View = mat4(1.0f);\n" \
														"\n" \
														"varying vec4 col;\n" \
														"\n" \
														"void main(void) \n" \
														"{\n" \
														"	gl_Position = View * vec4(in_Position, 1.0f);\n" \
														"   col = in_Colour;\n" \
														"}\n");


	const std::string GUIFragmentSource = std::string(	"#version 130\n" \
														"\n" \
														"varying vec4 col;\n" \
														"\n" \
														"void main(void)\n" \
														"{\n" \
														"	gl_FragColor = col;\n" \
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
	GUIEvent event;

	if (!translateEvent(_event, event)) return;

    std::vector<GUIEvent> floats;


	for (GuiPane pane : m_Panes)
	{
		if (pane.processEvent(event))
		{
			return;
		}
	}
}
void GuiDesktop::render(void)
{
    Mat4x4 ortho = Mat4x4::Orthographic2D(0.0f, static_cast<float>(m_Resolution.x), static_cast<float>(m_Resolution.y), 0.0f);
	
	for (GuiPane& pane : m_Panes)
	{
		pane.render(ortho);
	}
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

void GuiDesktop::throwEvent(const GUIEvent& _guiEvent)
{
	m_ThrownEvents.push_back(_guiEvent);
}

bool GuiDesktop::translateEvent(const Event& _event, GUIEvent& _guiEvent) const
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

void GuiDesktop::addPane(const std::string& _name)
{
	for (unsigned int i = 0; i < m_Panes.size(); i += 1)
	{
		if (m_Panes.at(i).getId() == _name)
		{
			return;
		}
	}

	m_Panes.push_back(GuiPane(_name));
}

GuiPane& GuiDesktop::getPane(const std::string& _id)
{
	for (unsigned int i = 0; i < m_Panes.size(); i += 1)
	{
		if (m_Panes.at(i).getId() == _id)
		{
			return m_Panes.at(i);
		}
	}

	throw std::runtime_error(std::string("Pane \"" + _id + "\" not present in desktop."));
}

void GuiDesktop::processThrown(void)
{
	for (GUIEvent event : m_ThrownEvents)
	{
		for (GuiPane& pane : m_Panes)
		{
			if (pane.processEvent(event))
			{
				continue;
			}
		}
	}

	m_ThrownEvents.clear();
}

bool GuiDesktop::loadGUIFont(const std::string& _filename, unsigned int _fontSize /*= 32*/)
{
	return m_GUIFont.loadFromFile(_filename, _fontSize);
}

Font *GuiDesktop::getGUIFont(void)
{
	return &m_GUIFont;
}

void GuiDesktop::addToPane(const std::string& _pane, GuiBase *_child)
{
	getPane(_pane).addChild(_child);
}

} //~ namespace zeno
