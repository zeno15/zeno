#ifndef INCLUDED_ZENO_GRAPHICS_RENDER_DATA_HPP
#define INCLUDED_ZENO_GRAPHICS_RENDER_DATA_HPP

#include <zeno/System/Mat4x4.hpp>
#include <zeno/Graphics/Texture.hpp>

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

#endif //~ INCLUDED_ZENO_GRAPHICS_RENDER_DATA_HPP