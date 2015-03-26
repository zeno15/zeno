#ifndef INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP
#define INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP

#include <zeno/Graphics/RenderData.hpp>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Abstract base class for renderable objects
//
////////////////////////////////////////////////////////////
class Renderable
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Virtual destructor
	//
	////////////////////////////////////////////////////////////
	virtual ~Renderable(void) {};

	////////////////////////////////////////////////////////////
	//
	//	Virtual function for deriving classes to implement
	//
	////////////////////////////////////////////////////////////
	virtual void render(RenderData _data) = 0;
private:

};

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_RENDERABLE_HPP