#ifndef INCLUDED_WINDOW_HPP
#define INCLUDED_WINDOW_HPP

#include <cstdint>

#include <WindowImplementation.hpp>
#include <WindowStyle.hpp>

#include <Vector2.hpp>

namespace zeno {

//~ Need context settings to set antialiasing/opengl version



////////////////////////////////////////////////////////////
//
//	
//
////////////////////////////////////////////////////////////
struct VideoMode
{
	unsigned int bitsPerPixel;
	unsigned int width;
	unsigned int height;
};


////////////////////////////////////////////////////////////
//
//	Base class for all platform specific windows to
//	inherate from.
//
////////////////////////////////////////////////////////////
class Window
{
public:
	////////////////////////////////////////////////////////////
	//
	//	
	//
	////////////////////////////////////////////////////////////
	Window(void);

	Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

	void create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style = WindowStyle::Default);

	void close(void);

	bool isOpen(void) const;

	//~ getContextSettings(void)

	//~ bool pollEvent(Event...)

	Vector2i getPosition(void) const;

	void setPosition(const Vector2i& _position);

	Vector2u getSize(void) const;

	void setSize(const Vector2u& _size);

	void display(void);

protected:

};

} //~ namespace zeno

#endif //~ INCLUDED_WINDOW_HPP