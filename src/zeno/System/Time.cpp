#include <zeno/System/Time.hpp>

namespace zeno {

Time::Time(void) :
m_Microseconds(0)
{
}
Time::Time(long long _microseconds) :
m_Microseconds(_microseconds)
{
}

float Time::asSeconds(void) const
{
	return static_cast<float>(m_Microseconds) / 1000000.0f;
}
long Time::asMilliseconds(void) const
{
	return static_cast<long>(m_Microseconds / 1000);
}
long long Time::asMicroseconds(void) const
{
	return m_Microseconds;
}

Time Time::seconds(const float& _seconds)
{
	return Time(static_cast<long long>(_seconds * 1000000));
}
Time Time::milliseconds(const long& _milliseconds)
{
	return Time(static_cast<long long>(_milliseconds * 1000));
}
Time Time::microseconds(const long long& _microseconds)
{
	return Time(_microseconds);
}

bool operator ==(const Time& _left, const Time& _right)
{
	return _left.asMicroseconds() == _right.asMicroseconds();
}

bool operator !=(const Time& _left, const Time& _right)
{
	return !(_left == _right);
}

bool operator >(const Time& _left, const Time& _right)
{
	return _left.asMicroseconds() > _right.asMicroseconds();
}

bool operator >=(const Time& _left, const Time& _right)
{
	return _left.asMicroseconds() >= _right.asMicroseconds();
}

bool operator <(const Time& _left, const Time& _right)
{
	return _left.asMicroseconds() < _right.asMicroseconds();
}

bool operator <=(const Time& _left, const Time& _right)
{
	return _left.asMicroseconds() <= _right.asMicroseconds();
}

Time operator -(const Time& _right)
{
	return Time::microseconds(- _right.asMicroseconds());
}

Time operator -(const Time& _left, const Time& _right)
{
	return Time::microseconds(_left.asMicroseconds() - _right.asMicroseconds());
}

Time& operator -=(Time& _left, const Time& _right)
{
	_left = Time::microseconds(_left.asMicroseconds() - _right.asMicroseconds());
	
	return _left;
}

Time operator +(const Time& _left, const Time& _right)
{
	return Time::microseconds(_left.asMicroseconds() + _right.asMicroseconds());
}

Time& operator +=(Time& _left, const Time& _right)
{
	_left = Time::microseconds(_left.asMicroseconds() + _right.asMicroseconds());
	
	return _left;
}

Time operator *(const Time& _left, const float& _right)
{
	return Time::seconds(_left.asSeconds() * _right);
}
Time operator *(const Time& _left, const long long& _right)
{
	return Time::microseconds(_left.asMicroseconds() * _right);
}
Time operator *(const float& _left, const Time& _right)
{
	return Time::seconds(_left * _right.asSeconds());
}
Time operator *(const long long& _left, const Time& _right)
{
	return Time::microseconds(_left * _right.asMicroseconds());
}

Time& operator *=(Time& _left, const float& _right)
{
	_left = Time::seconds(_left.asSeconds() * _right);
	
	return _left;
}
Time& operator *=(Time& _left, const long long& _right)
{
	_left = Time::microseconds(_left.asMicroseconds() * _right);
	
	return _left;
}

float operator /(const Time& _left, const Time& _right)
{
	return _left.asSeconds() / _right.asSeconds();
}
Time operator /(const Time& _left, const float& _right)
{
	return Time::seconds(_left.asSeconds() / _right);
}
Time operator /(const Time& _left, const long long& _right)
{
	return Time::microseconds(_left.asMicroseconds() / _right);
}

Time& operator /=(Time& _left, const float& _right)
{
	_left = Time::seconds(_left.asSeconds() / _right);
	
	return _left;
}
Time& operator /=(Time& _left, const long long& _right)
{
	_left = Time::microseconds(_left.asMicroseconds() / _right);
	
	return _left;
}

Time operator %(const Time& _left, const Time& _right)
{
	return Time::microseconds(_left.asMicroseconds() % _right.asMicroseconds());
}

Time& operator %=(Time& _left, const Time& _right)
{
	_left = Time::microseconds(_left.asMicroseconds() % _right.asMicroseconds());
	
	return _left;
}

std::ostream& operator <<(std::ostream& os, zeno::Time const& _time)
{
	os << _time.asMicroseconds() << " us";
	return os;
}

} //~ namespace zeno
