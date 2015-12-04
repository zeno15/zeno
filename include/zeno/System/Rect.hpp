#ifndef INCLUDED_ZENO_SYSTEM_RECT_HPP
#define INCLUDED_ZENO_SYSTEM_RECT_HPP

#include <zeno/System/Vector2.hpp>

#include <algorithm>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief	Template class for 2D rectangle operations
///
////////////////////////////////////////////////////////////
template <typename T>
class Rect
{
public:
	////////////////////////////////////////////////////////////
	///
	///	\brief	Default constructor
	///
	///	Initialises Rect with \a left, \a bot, \a width and 
	///	\a height at 0
	///
	////////////////////////////////////////////////////////////
	Rect(void);
	
	////////////////////////////////////////////////////////////
	///
	///	\brief	Initialises Rect with the four given values
	///
	///	\param	_left		value that left is set to
	///
	///	\param	_bot		value that bot is set to
	///
	///	\param	_width		value that width is set to
	///
	///	\param	_height		value that height is set to
	///
	////////////////////////////////////////////////////////////
	Rect(T _left, T _bot, T _width, T _height);
	
	////////////////////////////////////////////////////////////
	///
	///	\brief	Initialises the Rect with the given position
	///			and size
	///
	///	\param	_position	Vector2 that left and bot are set to
	///
	///	\param	_size		Vector2 that width and height are
	///						set to
	///
	////////////////////////////////////////////////////////////
	Rect(const Vector2<T>& _position, const Vector2<T>& _size);
	
	////////////////////////////////////////////////////////////
	///
	///	\brief	Copy constructor
	///
	///	Initialises the Rect to have the same values as that 
	///	of the parameter
	///
	///	\param	_rect	Rect that is used to initialise this
	///					Rect
	///
	////////////////////////////////////////////////////////////
	template <typename U>
	explicit Rect(const Rect<U>& _rect);
	
	////////////////////////////////////////////////////////////
	///
	///	\brief	Checks whether a point at the given x and y
	///			coordinate is contained within this Rect
	///
	///	\param	_x		x coordinate of the point to check
	///
	///	\param	_y		y coordinate of the point to check
	///
	///	\return	Boolean value representing whether or not the 
	///			x and y coordinate is contained
	///
	////////////////////////////////////////////////////////////
	bool contains(T _x, T _y);
	////////////////////////////////////////////////////////////
	///
	///	\brief	Checks whether the given Vector2 is contained
	///			within this Rect
	///
	///	\param	_position	Vector2 representation of the 
	///						position to check
	///
	///	\return	Boolean value whether or not the given position
	///			is contained
	///
	////////////////////////////////////////////////////////////
	bool contains(const Vector2<T>& _position);
	
	////////////////////////////////////////////////////////////
	///
	///	\brief	Checks whether the given Rect intersects with
	///			this one
	///
	///	\param	_rect			Rect to check intersection against
	///
	///	\param	_intersection	Rect that, if the intersection is
	///							true, will contain the intersected
	///							area
	///
	///	\return	Boolean value representing whether or not the
	///			given Rect intersects with this Rect
	///
	////////////////////////////////////////////////////////////
	bool intersects(const Rect<T>& _rect, Rect<T>& _intersection = Rect<T>());

    ////////////////////////////////////////////////////////////
    ///
    /// \brief  Expands the current Rect so it contains the given one
    ///
    /// \param  _rect   The rect to ensure is contained
    ///
    ////////////////////////////////////////////////////////////
	void expandToContain(const Rect<T>& _rect);
	
public:
	T left;		///<	left position of the Rect

	T bot;		///<	bottom position of the Rect

	T width;	///<	width of the Rect

	T height;	///<	height of the Rect
};

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Rect
///
///	\brief		Overload of equal-to operator
///
///	\param		_left		First Rect to compare
///
///	\param		_right		Second Rect to compare
///
///	\return		Boolean value representing if the given two
///				Rect's intersect
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator ==(const Rect<T>& _left, const Rect<T>& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Rect
///
///	\brief		Overload of not equal-to operator
///
///	\param		_left		First Rect to compare
///
///	\param		_right		Second Rect to compare
///
///	\return		Boolean value representing if the given two
///				Rect's don't intersect
///
////////////////////////////////////////////////////////////
template <typename T>
bool operator !=(const Rect<T>& _left, const Rect<T>& _right);

#include "Rect.inl"

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_RECT_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Rect
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code 
///	zeno::Rect<float> vec = zeno::Rect<float>();
///	\endcode
///
////////////////////////////////////////////////////////////