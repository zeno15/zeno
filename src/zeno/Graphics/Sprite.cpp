#include <zeno/Graphics/Sprite.hpp>

#include <zeno/Graphics/Colour.hpp>
#include <zeno/Graphics/RenderData.hpp>
#include <zeno/Graphics/Texture.hpp>

#include <iostream>

namespace zeno {

Sprite::Sprite(void) :
Sprite(nullptr)
{
}

Sprite::Sprite(Texture *_texture, const FloatRect& _bounds /*= FloatRect()*/) :
m_Texture(_texture)
{
	m_VertexArray.appendVertex(Vertex());
	m_VertexArray.appendVertex(Vertex());
	m_VertexArray.appendVertex(Vertex());
	m_VertexArray.appendVertex(Vertex());
	m_VertexArray.appendVertex(Vertex());
	m_VertexArray.appendVertex(Vertex());

	setTextureBounds(_bounds);
}

Sprite::~Sprite(void)
{
}


void Sprite::setTexture(Texture *_texture)
{
	m_Texture = _texture;
	setTextureBounds(FloatRect());
}

void Sprite::setTextureBounds(const FloatRect& _bounds)
{
	if (m_Texture == nullptr)
	{
		return;
	}

	FloatRect bounds = _bounds;
	if (bounds == FloatRect())
	{
		bounds.width	= static_cast<float>(m_Texture->getSize().x);
		bounds.height	= static_cast<float>(m_Texture->getSize().y);
	}

	m_Size = Vector2f(bounds.width, bounds.height);


	float L = bounds.left / static_cast<float>(m_Texture->getSize().x);
	float R = (bounds.left + bounds.width) / static_cast<float>(m_Texture->getSize().x);

	float B = bounds.bot / static_cast<float>(m_Texture->getSize().y);
	float T = (bounds.bot + bounds.height) / static_cast<float>(m_Texture->getSize().y);

	
	//~ Bottom Left
	m_VertexArray[0].position	= Vector3f(0.0f, 0.0f, 0.0f);
	m_VertexArray[0].colour		= Colour::White;
	m_VertexArray[0].texture	= Vector2f(B, L);

	//~ Bottom Right
	m_VertexArray[1].position	= Vector3f(0.0f + m_Size.x, 0.0f, 0.0f);
	m_VertexArray[1].colour		= Colour::White;
	m_VertexArray[1].texture	= Vector2f(T, L);

	//~ Top Right
	m_VertexArray[2].position	= Vector3f(0.0f + m_Size.x, 0.0f + m_Size.y, 0.0f);
	m_VertexArray[2].colour		= Colour::White;
	m_VertexArray[2].texture	= Vector2f(T, R);


	
	//~ Bottom Left
	m_VertexArray[3].position	= Vector3f(0.0f, 0.0f, 0.0f);
	m_VertexArray[3].colour		= Colour::White;
	m_VertexArray[3].texture	= Vector2f(B, L);
	
	//~ Top Right
	m_VertexArray[4].position	= Vector3f(0.0f + m_Size.x, 0.0f + m_Size.y, 0.0f);
	m_VertexArray[4].colour		= Colour::White;
	m_VertexArray[4].texture	= Vector2f(T, R);

	//~ Top Left
	m_VertexArray[5].position	= Vector3f(0.0f, 0.0f + m_Size.y, 0.0f);
	m_VertexArray[5].colour		= Colour::White;
	m_VertexArray[5].texture	= Vector2f(B, R);
	
	m_VertexArray.create();
}

void Sprite::render(RenderData& _data)
{
	if (m_Texture != nullptr)
	{
		_data.texture = m_Texture;
	}
	m_VertexArray.render(_data);
}

} //~ namespace zeno