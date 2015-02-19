#ifndef INCLUDED_TO_STRING_HPP
#define INCLUDED_TO_STRING_HPP

#include <Colour.hpp>
#include <Vector3.hpp>

namespace Catch {
	
std::string toString(zeno::Colour const& _value)
{
	return std::string("r: " + _value.r + ", g: " + _value.g + ", b: " + _value.b + ", a: " + _value.a);
}
	
template <typename T>
std::string toString(zeno::Vector3<T> const& _value)
{
	return std::string("x: " + _value.x + ", y: " + _value.y + ", z: " + _value.z);
}

}

#endif //~ INCLUDED_TO_STRING_HPP
