#ifndef INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP
#define INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP

#include <zeno/Graphics/Vertex.hpp>

#include <vector>

namespace zeno {

struct RenderData;
class Texture;

////////////////////////////////////////////////////////////
//
//	Class representing simple way to draw shapes,
//	can use textures and colours
//
////////////////////////////////////////////////////////////
class VertexArray
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor
	//
	////////////////////////////////////////////////////////////
	VertexArray(void);


	////////////////////////////////////////////////////////////
	//
	//	Appends a vertex to the array
	//
	////////////////////////////////////////////////////////////
	void appendVertex(const Vertex& _vertex);

	////////////////////////////////////////////////////////////
	//
	//	Returns the size of the array
	//
	////////////////////////////////////////////////////////////
	std::size_t getCount(void) const;

	////////////////////////////////////////////////////////////
	//
	//	Returns a modifiable reference to the vertex at the 
	//	given array index
	//
	////////////////////////////////////////////////////////////
	Vertex& operator [](std::size_t _index);

	////////////////////////////////////////////////////////////
	//
	//	Returns a non-modifiable reference to the vertex at the
	//	given array index
	//
	////////////////////////////////////////////////////////////
	const Vertex& operator [](std::size_t _index) const;

	////////////////////////////////////////////////////////////
	//
	//	Creates the vertex array object bound to this vertex
	//	array, passes data to gpu
	//
	////////////////////////////////////////////////////////////
	void create(void);

	////////////////////////////////////////////////////////////
	//
	//	Renders the vertex array
	//
	////////////////////////////////////////////////////////////
	void render(const RenderData& _data) const;

private:
	////////////////////////////////////////////////////////////
	//
	//	Vector of vertexes
	//
	////////////////////////////////////////////////////////////
	std::vector<Vertex>			m_Verticies;

	////////////////////////////////////////////////////////////
	//
	//	Vertex Array Object for OpenGL drawing
	//
	////////////////////////////////////////////////////////////
	unsigned int				m_VAO;

};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP