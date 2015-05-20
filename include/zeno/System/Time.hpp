#ifndef INCLUDED_ZENO_SYSTEM_TIME_HPP
#define INCLUDED_ZENO_SYSTEM_TIME_HPP

#include <ostream>


////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief	Class for mainpulating basic time operations
///
////////////////////////////////////////////////////////////
class Time
{
public:
	////////////////////////////////////////////////////////////
	///
	///	\brief	Default constructor
	///
	///	Initialises the time object at 0 seconds
	///
	////////////////////////////////////////////////////////////
	Time(void);
	
	////////////////////////////////////////////////////////////
	///
	///	\brief	Returns the value of this Time object in seconds
	///
	///	\return	float representing Time object in seconds
	///
	////////////////////////////////////////////////////////////
	float asSeconds(void) const;
	////////////////////////////////////////////////////////////
	///
	///	\brief	Returns the value of this Time object in milli 
	///			seconds
	///
	///	\return	long representing Time object in milli seconds
	///
	////////////////////////////////////////////////////////////
	long asMilliseconds(void) const;
	////////////////////////////////////////////////////////////
	///
	///	\brief	Returns the value of this Time object in micro 
	///			seconds
	///
	///	\return	long long representing Time object in micro 
	///			seconds
	///
	////////////////////////////////////////////////////////////
	long long asMicroseconds(void) const;
	
	////////////////////////////////////////////////////////////
	///
	///	\brief	Creates a Time object from an amount of seconds
	///
	///	\param	_seconds	amount of seconds
	///
	///	\return	Time object created from the amount of seconds
	///
	////////////////////////////////////////////////////////////
	static Time seconds(const float& _seconds);
	////////////////////////////////////////////////////////////
	///
	///	\brief	Creates a Time object from an amount of milli 
	///			seconds
	///
	///	\param	_milliseconds	amount of milli seconds
	///
	///	\return	Time object created from the amount of milli 
	///			seconds
	///
	////////////////////////////////////////////////////////////
	static Time milliseconds(const long& _milliseconds);
	////////////////////////////////////////////////////////////
	///
	///	\brief	Creates a Time object from an amount of micro 
	///			seconds
	///
	///	\param	_microseconds	amount of micro seconds
	///
	///	\return	Time object created from the amount of micro 
	///			seconds
	///
	////////////////////////////////////////////////////////////
	static Time microseconds(const long long& _microseconds);

private:
	////////////////////////////////////////////////////////////
	///
	///	\brief	Internal constructor
	///
	///	Used to create Time object, to actually construct
	///	with user defined values, use the static methods
	///
	///	\param	_microseconds	value to initialise Time object
	///							with in micro seconds
	///
	////////////////////////////////////////////////////////////
	explicit Time(long long _microseconds);
	
private:
	long long 	m_Microseconds;		///<	Value of Time object in micro seconds
};

////////////////////////////////////////////////////////////
///
///	\relates zeno::Time
///
///	\brief	Overload of boolean equal operator
///
///	\param	_left	Time object
///
///	\param	_right	Time object
///
///	\return	Boolean value representing if the two Time 
///			objects represent the same Time value
///
////////////////////////////////////////////////////////////
bool operator ==(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates zeno::Time
///
///	\brief	Overload of boolean not-equal operator
///
///	\param	_left	Time object
///
///	\param	_right	Time object
///
///	\return	Boolean value representing if the two Time 
///			objects represent a different Time value
///
////////////////////////////////////////////////////////////
bool operator !=(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Time
///
///	\brief		Overload of greater-than operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Boolean value representing if \a _left is
///				greater than \a _right
///
////////////////////////////////////////////////////////////
bool operator >(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Time
///
///	\brief		Overload of greater-than-or-equal operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Boolean value representing if \a _left is
///				greater than or equal to \a _right
///
////////////////////////////////////////////////////////////
bool operator >=(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Time
///
///	\brief		Overload of less-than operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Boolean value representing if \a _left is
///				less than \a _right
///
////////////////////////////////////////////////////////////
bool operator <(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Time
///
///	\brief		Overload of less-than-or-equal operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Boolean value representing if \a _left is
///				less than or equal to \a _right
///
////////////////////////////////////////////////////////////
bool operator <=(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Time
///
///	\brief		Overload of negate operator
///
///	\param		_right	Time object
///
///	\return		Time object which has the negated value of
///				\a _right
///
////////////////////////////////////////////////////////////
Time operator -(const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of minus operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Time object who has the value of \a _left 
///				with \a _right subtracted from it
///
////////////////////////////////////////////////////////////
Time operator -(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Time
///
///	\brief		Overload of minus-equals operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Reference to \a _left which has \a _right
///				subtracted from it
///
////////////////////////////////////////////////////////////
Time& operator -=(Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of plus operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Time object who has the value of \a _left 
///				added to \a _right
///
////////////////////////////////////////////////////////////
Time operator +(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of plus-equals operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Reference to \a _left which has \a _right
///				added to it
///
////////////////////////////////////////////////////////////
Time& operator +=(Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of multiply operator
///
///	\param		_left	Time object
///
///	\param		_right	Value in seconds
///
///	\return		Time object who has the value of \a _left 
///				multiplied by \a _right
///
////////////////////////////////////////////////////////////
Time operator *(const Time& _left, const float& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of multiply operator
///
///	\param		_left	Time object
///
///	\param		_right	Value in microseconds
///
///	\return		Time object who has the value of \a _left 
///				multiplied by \a _right
///
////////////////////////////////////////////////////////////
Time operator *(const Time& _left, const long long& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of multiply operator
///
///	\param		_left	Value in seconds
///
///	\param		_right	Time object
///
///	\return		Time object who has the value of \a _left 
///				multiplied by \a _right
///
////////////////////////////////////////////////////////////
Time operator *(const float& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of multiply operator
///
///	\param		_left	Value in microseconds
///
///	\param		_right	Time object
///
///	\return		Time object who has the value of \a _left 
///				multiplied by \a _right
///
////////////////////////////////////////////////////////////
Time operator *(const long long& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of multiply-equals operator
///
///	\param		_left	Time object
///
///	\param		_right	Value in seconds
///
///	\return		Reference to \a _left which has been multiplied
///				by \a _right
///
////////////////////////////////////////////////////////////
Time& operator *=(Time& _left, const float& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of multiply-equals operator
///
///	\param		_left	Time object
///
///	\param		_right	Value in microseconds
///
///	\return		Reference to \a _left which has been multiplied
///				by \a _right
///
////////////////////////////////////////////////////////////
Time& operator *=(Time& _left, const long long& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of divide operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Time object which is \a _left divided by 
///				\a _right
///
////////////////////////////////////////////////////////////
float operator /(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of divide operator
///
///	\param		_left	Time object
///
///	\param		_right	Value in seconds
///
///	\return		Time object which is \a _left divided by 
///				\a _right
///
////////////////////////////////////////////////////////////
Time operator /(const Time& _left, const float& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of divide operator
///
///	\param		_left	Time object
///
///	\param		_right	Value in microseconds
///
///	\return		Time object which is \a _left divided by 
///				\a _right
///
////////////////////////////////////////////////////////////
Time operator /(const Time& _left, const long long& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of divide-equals operator
///
///	\param		_left	Time object
///
///	\param		_right	Value in seconds
///
///	\return		Reference to \a _left which has been divided
///				by \a _right
///
////////////////////////////////////////////////////////////
Time& operator /=(Time& _left, const float& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of divide-equals operator
///
///	\param		_left	Time object
///
///	\param		_right	Value in microseconds
///
///	\return		Reference to \a _left which has been divided
///				by \a _right
///
////////////////////////////////////////////////////////////
Time& operator /=(Time& _left, const long long& _right);

////////////////////////////////////////////////////////////
///
///	\relates 	zeno::Time
///
///	\brief		Overload of modulo operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Time object which is the remainder of 
///				\a _left modulo \a _right
///
////////////////////////////////////////////////////////////
Time operator %(const Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Time
///
///	\brief		Overload of modulo-equals operator
///
///	\param		_left	Time object
///
///	\param		_right	Time object
///
///	\return		Reference to \a _left Time object which is
///				the remainder of \a _left modulo \a _right
///
////////////////////////////////////////////////////////////
Time& operator %=(Time& _left, const Time& _right);

////////////////////////////////////////////////////////////
///
///	\relates	zeno::Time
///
///	\brief		Overload of << operator
///
///	\param		os			std::ostream reference
///
///	\param		_time		Time to be output
///
///	\return		std::ostream reference with formatted Time
///				output inserted into it
///
////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& os, zeno::Time const& _time);

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_TIME_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Time
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code 
///	zeno::Time time = zeno::Time::seconds(0.0f);
///	\endcode
///
////////////////////////////////////////////////////////////