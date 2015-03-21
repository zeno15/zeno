#include <zeno/Graphics/Vertex.hpp>

namespace zeno {

Vertex::Vertex(void) :
position(Vector3f()),
colour(Colour::White),
texture(Vector2f())
{
}

Vertex::Vertex(const Vector3f& _position) :
position(_position),
colour(Colour::White),
texture(Vector2f())
{
}

Vertex::Vertex(const Vector3f& _position, const Colour& _colour) :
position(_position),
colour(_colour),
texture(Vector2f())
{
}

Vertex::Vertex(const Vector3f& _position, const Vector2f& _texture) :
position(_position),
colour(Colour::White),
texture(_texture)
{
}

Vertex::Vertex(const Vector3f& _position, const Colour& _colour, const Vector2f& _texture) :
position(_position),
colour(_colour),
texture(_texture)
{
}

} //~ namespace zeno