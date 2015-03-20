#ifndef INCLUDED_RENDER_DATA_HPP
#define INCLUDED_RENDER_DATA_HPP

#include <Mat4x4.hpp>
#include <Texture.hpp>

#include <string>

namespace zeno {

////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////
struct RenderData
{
	RenderData(void) :
		texture(nullptr),
		transform(1.0f),
		shader("Zenos_Default_Shader")
	{
	}

	Mat4x4		transform;

	Texture *	texture;

	std::string	shader;
};

} //~ namespace zeno

#endif //~ INCLUDED_RENDER_DATA_HPP