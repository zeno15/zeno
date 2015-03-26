#ifndef INCLUDED_ZENO_SYSTEM_TIME_HPP
#define INCLUDED_ZENO_SYSTEM_TIME_HPP

#include <ostream>

namespace zeno {

////////////////////////////////////////////////////////////
//
//	Class for mainpulating basic time operations
//
////////////////////////////////////////////////////////////
class Time
{
public:
	////////////////////////////////////////////////////////////
	//
	//	Default constructor, sets time to zero
	//
	////////////////////////////////////////////////////////////
	Time(void);
	
	////////////////////////////////////////////////////////////
	//
	//	returns the value of the time in seconds
	//
	////////////////////////////////////////////////////////////
	float asSeconds(void) const;
	////////////////////////////////////////////////////////////
	//
	//	returns the value of the time in milliseconds
	//
	////////////////////////////////////////////////////////////
	long asMilliseconds(void) const;
	////////////////////////////////////////////////////////////
	//
	//	returns the value of the time in microseconds
	//
	////////////////////////////////////////////////////////////
	long long asMicroseconds(void) const;
	
	////////////////////////////////////////////////////////////
	//
	//	creates a time value from seconds
	//
	////////////////////////////////////////////////////////////
	static Time seconds(const float& _seconds);
	////////////////////////////////////////////////////////////
	//
	//	creates a time value from milliseconds
	//
	////////////////////////////////////////////////////////////
	static Time milliseconds(const long& _milliseconds);
	////////////////////////////////////////////////////////////
	//
	//	create a time value from microseconds
	//
	////////////////////////////////////////////////////////////
	static Time microseconds(const long long& _microseconds);

private:
	////////////////////////////////////////////////////////////
	//
	//	Explicit constructor to create Time using microseconds
	//
	////////////////////////////////////////////////////////////
	explicit Time(long long _microseconds);
	
private:
	////////////////////////////////////////////////////////////
	//
	//	representation of time in microseconds
	//
	////////////////////////////////////////////////////////////
	long long 	m_Microseconds;
};

////////////////////////////////////////////////////////////
//
//	Overload of == operator
//	compares if two Time objects are equal
//
////////////////////////////////////////////////////////////
bool operator ==(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of != operator
//	compares if two Time objects are not equal
//
////////////////////////////////////////////////////////////
bool operator !=(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of > operator
//	compares if one Time object is greater than another
//
////////////////////////////////////////////////////////////
bool operator >(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of >= operator
//	compares if one Time object is greater than/equal to another
//
////////////////////////////////////////////////////////////
bool operator >=(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of < operator
//	compares if one Time object is less than another
//
////////////////////////////////////////////////////////////
bool operator <(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of <= operator
//	compares if one Tine object is less than/equal to another
//
////////////////////////////////////////////////////////////
bool operator <=(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of - operator
//	returns negated Time object
//
////////////////////////////////////////////////////////////
Time operator -(const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of - operator
//	returns one Time object subtracted from another
//
////////////////////////////////////////////////////////////
Time operator -(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of -= operator
//	subtracts one Time object from another
//
////////////////////////////////////////////////////////////
Time& operator -=(Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of + operator
//	return one Time object added to another
//
////////////////////////////////////////////////////////////
Time operator +(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of += operator
//	adds one Time object to another
//
////////////////////////////////////////////////////////////
Time& operator +=(Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of * operator
//	returns a Time object multiplied by a float value (seconds)
//
////////////////////////////////////////////////////////////
Time operator *(const Time& _left, const float& _right);

////////////////////////////////////////////////////////////
//
//	Overload of * operator
//	return a Time object multiplied by a long long value (microseconds)
//
////////////////////////////////////////////////////////////
Time operator *(const Time& _left, const long long& _right);

////////////////////////////////////////////////////////////
//
//	Overload of * operator
//	returns a Time object multiplied by another
//
////////////////////////////////////////////////////////////
Time operator *(const float& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of * operator
//	returns a long long value (microseconds) multiplied by a Time object
//
////////////////////////////////////////////////////////////
Time operator *(const long long& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of *= operator
//	multiplies one Time object by a float value (seconds)
//
////////////////////////////////////////////////////////////
Time& operator *=(Time& _left, const float& _right);

////////////////////////////////////////////////////////////
//
//	Overload of *= operator
//	multiplies one Time object by a long long value (microseconds)
//
////////////////////////////////////////////////////////////
Time& operator *=(Time& _left, const long long& _right);

////////////////////////////////////////////////////////////
//
//	Overload of / operator
//	returns float value of one Time object divided by another
//
////////////////////////////////////////////////////////////
float operator /(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overoad of / operator
//	returns a Time object by a float value (seconds)
//
////////////////////////////////////////////////////////////
Time operator /(const Time& _left, const float& _right);

////////////////////////////////////////////////////////////
//
//	Overload of / operator
//	returns a Time object by a long long value (microseconds)
//
////////////////////////////////////////////////////////////
Time operator /(const Time& _left, const long long& _right);

////////////////////////////////////////////////////////////
//
//	Overload of /= operator
//	divides a Time object by a float value (seconds)
//
////////////////////////////////////////////////////////////
Time& operator /=(Time& _left, const float& _right);

////////////////////////////////////////////////////////////
//
//	Overload of /= operator
//	divides a Time object by a long long value (microseconds)
//
////////////////////////////////////////////////////////////
Time& operator /=(Time& _left, const long long& _right);

////////////////////////////////////////////////////////////
//
//	Overload of % operator
//	returns a Time object modulo another Time object
//
////////////////////////////////////////////////////////////
Time operator %(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of %= operator
//	modulos one TIme object by another Time object
//
////////////////////////////////////////////////////////////
Time& operator %=(Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
//
//	Overload of << operator for std::ostream
//
////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& os, zeno::Time const& _time);
} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_TIME_HPP
