#include <iostream>
#include <cstdlib>
#include <unistd.h>

//~ https://github.com/philsquared/Catch
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <Colour.hpp>
#include <Clock.hpp>
#include <Image.hpp>
#include <ImageLoader.hpp>
#include <Mat4x4.hpp>
#include <Rect.hpp>
#include <Time.hpp>
#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>
#include <Window.hpp>


/*	Macros

	REQUIRE(expression)	-	Returns on failure
	CHECK(expression)		-	Continues on failure

	REQUIRE_FALSE(expression)
	CHECK_FALSE(expression)

	REQUIRE_THROW_AS(expression, exception type)
	CHECK_THROW_AS(expression, exception type)

	REQUIRE_NOTHROW(expression)
	CHECK_NOTHROW(expression)
*/

TEST_CASE("Clock test", "[Clock]") {
	SECTION("Initial") {
		zeno::Clock clock = zeno::Clock();
		
		sleep(1);
		
		REQUIRE(clock.getElapsedTime().asSeconds() > 0.95f);
		REQUIRE(clock.getElapsedTime().asSeconds() < 1.05f);
	}
}

TEST_CASE("Colour::Red test", "[Colour]" ) {
	//~ Anything done here is like a setup for each section
	//~ Can nest sections

	SECTION("Section 1") {
		REQUIRE(1 == 1);
	}
	SECTION("Section 2") {
		int val = 2;
		SECTION("Section 2.1")
		{
			REQUIRE(val == 2);
			val = 5;
		}
		SECTION("Section 2.2")
		{
			REQUIRE(val == 2);
		}
	}
}

TEST_CASE("Image Test", "[Image]") {
	SECTION("Initial") {
		zeno::Image img = zeno::Image();
	}
}

TEST_CASE("ImageLoader Test", "[ImageLoader]") {
	SECTION("Initial") {
		zeno::ImageLoader::getInstance();
	}
}

TEST_CASE("Mat4x4 Test", "[Mat4x4]") {
	SECTION("Initial") {
		zeno::Mat4x4 mat = zeno::Mat4x4(1.0f);
		
		REQUIRE(mat[0] == 1.0f);
	}
}

TEST_CASE("Time Test", "[Time]") {
	SECTION("Initial") {
		zeno::Time time = zeno::Time::seconds(1.0f);
		
		REQUIRE(time.asSeconds() == 1.0f);
	}
}

TEST_CASE("Rect Test", "[Rect]") {
	SECTION("Initial") {
		zeno::Rect<float> rect = zeno::Rect<float>();
		
		REQUIRE(rect.left == 0.0f);
	}
}

TEST_CASE("Vector2 Test", "[Vector2]") {
	SECTION("Initial") {
		zeno::Vector2f vec = zeno::Vector2f(1.0f, 2.0f);
		
		REQUIRE(vec.x == 1.0f);
		REQUIRE(vec.y == 2.0f);
	}
}

TEST_CASE("Vector3 Test", "[Vector3]") {
	SECTION("Initial") {
		zeno::Vector3f vec = zeno::Vector3f(1.0f, 2.0f, 3.0f);
		
		REQUIRE(vec.x == 1.0f);
		REQUIRE(vec.y == 2.0f);
		REQUIRE(vec.z == 3.0f);
	}
}

TEST_CASE("Vector4 Test", "[Vector4]") {
	SECTION("Initial") {
		zeno::Vector4f vec = zeno::Vector4f(1.0f, 2.0f, 3.0f, 4.0f);
		
		REQUIRE(vec.x == 1.0f);
		REQUIRE(vec.y == 2.0f);
		REQUIRE(vec.z == 3.0f);
		REQUIRE(vec.w == 4.0f);
	}
}

TEST_CASE("Window Test", "[Window]") {
	SECTION("Initial") {
		zeno::Window window = zeno::Window();
		window.display();
	}
}

/*
#include <iostream>
#include <cstdlib>

#include "../test/testStringConversions.hpp"
#include "../include/lest-1.22.0/lest.hpp"

#include "../include/Clock.hpp"
#include "../include/Time.hpp"
#include "../include/Vector2.hpp"
#include "../include/Vector3.hpp"
#include "../include/Vector4.hpp"
#include "../include/Colour.hpp"
#include "../include/Rect.hpp"
#include "../include/Mat4x4.hpp"




const lest::test TimeClassTest[] =
{
	CASE("Test time default constructor gives 0 initial value")
    {
		zeno::Time t = zeno::Time();
		
        EXPECT(t.asMicroseconds() == 0);
    },
	CASE("Test non default seconds constructor works as expected")
	{
		zeno::Time t = zeno::Time::seconds(1.0f);
		
		EXPECT(t.asSeconds() == 1.0f);
		EXPECT(t.asMilliseconds() == 1000);
		EXPECT(t.asMicroseconds() == 1000000);
	},
	CASE("Test non default milliseconds constructor works as expected")
	{
		zeno::Time t = zeno::Time::milliseconds(1000);
		
		EXPECT(t.asSeconds() == 1.0f);
		EXPECT(t.asMilliseconds() == 1000);
		EXPECT(t.asMicroseconds() == 1000000);
	},
	CASE("Test non default microseconds constructor works as expected")
	{
		zeno::Time t = zeno::Time::microseconds(1000000);
		
		EXPECT(t.asSeconds() == 1.0f);
		EXPECT(t.asMilliseconds() == 1000);
		EXPECT(t.asMicroseconds() == 1000000);
	},
	CASE("Test == operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		EXPECT(t1 == t2);
		
		t1 = zeno::Time::microseconds(1000);
		t2 = zeno::Time::milliseconds(1);
		EXPECT(t1 == t2);
		
		t1 = zeno::Time::seconds(12.0f);
		EXPECT_NOT(t1 == t2);
	},
	CASE("Test != operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		EXPECT_NOT(t1 != t2);
		
		t1 = zeno::Time::seconds(10.0f);
		EXPECT(t1 != t2);
	},
	CASE("Test > operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		EXPECT_NOT(t1 > t2);
		
		t1 = zeno::Time::microseconds(100);
		EXPECT(t1 > t2);
		EXPECT_NOT(t2 > t1);
	},
	CASE("Test >= operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		EXPECT(t1 >= t2);
		EXPECT(t2 >= t1);
		
		t1 = zeno::Time::microseconds(10);
		EXPECT(t1 >= t2);
		EXPECT_NOT(t2 >= t1);
	},
	CASE("Test < operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		EXPECT_NOT(t1 < t2);
		
		t1 = zeno::Time::microseconds(10);
		EXPECT(t2 < t1);
		EXPECT_NOT(t1 < t2);
	},
	CASE("Test <= operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		EXPECT(t1 <= t2);
		EXPECT(t2 <= t1);
		
		t1 = zeno::Time::microseconds(10);
		EXPECT(t2 <= t1);
		EXPECT_NOT(t1 <= t2);
	},
	CASE("Test -(negate) operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		EXPECT(t1.asMicroseconds() == 1);
		
		t1 = - t1;
		EXPECT(t1.asMicroseconds() == -1);		
	},
	CASE("Test - operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		zeno::Time res = t1 - t2;
		EXPECT(res == zeno::Time::microseconds(0));
		
		t2 = zeno::Time::microseconds(10);
		res = t1 - t2;
		EXPECT(res == zeno::Time::microseconds(-9));
	},
	CASE("Test -= operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		t1 -= t2;
		EXPECT(t1.asMicroseconds() == 0);
		
		t1 -= t2;
		EXPECT(t1.asMicroseconds() == -1);
	},
	CASE("Test + operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		zeno::Time res = t1 + t2;
		EXPECT(res == zeno::Time::microseconds(2));
		
		t1 = zeno::Time::microseconds(-5);
		res = t1 + t2;
		EXPECT(res == zeno::Time::microseconds(-4));
	},
	CASE("Test += operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		t1 += t2;
		EXPECT(t1 == zeno::Time::microseconds(2));
		
		t2 = zeno::Time::microseconds(-5);
		t1 += t2;
		EXPECT(t1 == zeno::Time::microseconds(-3));
	},
	CASE("Test / operator")
	{
		zeno::Time t1 = zeno::Time::seconds(1.0f);
		zeno::Time t2 = zeno::Time::seconds(0.5f);
		float tf = 0.1f;
		long long tll = 1000000;
		
		
		EXPECT((t1 / t2) == 2.0f);
		
		EXPECT((t1 / tf) == zeno::Time::seconds(10.0f));
		
		EXPECT((t1 / tll) == zeno::Time::microseconds(1));
	},
	CASE("Test /= operator")
	{
		zeno::Time t1 = zeno::Time::seconds(100);
		zeno::Time t2 = zeno::Time::microseconds(100);
		
		t1 /= 4.0f;
		EXPECT(t1 == zeno::Time::seconds(25.0f));
		
		t2 /= 20ll;
		EXPECT(t2 == zeno::Time::microseconds(5));
	},
	CASE("Test * operator")
	{
		zeno::Time t1 = zeno::Time::seconds(10);
		zeno::Time t2 = zeno::Time::microseconds(10);
		
		zeno::Time res = t1 * 3.0f;
		EXPECT(res == zeno::Time::seconds(30.0f));
		
		res = t2 * 3ll;
		EXPECT(res == zeno::Time::microseconds(30));
		
		res = 3.0f * t1;
		EXPECT(res == zeno::Time::seconds(30.0f));
		
		res = 3ll * t2;
		EXPECT(res == zeno::Time::microseconds(30));
	},
	CASE("Test *= operator")
	{
		zeno::Time t1 = zeno::Time::seconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		
		t1 *= 100.0f;
		EXPECT(t1 == zeno::Time::seconds(100.0f));
		
		t2 *= 1023ll;
		EXPECT(t2 == zeno::Time::microseconds(1023));
	},
	CASE("Test % operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(10);
		zeno::Time t2 = zeno::Time::microseconds(4);
		
		zeno::Time res = t1 % t2;
		EXPECT(res == zeno::Time::microseconds(2));
		
		t2 = zeno::Time::microseconds(5);
		res = t1 % t2;
		EXPECT(res == zeno::Time::microseconds(0));
	},
	CASE("Test %= operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(10);
		zeno::Time t2 = zeno::Time::microseconds(10);
		
		t1 %= t2;
		EXPECT(t1 == zeno::Time::microseconds(0));
		
		t1 = zeno::Time::microseconds(10);
		t2 = zeno::Time::microseconds(4);
		t1 %= t2;
		EXPECT(t1 == zeno::Time::microseconds(2));
	},
};

const lest::test Vector2Test[] = 
{
	CASE("Test default constructor")
	{
		zeno::Vector2<float> vec = zeno::Vector2<float>();
		
		EXPECT(vec.x == 0.0f);
		EXPECT(vec.y == 0.0f);
	},
	
	CASE("Test non-default constructor")
	{
		float x = 1.0f;
		float y = 12.0f;
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		
		EXPECT(vec.x == x);
		EXPECT(vec.y == y);
	},
	
	CASE("Test copy constructor from same type")
	{
		float x = 1.2f;
		float y = 12.2f;
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		zeno::Vector2<float> cpy = zeno::Vector2<float>(vec);
		
		EXPECT(cpy == vec);
	},
	
	CASE("Test copy constructor from different type")
	{
		int x = 12;
		int y = 453;
		zeno::Vector2<int> vec = zeno::Vector2<int>(x, y);
		zeno::Vector2<float> cpy = zeno::Vector2<float>(vec);
		
		EXPECT(cpy.x == static_cast<float>(x));
		EXPECT(cpy.y == static_cast<float>(y));
	},
	
	CASE("Test -(negate) operator")
	{
		float x = 12.3f;
		float y = -123.7f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec = - vec;
		
		EXPECT(vec.x == -x);
		EXPECT(vec.y == -y);
	},
	
	CASE("TEST - operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		
		zeno::Vector2<float> res = zeno::Vector2<float>(x, y) - zeno::Vector2<float>(x, y);
		
		EXPECT(res == zeno::Vector2<float>(0.0f, 0.0f));
	},
	
	CASE("Test -= operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		
		zeno::Vector2<float> res = zeno::Vector2<float>(x, y);
		
		res -= zeno::Vector2<float>(x, y);
		
		EXPECT(res == zeno::Vector2<float>(0.0f, 0.0f));
	},
	
	CASE("Test + operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		
		zeno::Vector2<float> res = zeno::Vector2<float>(x, y) + zeno::Vector2<float>(x, y);
		
		EXPECT(res == zeno::Vector2<float>(2.0f * x, 2.0f * y));
	},
	
	CASE("Test += operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		
		zeno::Vector2<float> res = zeno::Vector2<float>(x, y);
		res += res;
		
		EXPECT(res == zeno::Vector2<float>(2.0f * x, 2.0f * y));
	},
		
	CASE("Test / operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float div = 7.4f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec = vec / div;
		
		EXPECT(vec == zeno::Vector2<float>(x / div, y / div));
	},
	
	CASE("Test /= operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float div = 7.4f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec /= div;
		
		EXPECT(vec == zeno::Vector2<float>(x / div, y / div));
	},
	
	CASE("Test * operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float mul = 2.1f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec = vec * mul;
		
		EXPECT(vec == zeno::Vector2<float>(x * mul, y * mul));
		
		
		vec = zeno::Vector2<float>(x, y);
		vec = mul * vec;
		
		EXPECT(vec == zeno::Vector2<float>(x * mul, y * mul));
	},
	
	CASE("Test *= operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float mul = 2.1f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec *= mul;
		
		EXPECT(vec == zeno::Vector2<float>(x * mul, y * mul));
	},
		
	CASE("Test == operator")
	{
		zeno::Vector2<float> vec1 = zeno::Vector2<float>(123.4f, 11.0f);
		zeno::Vector2<float> vec2 = zeno::Vector2<float>(13.4f, 1121.0f);
		
		EXPECT_NOT(vec1 == vec2);
		
		vec2 = vec1;
		EXPECT(vec1 == vec2);
	},
	
	CASE("Test != operator")
	{
		zeno::Vector2<float> vec1 = zeno::Vector2<float>(123.4f, 11.0f);
		zeno::Vector2<float> vec2 = zeno::Vector2<float>(13.4f, 1121.0f);
		
		EXPECT(vec1 != vec2);
		
		vec2 = vec1;
		EXPECT_NOT(vec1 != vec2);
	},
};

const lest::test Vector3Test[] = 
{
	CASE("Test default constructor")
	{
		zeno::Vector3<float> vec = zeno::Vector3<float>();
		
		EXPECT(vec.x == 0.0f);
		EXPECT(vec.y == 0.0f);
		EXPECT(vec.z == 0.0f);
	},
	
	CASE("Test non-default constructor")
	{
		float x = 1.0f;
		float y = 12.0f;
		float z = -12.8f;
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		
		EXPECT(vec.x == x);
		EXPECT(vec.y == y);
		EXPECT(vec.z == z);
	},
	
	CASE("Test copy constructor from same type")
	{
		float x = 1.2f;
		float y = 12.2f;
		float z = -12.8f;
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		zeno::Vector3<float> cpy = zeno::Vector3<float>(vec);
		
		EXPECT(cpy == vec);
	},
	
	CASE("Test copy constructor from different type")
	{
		int x = 12;
		int y = 453;
		int z = -18;
		zeno::Vector3<int> vec = zeno::Vector3<int>(x, y, z);
		zeno::Vector3<float> cpy = zeno::Vector3<float>(vec);
		
		EXPECT(cpy == zeno::Vector3<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
	},
	
	CASE("Test -(negate) operator")
	{
		float x = 12.3f;
		float y = -123.7f;
		float z = 88.1f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec = - vec;
		
		EXPECT(vec == zeno::Vector3<float>(-x, -y, -z));
	},
	
	CASE("TEST - operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -12.8f;
		
		zeno::Vector3<float> res = zeno::Vector3<float>(x, y, z) - zeno::Vector3<float>(x, y, z);
		
		EXPECT(res == zeno::Vector3<float>());
	},
	
	CASE("Test -= operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.1f;
		
		zeno::Vector3<float> res = zeno::Vector3<float>(x, y, z);
		
		res -= zeno::Vector3<float>(x, y, z);
		
		EXPECT(res == zeno::Vector3<float>());
	},
	
	CASE("Test + operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.9f;
		
		zeno::Vector3<float> res = zeno::Vector3<float>(x, y, z) + zeno::Vector3<float>(x, y, z);
		
		EXPECT(res == zeno::Vector3<float>(2.0f * x, 2.0f * y, 2.0f * z));
	},
	
	CASE("Test += operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.5f;
		
		zeno::Vector3<float> res = zeno::Vector3<float>(x, y, z);
		res += res;
		
		EXPECT(res == zeno::Vector3<float>(2.0f * x, 2.0f * y, 2.0f * z));
	},
		
	CASE("Test / operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float z = -23.4f;
		float div = 7.4f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec = vec / div;
		
		EXPECT(vec == zeno::Vector3<float>(x / div, y / div, z / div));
	},
	
	CASE("Test /= operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float z = -8.9f;
		float div = 7.4f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec /= div;
		
		EXPECT(vec == zeno::Vector3<float>(x / div, y / div, z / div));
	},
	
	CASE("Test * operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float z = -123.6f;
		float mul = 2.1f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec = vec * mul;
		
		EXPECT(vec == zeno::Vector3<float>(x * mul, y * mul, z * mul));
		
		
		vec = zeno::Vector3<float>(x, y, z);
		vec = mul * vec;
		
		EXPECT(vec == zeno::Vector3<float>(x * mul, y * mul, z * mul));
	},
	
	CASE("Test *= operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float z = -764.4f;
		float mul = 2.1f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec *= mul;
		
		EXPECT(vec == zeno::Vector3<float>(x * mul, y * mul, z* mul));
	},
		
	CASE("Test == operator")
	{
		zeno::Vector3<float> vec1 = zeno::Vector3<float>(123.4f, 11.0f, -12.0f);
		zeno::Vector3<float> vec2 = zeno::Vector3<float>(13.4f, 1121.0f, -64.4f);
		
		EXPECT_NOT(vec1 == vec2);
		
		vec2 = vec1;
		EXPECT(vec1 == vec2);
	},
	
	CASE("Test != operator")
	{
		zeno::Vector3<float> vec1 = zeno::Vector3<float>(123.4f, 11.0f, -12.0f);
		zeno::Vector3<float> vec2 = zeno::Vector3<float>(13.4f, 1121.0f, -64.4f);
		
		EXPECT(vec1 != vec2);
		
		vec2 = vec1;
		EXPECT_NOT(vec1 != vec2);
	},
};

const lest::test Vector4Test[] = 
{
	CASE("Test default constructor")
	{
		zeno::Vector4<float> vec = zeno::Vector4<float>();
		
		EXPECT(vec.x == 0.0f);
		EXPECT(vec.y == 0.0f);
		EXPECT(vec.z == 0.0f);
		EXPECT(vec.w == 0.0f);
	},
	
	CASE("Test non-default constructor")
	{
		float x = 1.0f;
		float y = 12.0f;
		float z = -12.8f;
		float w = 1.0f;
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		
		EXPECT(vec.x == x);
		EXPECT(vec.y == y);
		EXPECT(vec.z == z);
		EXPECT(vec.w == w);
	},
	
	CASE("Test copy constructor from same type")
	{
		float x = 1.2f;
		float y = 12.2f;
		float z = -12.8f;
		float w = 1.0f;
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		zeno::Vector4<float> cpy = zeno::Vector4<float>(vec);
		
		EXPECT(cpy == vec);
	},
	
	CASE("Test copy constructor from different type")
	{
		int x = 12;
		int y = 453;
		int z = -18;
		float w = 1;
		zeno::Vector4<int> vec = zeno::Vector4<int>(x, y, z, w);
		zeno::Vector4<float> cpy = zeno::Vector4<float>(vec);
		
		EXPECT(cpy == zeno::Vector4<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)));
	},
	
	CASE("Test -(negate) operator")
	{
		float x = 12.3f;
		float y = -123.7f;
		float z = 88.1f;
		float w = 1.0f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec = - vec;
		
		EXPECT(vec == zeno::Vector4<float>(-x, -y, -z, w));
	},
	
	CASE("TEST - operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -12.8f;
		float w = 1.0f;
		
		zeno::Vector4<float> res = zeno::Vector4<float>(x, y, z, w) - zeno::Vector4<float>(x, y, z, w);
		
		EXPECT(res == zeno::Vector4<float>(0.0f, 0.0f, 0.0f, w));
	},
	
	CASE("Test -= operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.1f;
		float w = 1.0f;
		
		zeno::Vector4<float> res = zeno::Vector4<float>(x, y, z, w);
		
		res -= zeno::Vector4<float>(x, y, z, w);
		
		EXPECT(res == zeno::Vector4<float>(0.0f, 0.0f, 0.0f, w));
	},
	
	CASE("Test + operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.9f;
		float w = 1.0f;
		
		zeno::Vector4<float> res = zeno::Vector4<float>(x, y, z, w) + zeno::Vector4<float>(x, y, z, w);
		
		EXPECT(res == zeno::Vector4<float>(2.0f * x, 2.0f * y, 2.0f * z, w));
	},
	
	CASE("Test += operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.5f;
		float w = 1.0f;
		
		zeno::Vector4<float> res = zeno::Vector4<float>(x, y, z, w);
		res += res;
		
		EXPECT(res == zeno::Vector4<float>(2.0f * x, 2.0f * y, 2.0f * z, w));
	},
		
	CASE("Test / operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float z = -23.4f;
		float w = 1.0f;
		float div = 7.4f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec = vec / div;
		
		EXPECT(vec == zeno::Vector4<float>(x / div, y / div, z / div, w));
	},
	
	CASE("Test /= operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float z = -8.9f;
		float w = 1.0f;
		float div = 7.4f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec /= div;
		
		EXPECT(vec == zeno::Vector4<float>(x / div, y / div, z / div, w));
	},
	
	CASE("Test * operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float z = -123.6f;
		float w = 1.0f;
		float mul = 2.1f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec = vec * mul;
		
		EXPECT(vec == zeno::Vector4<float>(x * mul, y * mul, z * mul, w));
		
		
		vec = zeno::Vector4<float>(x, y, z, w);
		vec = mul * vec;
		
		EXPECT(vec == zeno::Vector4<float>(x * mul, y * mul, z * mul, w));
	},
	
	CASE("Test *= operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float z = -764.4f;
		float w = 1.0f;
		float mul = 2.1f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec *= mul;
		
		EXPECT(vec == zeno::Vector4<float>(x * mul, y * mul, z* mul, w));
	},
		
	CASE("Test == operator")
	{
		zeno::Vector4<float> vec1 = zeno::Vector4<float>(123.4f, 11.0f, -12.0f, 0.0f);
		zeno::Vector4<float> vec2 = zeno::Vector4<float>(13.4f, 1121.0f, -64.4f, 0.0f);
		
		EXPECT_NOT(vec1 == vec2);
		
		vec2 = vec1;
		EXPECT(vec1 == vec2);
	},
	
	CASE("Test != operator")
	{
		zeno::Vector4<float> vec1 = zeno::Vector4<float>(123.4f, 11.0f, -12.0f, 0.0f);
		zeno::Vector4<float> vec2 = zeno::Vector4<float>(13.4f, 1121.0f, -64.4f, 0.0f);
		
		EXPECT(vec1 != vec2);
		
		vec2 = vec1;
		EXPECT_NOT(vec1 != vec2);
	},
};

const lest::test ColourClassTest[] =
{
	CASE("Test default constructor")
	{
		zeno::Colour col = zeno::Colour();
		
		EXPECT((col.r == 0.0f &&
				col.g == 0.0f &&
				col.b == 0.0f &&
				col.a == 1.0f));
	},
	CASE("Test non-default constructor")
	{
		float r = 0.2f;
		float g = 0.4f;
		float b = 0.6f;
		float a = 0.8f;
		zeno::Colour col = zeno::Colour(r, g, b, a);
		
		EXPECT((col.r == r &&
				col.g == g &&
				col.b == b &&
				col.a == a));
	},
	CASE("Test Black zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Black;
		
		EXPECT(col == zeno::Colour(0.0f, 0.0f, 0.0f, 1.0f));
	},
	CASE("Test White zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::White;
		
		EXPECT(col == zeno::Colour(1.0f, 1.0f, 1.0f));
	},
	CASE("Test Red zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Red;
		
		EXPECT(col == zeno::Colour(1.0f, 0.0f, 0.0f));
	},
	CASE("Test Green zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Green;
		
		EXPECT(col == zeno::Colour(0.0f, 1.0f, 0.0f));
	},
	CASE("Test Blue zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Blue;
		
		EXPECT(col == zeno::Colour(0.0f, 0.0f, 1.0f));
	},
	CASE("Test Yellow zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Yellow;
		
		EXPECT(col == zeno::Colour(1.0f, 1.0f, 0.0f));
	},
	CASE("Test Magenta zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Magenta;
		
		EXPECT(col == zeno::Colour(1.0f, 0.0f, 1.0f));
	},
	CASE("Test Cyan zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Cyan;
		
		EXPECT(col == zeno::Colour(0.0f, 1.0f, 1.0f));
	},
	CASE("Test Transparent zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Transparent;
		
		EXPECT(col == zeno::Colour(0.0f, 0.0f, 0.0f, 0.0f));
	},
	CASE("Test == operator")
	{
		float r = 0.2f;
		float g = 0.4f;
		float b = 0.6f;
		float a = 0.8f;
		zeno::Colour col = zeno::Colour(r, g, b, a);
		
		EXPECT(col == zeno::Colour(r, g, b, a));
		
		EXPECT_NOT(col == zeno::Colour(a, b, g, r));
	},
	CASE("Test != operator")
	{
		float r = 0.2f;
		float g = 0.4f;
		float b = 0.6f;
		float a = 0.8f;
		zeno::Colour col = zeno::Colour(r, g, b, a);
		
		EXPECT_NOT(col != zeno::Colour(r, g, b, a));
		
		EXPECT(col != zeno::Colour(a, b, g, r));
	},
	CASE("Test + operator")
	{
		zeno::Colour red = zeno::Colour::Red;
		zeno::Colour green = zeno::Colour::Green;
		
		EXPECT((red + green) == zeno::Colour::Yellow);
		
		EXPECT((red + red) == zeno::Colour::Red);
	},
	CASE("Test += operator")
	{
		zeno::Colour col = zeno::Colour::Red;
		
		col += zeno::Colour::Green;
		
		EXPECT(col == zeno::Colour::Yellow);
	},
	CASE("Test - operator")
	{
		zeno::Colour yellow = zeno::Colour::Yellow;
		zeno::Colour red = zeno::Colour::Red;
		
		EXPECT((yellow - red) == zeno::Colour::Green);
		
		EXPECT((yellow - yellow) == zeno::Colour::Black);
	},
	CASE("Test -= operator")
	{
		zeno::Colour col = zeno::Colour::Red;
		
		col -= zeno::Colour::Red;
		
		EXPECT(col == zeno::Colour::Black);
	},
	CASE("Test * operator (float)")
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		
		float val = 0.5f;
		
		zeno::Colour col = zeno::Colour(r, g, b);
		
		EXPECT((col * val) == zeno::Colour(r * val, g * val, b * val));
	},
	CASE("Test * operator (Colour)")
	{
		zeno::Colour red = zeno::Colour::Red;
		zeno::Colour white = zeno::Colour::White;
		
		EXPECT((red * white) == zeno::Colour::Red);
	},
	CASE("Test *= operator (float)")
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		
		float val = 0.5f;
		
		zeno::Colour col = zeno::Colour(r, g, b);
		
		col *= val;
		
		EXPECT(col == zeno::Colour(r * val, g * val, b * val));
	},
	CASE("Test *= operator (Colour)")
	{
		zeno::Colour red = zeno::Colour::Red;
		zeno::Colour white = zeno::Colour::White;
		
		red *= white;
		
		EXPECT(red == zeno::Colour::Red);
	},
};

const lest::test RectClassTest[] = 
{
	CASE("Test default constructor")
	{
		zeno::Rect<int> rect = zeno::Rect<int>();
		
		EXPECT((rect.left == 0 &&
				rect.bot == 0 &&
				rect.width == 0 &&
				rect.height ==0));
	},
	CASE("Test non-default constructor")
	{
		int l = 1;
		int b = 2;
		int w = 5;
		int h = 6;
		
		zeno::Rect<int> rect = zeno::Rect<int>(l, b, w, h);
		
		EXPECT((rect.left 		== l 	&&
				rect.bot 		== b 	&&
				rect.width 		== w 	&&
				rect.height 	== h));
	},
	CASE("Test copy constructor")
	{
		int l = 1;
		int b = 2;
		int w = 5;
		int h = 6;
		
		zeno::Rect<int> recti = zeno::Rect<int>(l, b, w, h);
		
		zeno::Rect<float> rectf = zeno::Rect<float>(recti);
		
		EXPECT((rectf.left 		== static_cast<float>(recti.left) 	&&
				rectf.bot 		== static_cast<float>(recti.bot) 	&&
				rectf.width 	== static_cast<float>(recti.width) 	&&
				rectf.height 	== static_cast<float>(recti.height)));
	},
	CASE("Test contains")
	{
		zeno::Rect<int> rect = zeno::Rect<int>(0, 0, 10, 10);
		
		EXPECT(rect.contains(5, 5));
		EXPECT(rect.contains(zeno::Vector2<int>(5, 5)));
		
		EXPECT_NOT(rect.contains(-5, 15));
		EXPECT_NOT(rect.contains(zeno::Vector2<int>(15, -5)));
	},
	CASE("Test intersects")
	{
		zeno::Rect<int> rect1 = zeno::Rect<int>(0, 0, 10, 10);
		zeno::Rect<int> rect2 = rect1;
		
		zeno::Rect<int> result = zeno::Rect<int>();
		
		EXPECT(rect1.intersects(rect2, result));
		
		EXPECT(result == zeno::Rect<int>(0, 0, 10, 10));
		
		rect2 = zeno::Rect<int>(10, 10, 10, 10);
		
		EXPECT_NOT(rect1.intersects(rect2, result));
	},
	CASE("Test == operator")
	{
		zeno::Rect<int> rect = zeno::Rect<int>(1, 2, 3, 4);
		
		EXPECT(rect == zeno::Rect<int>(1, 2, 3, 4));
		
		EXPECT_NOT(rect == zeno::Rect<int>(2, 3, 4, 5));
	},
	CASE("Test != operator")
	{
		zeno::Rect<int> rect = zeno::Rect<int>(1, 2, 3, 4);
		
		EXPECT_NOT(rect != zeno::Rect<int>(1, 2, 3, 4));
		
		EXPECT(rect != zeno::Rect<int>(2, 3, 4, 5));
	},
};

const lest::test Mat4x4ClassTest[] = 
{
	CASE("Test default constructor")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4();
		
		EXPECT(mat[0] == 0.0f);
		EXPECT(mat[1] == 0.0f);
		EXPECT(mat[2] == 0.0f);
		EXPECT(mat[3] == 0.0f);
		
		EXPECT(mat[4] == 0.0f);
		EXPECT(mat[5] == 0.0f);
		EXPECT(mat[6] == 0.0f);
		EXPECT(mat[7] == 0.0f);
		
		EXPECT(mat[8] == 0.0f);
		EXPECT(mat[9] == 0.0f);
		EXPECT(mat[10] == 0.0f);
		EXPECT(mat[11] == 0.0f);
		
		EXPECT(mat[12] == 0.0f);
		EXPECT(mat[13] == 0.0f);
		EXPECT(mat[14] == 0.0f);
		EXPECT(mat[15] == 0.0f);
	},
	CASE("Test scalar constructor")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(9.0f);
		
		EXPECT(mat[0] == 9.0f);
		EXPECT(mat[1] == 0.0f);
		EXPECT(mat[2] == 0.0f);
		EXPECT(mat[3] == 0.0f);
		
		EXPECT(mat[4] == 0.0f);
		EXPECT(mat[5] == 9.0f);
		EXPECT(mat[6] == 0.0f);
		EXPECT(mat[7] == 0.0f);
		
		EXPECT(mat[8] == 0.0f);
		EXPECT(mat[9] == 0.0f);
		EXPECT(mat[10] == 9.0f);
		EXPECT(mat[11] == 0.0f);
		
		EXPECT(mat[12] == 0.0f);
		EXPECT(mat[13] == 0.0f);
		EXPECT(mat[14] == 0.0f);
		EXPECT(mat[15] == 9.0f);
	},
	CASE("Test vector constructor")
	{
		zeno::Vector3<float> x(1.0f, 2.0f, 3.0f);
		zeno::Vector3<float> y(4.0f, 5.0f, 6.0f);
		zeno::Vector3<float> z(7.0f, 8.0f, 9.0f);
		
		zeno::Mat4x4 mat = zeno::Mat4x4(x, y, z);
		
		EXPECT(mat[0] == x.x);
		EXPECT(mat[1] == x.y);
		EXPECT(mat[2] == x.z);
		EXPECT(mat[3] == 0.0f);
		
		EXPECT(mat[4] == y.x);
		EXPECT(mat[5] == y.y);
		EXPECT(mat[6] == y.z);
		EXPECT(mat[7] == 0.0f);
		
		EXPECT(mat[8] == z.x);
		EXPECT(mat[9] == z.y);
		EXPECT(mat[10] == z.z);
		EXPECT(mat[11] == 0.0f);
		
		EXPECT(mat[12] == 0.0f);
		EXPECT(mat[13] == 0.0f);
		EXPECT(mat[14] == 0.0f);
		EXPECT(mat[15] == 1.0f);
	},
	CASE("Test 16 value constructor")
	{
		float _0 = 5.0f;
		float _1 = 9.0f;
		float _2 = 7.0f;
		float _3 = 11.0f;
		float _4 = 3.0f;
		float _5 = 13.0f;
		float _6 = 14.0f;
		float _7 = 4.0f;
		float _8 = 15.0f;
		float _9 = 0.0f;
		float _10 = 10.0f;
		float _11 = 6.0f;
		float _12 = 12.0f;
		float _13 = 2.0f;
		float _14 = 1.0f;
		float _15 = 8.0f;
		
		zeno::Mat4x4 mat = zeno::Mat4x4(_0, _4, _8, _12,
										_1, _5, _9, _13,
										_2, _6, _10, _14,
										_3, _7, _11, _15);
										
		EXPECT(mat[0] == _0);
		EXPECT(mat[1] == _1);
		EXPECT(mat[2] == _2);
		EXPECT(mat[3] == _3);
		EXPECT(mat[4] == _4);
		EXPECT(mat[5] == _5);
		EXPECT(mat[6] == _6);
		EXPECT(mat[7] == _7);
		EXPECT(mat[8] == _8);
		EXPECT(mat[9] == _9);
		EXPECT(mat[10] == _10);
		EXPECT(mat[11] == _11);
		EXPECT(mat[12] == _12);
		EXPECT(mat[13] == _13);
		EXPECT(mat[14] == _14);
		EXPECT(mat[15] == _15);
	},
	CASE("Test copy constructor")
	{
		zeno::Mat4x4 mat1 = zeno::Mat4x4(1.5f);
		
		zeno::Mat4x4 mat2 = zeno::Mat4x4();
		
		EXPECT_NOT(mat1 == mat2);
		
		mat2 = mat1;
		
		EXPECT(mat1 == mat2);
	},
	CASE("Test data pointer")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.45f);
		
		const float *data = mat.pointer();
		
		EXPECT(data[0] == 1.45f);
		EXPECT(data[1] == 0.0f);
		EXPECT(data[2] == 0.0f);
		EXPECT(data[3] == 0.0f);
		
		EXPECT(data[4] == 0.0f);
		EXPECT(data[5] == 1.45f);
		EXPECT(data[6] == 0.0f);
		EXPECT(data[7] == 0.0f);
		
		EXPECT(data[8] == 0.0f);
		EXPECT(data[9] == 0.0f);
		EXPECT(data[10] == 1.45f);
		EXPECT(data[11] == 0.0f);
		
		EXPECT(data[12] == 0.0f);
		EXPECT(data[13] == 0.0f);
		EXPECT(data[14] == 0.0f);
		EXPECT(data[15] == 1.45f);
	},
	CASE("Test transpose method")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.45f);
		
		EXPECT(mat.transpose() == zeno::Mat4x4(1.45f));
		
		mat[8] = 60.0f;
		
		mat.transpose();
		
		EXPECT(mat[2] == 60.0f);
	},
	CASE("Test inverse method")
	{
		zeno::Vector3<float> x = zeno::Vector3<float>(1.0f, 2.0f, 3.0f);
		zeno::Vector3<float> y = zeno::Vector3<float>(8.0f, 2.0f, -5.0f);
		zeno::Vector3<float> z = zeno::Vector3<float>(1.0f, -2.0f, 3.0f);
		zeno::Mat4x4 mat = zeno::Mat4x4(x, y, z);
		
		zeno::Mat4x4 mat2 = mat;
		
		mat.inverse();
		
		zeno::Mat4x4 id = mat * mat2;
		
		for (unsigned int i = 0; i < 16; i += 1)
		{
			EXPECT(id[i] == lest::approx(zeno::Mat4x4(1.0f)[i]));
		}
	},
	CASE("Test Orthographic2D method")
	{
		zeno::Vector2f size = zeno::Vector2f(1920.0f, 1080.0f);
		
		zeno::Vector3f posTL = zeno::Vector3f(-1.0f, 1.0f, 0.0f);
		zeno::Vector3f posTR = zeno::Vector3f(1.0f, 1.0f, 0.0f);
		zeno::Vector3f posBL = zeno::Vector3f(-1.0f, -1.0f, 0.0f);
		zeno::Vector3f posBR = zeno::Vector3f(1.0f, -1.0f, 0.0f);
		
		zeno::Mat4x4 mat = zeno::Mat4x4::Orthographic2D(0.0f, size.x, size.y, 0.0f);
		
		EXPECT(zeno::Vector3f(0.0f, 	1080.0f, 	0.0f) 	== (mat * posTL));
		EXPECT(zeno::Vector3f(1920.0f, 	1080.0f, 	0.0f) 	== (mat * posTR));
		EXPECT(zeno::Vector3f(0.0f, 	0.0f, 		0.0f) 	== (mat * posBL));
		EXPECT(zeno::Vector3f(1920.0f, 	0.0f, 		0.0f) 	== (mat * posBR));
	},
	CASE("Test Orthographic3D method")
	{
		EXPECT(0.0f == 0.0f);
	},
	CASE("Test lookat method")
	{
		EXPECT(0.0f == 0.0f);
	},
	CASE("Test persepective method")
	{
		EXPECT(0.0f == 0.0f);
	},
	CASE("Test = operator")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.45f);
		
		zeno::Mat4x4 mat2;
		
		mat = mat2;
		
		EXPECT(mat == mat2);
	},
	CASE("Test == operator")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.23f);
		
		zeno::Mat4x4 mat2 = zeno::Mat4x4(1.22f);
		
		EXPECT_NOT(mat == mat2);
		
		mat2 = mat;
		
		EXPECT(mat == mat2);
	},
	CASE("Test != operator")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.23f);
		
		zeno::Mat4x4 mat2 = zeno::Mat4x4(1.22f);
		
		EXPECT(mat != mat2);
		
		mat2 = mat;
		
		EXPECT_NOT(mat != mat2);
	},
	CASE("Test Mat4x4 * Vector4 operation")
	{
		zeno::Vector4f vec 	= zeno::Vector4f(1.0f, 2.0f, 3.0f, 0.0f);
		zeno::Mat4x4 mat	= zeno::Mat4x4(1.0f);
		
		EXPECT(vec == (mat * vec));
		
		mat[0] = 2.0f;
		mat[5] = 2.0f;
		mat[10]= 2.0f;
		
		EXPECT((vec * 2.0f) == (mat * vec));
	},
	CASE("Test Mat4x4 * Vector3 operation")
	{
		zeno::Mat4x4 mat	=	zeno::Mat4x4(1.0f);
		zeno::Vector3f vec	=	zeno::Vector3f(10.0f, 20.0f, 30.0f);
		
		EXPECT(vec == (mat * vec));
		
		mat[0] = 2.0f;
		mat[5] = 2.0f;
		mat[10]= 2.0f;
		
		EXPECT((vec * 2.0f) == (mat * vec));
	},
	CASE("Test Mat4x4 * Mat4x4 operation")
	{
		zeno::Mat4x4 mat1	=	zeno::Mat4x4(1.0f);
		zeno::Mat4x4 mat2	=	zeno::Mat4x4(1.0f);
		
		EXPECT(zeno::Mat4x4(1.0f) == (mat1 * mat2));
		
		mat2[3] = 6.3f;
		mat2[9] = 2.1f;
		
		EXPECT(mat2 == (mat1 * mat2));
	},
	
	
	
};



int main(int argc, char** argv)
{
    int ret = 0;
	
	zeno::Clock clock;
	zeno::Clock totalClock;
	
	
	std::cout << "Time Class Test beginning" << std::endl;
	ret = lest::run(TimeClassTest);
	if (ret != 0)
	{
		return ret;
	}
	std::cout << "Time Class Test completed successfully: " << clock.restart() << std::endl;
	
	std::cout << "Vector2 Class Test beginning" << std::endl;
	ret = lest::run(Vector2Test);
	if (ret != 0)
	{
		return ret;
	}
	std::cout << "Vector2 Class Test completed successfully: " << clock.restart() << std::endl;
	
	std::cout << "Vector3 Class Test beginning" << std::endl;
	ret = lest::run(Vector3Test);
	if (ret != 0)
	{
		return ret;
	}
	std::cout << "Vector3 Class Test completed successfully: " << clock.restart() << std::endl;
	
	std::cout << "Vector4 Class Test beginning" << std::endl;
	ret = lest::run(Vector4Test);
	if (ret != 0)
	{
		return ret;
	}
	std::cout << "Vector4 Class Test completed successfully: " << clock.restart() << std::endl;
	
	std::cout << "Colour Class Test beginning" << std::endl;
	ret = lest::run(ColourClassTest);
	if (ret != 0)
	{
		return ret;
	}
	std::cout << "Colour Class Test completed successfully: " << clock.restart() << std::endl;
	
	std::cout << "Rect Class Test beginning" << std::endl;
	ret = lest::run(RectClassTest);
	if (ret != 0)
	{
		return ret;
	}
	std::cout << "Rect Class Test completed successfully: " << clock.restart() << std::endl;
	
	std::cout << "Mat4x4 Class Test beginning" << std::endl;
	ret = lest::run(Mat4x4ClassTest);
	if (ret != 0)
	{
		return ret;
	}
	std::cout << "Mat4x4 Class Test completed successfully: " << clock.restart() << std::endl;
	
	
	std::cout << "All Tests completed successfully: " << totalClock.restart().asMicroseconds() << " us" << std::endl;
	return ret;
}
*/
