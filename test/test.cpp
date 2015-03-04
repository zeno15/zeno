#include <iostream>
#include <cstdlib>
#include <cmath>

//~ https://github.com/philsquared/Catch
#include <catch.hpp>

#include <Clock.hpp>
#include <Colour.hpp>
#include <Mat4x4.hpp>
#include <Rect.hpp>
#include <Time.hpp>
#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>
#include <Keyboard.hpp>
#include <Window.hpp>

#include <GL/glew.h>


/*	Macros

	INFO(expression)		-	Logging

	REQUIRE(expression)		-	Returns on failure
	CHECK(expression)		-	Continues on failure

	REQUIRE_FALSE(expression)
	CHECK_FALSE(expression)

	REQUIRE_THROW_AS(expression, exception type)
	CHECK_THROW_AS(expression, exception type)

	REQUIRE_NOTHROW(expression)
	CHECK_NOTHROW(expression)
*/

TEST_CASE("Colour Test", "[Colour]" )
{
	SECTION("Test default constructor")
	{
		zeno::Colour col = zeno::Colour();
		
		REQUIRE((col.r == 0.0f &&
				col.g == 0.0f &&
				col.b == 0.0f &&
				col.a == 1.0f));
	}
	SECTION("Test non-default constructor")
	{
		float r = 0.2f;
		float g = 0.4f;
		float b = 0.6f;
		float a = 0.8f;
		zeno::Colour col = zeno::Colour(r, g, b, a);
		
		REQUIRE((col.r == r &&
				col.g == g &&
				col.b == b &&
				col.a == a));
	}
	SECTION("Test Black zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Black;
		
		REQUIRE(col == zeno::Colour(0.0f, 0.0f, 0.0f, 1.0f));
	}
	SECTION("Test White zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::White;
		
		REQUIRE(col == zeno::Colour(1.0f, 1.0f, 1.0f));
	}
	SECTION("Test Red zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Red;
		
		REQUIRE(col == zeno::Colour(1.0f, 0.0f, 0.0f));
	}
	SECTION("Test Green zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Green;
		
		REQUIRE(col == zeno::Colour(0.0f, 1.0f, 0.0f));
	}
	SECTION("Test Blue zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Blue;
		
		REQUIRE(col == zeno::Colour(0.0f, 0.0f, 1.0f));
	}
	SECTION("Test Yellow zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Yellow;
		
		REQUIRE(col == zeno::Colour(1.0f, 1.0f, 0.0f));
	}
	SECTION("Test Magenta zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Magenta;
		
		REQUIRE(col == zeno::Colour(1.0f, 0.0f, 1.0f));
	}
	SECTION("Test Cyan zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Cyan;
		
		REQUIRE(col == zeno::Colour(0.0f, 1.0f, 1.0f));
	}
	SECTION("Test Transparent zeno::Colour")
	{
		zeno::Colour col = zeno::Colour::Transparent;
		
		REQUIRE(col == zeno::Colour(0.0f, 0.0f, 0.0f, 0.0f));
	}
	SECTION("Test == operator")
	{
		float r = 0.2f;
		float g = 0.4f;
		float b = 0.6f;
		float a = 0.8f;
		zeno::Colour col = zeno::Colour(r, g, b, a);
		
		REQUIRE(col == zeno::Colour(r, g, b, a));
		
		REQUIRE_FALSE(col == zeno::Colour(a, b, g, r));
	}
	SECTION("Test != operator")
	{
		float r = 0.2f;
		float g = 0.4f;
		float b = 0.6f;
		float a = 0.8f;
		zeno::Colour col = zeno::Colour(r, g, b, a);
		
		REQUIRE_FALSE(col != zeno::Colour(r, g, b, a));
		
		REQUIRE(col != zeno::Colour(a, b, g, r));
	}
	SECTION("Test + operator")
	{
		zeno::Colour red = zeno::Colour::Red;
		zeno::Colour green = zeno::Colour::Green;
		
		REQUIRE((red + green) == zeno::Colour::Yellow);
		
		REQUIRE((red + red) == zeno::Colour::Red);
	}
	SECTION("Test += operator")
	{
		zeno::Colour col = zeno::Colour::Red;
		
		col += zeno::Colour::Green;
		
		REQUIRE(col == zeno::Colour::Yellow);
	}
	SECTION("Test - operator")
	{
		zeno::Colour yellow = zeno::Colour::Yellow;
		zeno::Colour red = zeno::Colour::Red;
		
		REQUIRE((yellow - red) == zeno::Colour::Green);
		
		REQUIRE((yellow - yellow) == zeno::Colour::Black);
	}
	SECTION("Test -= operator")
	{
		zeno::Colour col = zeno::Colour::Red;
		
		col -= zeno::Colour::Red;
		
		REQUIRE(col == zeno::Colour::Black);
	}
	SECTION("Test * operator (float)")
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		
		float val = 0.5f;
		
		zeno::Colour col = zeno::Colour(r, g, b);
		
		REQUIRE((col * val) == zeno::Colour(r * val, g * val, b * val));
	}
	SECTION("Test * operator (Colour)")
	{
		zeno::Colour red = zeno::Colour::Red;
		zeno::Colour white = zeno::Colour::White;
		
		REQUIRE((red * white) == zeno::Colour::Red);
	}
	SECTION("Test *= operator (float)")
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		
		float val = 0.5f;
		
		zeno::Colour col = zeno::Colour(r, g, b);
		
		col *= val;
		
		REQUIRE(col == zeno::Colour(r * val, g * val, b * val));
	}
	SECTION("Test *= operator (Colour)")
	{
		zeno::Colour red = zeno::Colour::Red;
		zeno::Colour white = zeno::Colour::White;
		
		red *= white;
		
		REQUIRE(red == zeno::Colour::Red);
	}
}

TEST_CASE("Mat4x4 Test", "[Mat4x4]")
{
	SECTION("Test default constructor")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4();
		
		REQUIRE(mat[0] == 0.0f);
		REQUIRE(mat[1] == 0.0f);
		REQUIRE(mat[2] == 0.0f);
		REQUIRE(mat[3] == 0.0f);
		
		REQUIRE(mat[4] == 0.0f);
		REQUIRE(mat[5] == 0.0f);
		REQUIRE(mat[6] == 0.0f);
		REQUIRE(mat[7] == 0.0f);
		
		REQUIRE(mat[8] == 0.0f);
		REQUIRE(mat[9] == 0.0f);
		REQUIRE(mat[10] == 0.0f);
		REQUIRE(mat[11] == 0.0f);
		
		REQUIRE(mat[12] == 0.0f);
		REQUIRE(mat[13] == 0.0f);
		REQUIRE(mat[14] == 0.0f);
		REQUIRE(mat[15] == 0.0f);
	}
	SECTION("Test scalar constructor")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(9.0f);
		
		REQUIRE(mat[0] == 9.0f);
		REQUIRE(mat[1] == 0.0f);
		REQUIRE(mat[2] == 0.0f);
		REQUIRE(mat[3] == 0.0f);
		
		REQUIRE(mat[4] == 0.0f);
		REQUIRE(mat[5] == 9.0f);
		REQUIRE(mat[6] == 0.0f);
		REQUIRE(mat[7] == 0.0f);
		
		REQUIRE(mat[8] == 0.0f);
		REQUIRE(mat[9] == 0.0f);
		REQUIRE(mat[10] == 9.0f);
		REQUIRE(mat[11] == 0.0f);
		
		REQUIRE(mat[12] == 0.0f);
		REQUIRE(mat[13] == 0.0f);
		REQUIRE(mat[14] == 0.0f);
		REQUIRE(mat[15] == 9.0f);
	}
	SECTION("Test vector constructor")
	{
		zeno::Vector3<float> x(1.0f, 2.0f, 3.0f);
		zeno::Vector3<float> y(4.0f, 5.0f, 6.0f);
		zeno::Vector3<float> z(7.0f, 8.0f, 9.0f);
		
		zeno::Mat4x4 mat = zeno::Mat4x4(x, y, z);
		
		REQUIRE(mat[0] == x.x);
		REQUIRE(mat[1] == x.y);
		REQUIRE(mat[2] == x.z);
		REQUIRE(mat[3] == 0.0f);
		
		REQUIRE(mat[4] == y.x);
		REQUIRE(mat[5] == y.y);
		REQUIRE(mat[6] == y.z);
		REQUIRE(mat[7] == 0.0f);
		
		REQUIRE(mat[8] == z.x);
		REQUIRE(mat[9] == z.y);
		REQUIRE(mat[10] == z.z);
		REQUIRE(mat[11] == 0.0f);
		
		REQUIRE(mat[12] == 0.0f);
		REQUIRE(mat[13] == 0.0f);
		REQUIRE(mat[14] == 0.0f);
		REQUIRE(mat[15] == 1.0f);
	}
	SECTION("Test 16 value constructor")
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
										
		REQUIRE(mat[0] == _0);
		REQUIRE(mat[1] == _1);
		REQUIRE(mat[2] == _2);
		REQUIRE(mat[3] == _3);
		REQUIRE(mat[4] == _4);
		REQUIRE(mat[5] == _5);
		REQUIRE(mat[6] == _6);
		REQUIRE(mat[7] == _7);
		REQUIRE(mat[8] == _8);
		REQUIRE(mat[9] == _9);
		REQUIRE(mat[10] == _10);
		REQUIRE(mat[11] == _11);
		REQUIRE(mat[12] == _12);
		REQUIRE(mat[13] == _13);
		REQUIRE(mat[14] == _14);
		REQUIRE(mat[15] == _15);
	}
	SECTION("Test copy constructor")
	{
		zeno::Mat4x4 mat1 = zeno::Mat4x4(1.5f);
		
		zeno::Mat4x4 mat2 = zeno::Mat4x4();
		
		REQUIRE_FALSE(mat1 == mat2);
		
		mat2 = mat1;
		
		REQUIRE(mat1 == mat2);
	}
	SECTION("Test data pointer")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.45f);
		
		const float *data = mat.pointer();
		
		REQUIRE(data[0] == 1.45f);
		REQUIRE(data[1] == 0.0f);
		REQUIRE(data[2] == 0.0f);
		REQUIRE(data[3] == 0.0f);
		
		REQUIRE(data[4] == 0.0f);
		REQUIRE(data[5] == 1.45f);
		REQUIRE(data[6] == 0.0f);
		REQUIRE(data[7] == 0.0f);
		
		REQUIRE(data[8] == 0.0f);
		REQUIRE(data[9] == 0.0f);
		REQUIRE(data[10] == 1.45f);
		REQUIRE(data[11] == 0.0f);
		
		REQUIRE(data[12] == 0.0f);
		REQUIRE(data[13] == 0.0f);
		REQUIRE(data[14] == 0.0f);
		REQUIRE(data[15] == 1.45f);
	}
	SECTION("Test transpose method")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.45f);
		
		REQUIRE(mat.transpose() == zeno::Mat4x4(1.45f));
		
		mat[8] = 60.0f;
		
		mat.transpose();
		
		REQUIRE(mat[2] == 60.0f);
	}
	SECTION("Test inverse method")
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
			REQUIRE(fabsf(id[i] - zeno::Mat4x4(1.0f)[i]) < 0.001f);
		}
	}
	SECTION("Test Orthographic2D method")
	{
		zeno::Vector2f size = zeno::Vector2f(1920.0f, 1080.0f);
		
		zeno::Vector3f posTL = zeno::Vector3f(0.0f,		size.y,		0.0f);
		zeno::Vector3f posTR = zeno::Vector3f(size.x,	size.y,		0.0f);
		zeno::Vector3f posBL = zeno::Vector3f(0.0f,		0.0f,		0.0f);
		zeno::Vector3f posBR = zeno::Vector3f(size.x,	0.0f,		0.0f);
		

		zeno::Mat4x4 mat = zeno::Mat4x4::Orthographic2D(0.0f, size.x, size.y, 0.0f);

		REQUIRE(zeno::Vector3f(-1.0f, 	+1.0f, 	0.0f) 	== (mat * posTL));
		REQUIRE(zeno::Vector3f(+1.0f, 	+1.0f, 	0.0f) 	== (mat * posTR));
		REQUIRE(zeno::Vector3f(-1.0f, 	-1.0f, 	0.0f) 	== (mat * posBL));
		REQUIRE(zeno::Vector3f(+1.0f, 	-1.0f, 	0.0f) 	== (mat * posBR));
	}
	SECTION("Test Orthographic3D method")
	{
		zeno::Vector3f size = zeno::Vector3f(1920.0f, 1080.0f, 100.0f);

		zeno::Vector3f posTLF = zeno::Vector3f(0.0f,	size.y,	size.z);
		zeno::Vector3f posTRF = zeno::Vector3f(size.x,	size.y,	size.z);
		zeno::Vector3f posBRF = zeno::Vector3f(size.x,	0.0f,	size.z);
		zeno::Vector3f posBLF = zeno::Vector3f(0.0f,	0.0f,	size.z);

		zeno::Vector3f posTLB = zeno::Vector3f(0.0f,	size.y,	size.z * 2.0f);
		zeno::Vector3f posTRB = zeno::Vector3f(size.x,	size.y,	size.z * 2.0f);
		zeno::Vector3f posBRB = zeno::Vector3f(size.x,	0.0f,	size.z * 2.0f);
		zeno::Vector3f posBLB = zeno::Vector3f(0.0f,	0.0f,	size.z * 2.0f);


		zeno::Mat4x4 mat = zeno::Mat4x4::Orthographic3D(0.0f, size.x, size.y, 0.0f, size.z, size.z * 2.0f);

		REQUIRE(zeno::Vector3f(-1.0f, +1.0f, -1.0f) == (mat * posTLF));
		REQUIRE(zeno::Vector3f(+1.0f, +1.0f, -1.0f) == (mat * posTRF));
		REQUIRE(zeno::Vector3f(+1.0f, -1.0f, -1.0f) == (mat * posBRF));
		REQUIRE(zeno::Vector3f(-1.0f, -1.0f, -1.0f) == (mat * posBLF));


		REQUIRE(zeno::Vector3f(-1.0f, +1.0f, +1.0f) == (mat * posTLB));
		REQUIRE(zeno::Vector3f(+1.0f, +1.0f, +1.0f) == (mat * posTRB));
		REQUIRE(zeno::Vector3f(+1.0f, -1.0f, +1.0f) == (mat * posBRB));
		REQUIRE(zeno::Vector3f(-1.0f, -1.0f, +1.0f) == (mat * posBLB));
	}
	SECTION("Test lookat method")
	{
		REQUIRE(0.0f == 0.0f);
	}
	SECTION("Test persepective method")
	{
		REQUIRE(0.0f == 0.0f);
	}
	SECTION("Test = operator")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.45f);
		
		zeno::Mat4x4 mat2;
		
		mat = mat2;
		
		REQUIRE(mat == mat2);
	}
	SECTION("Test == operator")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.23f);
		
		zeno::Mat4x4 mat2 = zeno::Mat4x4(1.22f);
		
		REQUIRE_FALSE(mat == mat2);
		
		mat2 = mat;
		
		REQUIRE(mat == mat2);
	}
	SECTION("Test != operator")
	{
		zeno::Mat4x4 mat = zeno::Mat4x4(1.23f);
		
		zeno::Mat4x4 mat2 = zeno::Mat4x4(1.22f);
		
		REQUIRE(mat != mat2);
		
		mat2 = mat;
		
		REQUIRE_FALSE(mat != mat2);
	}
	SECTION("Test Mat4x4 * Vector4 operation")
	{
		zeno::Vector4f vec 	= zeno::Vector4f(1.0f, 2.0f, 3.0f, 0.0f);
		zeno::Mat4x4 mat	= zeno::Mat4x4(1.0f);
		
		REQUIRE(vec == (mat * vec));
		
		mat[0] = 2.0f;
		mat[5] = 2.0f;
		mat[10]= 2.0f;
		
		REQUIRE((vec * 2.0f) == (mat * vec));
	}
	SECTION("Test Mat4x4 * Vector3 operation")
	{
		zeno::Mat4x4 mat	=	zeno::Mat4x4(1.0f);
		zeno::Vector3f vec	=	zeno::Vector3f(10.0f, 20.0f, 30.0f);
		
		REQUIRE(vec == (mat * vec));
		
		mat[0] = 2.0f;
		mat[5] = 2.0f;
		mat[10]= 2.0f;
		
		REQUIRE((vec * 2.0f) == (mat * vec));

		mat = zeno::Mat4x4(1.0f);

		mat[12] = -1.0f;		//~ Translate left by one unit

		REQUIRE((vec - zeno::Vector3f(1.0f, 0.0f, 0.0f)) == (mat * vec));
	}
	SECTION("Test Mat4x4 * Mat4x4 operation")
	{
		zeno::Mat4x4 mat1	=	zeno::Mat4x4(1.0f);
		zeno::Mat4x4 mat2	=	zeno::Mat4x4(1.0f);
		
		REQUIRE(zeno::Mat4x4(1.0f) == (mat1 * mat2));
		
		mat2[3] = 6.3f;
		mat2[9] = 2.1f;
		
		REQUIRE(mat2 == (mat1 * mat2));
	}
}

TEST_CASE("Time Test", "[Time]")
{
	SECTION("Test time default constructor gives 0 initial value")
    {
		zeno::Time t = zeno::Time();
		
        REQUIRE(t.asMicroseconds() == 0);
    }
	SECTION("Test non default seconds constructor works as REQUIREed")
	{
		zeno::Time t = zeno::Time::seconds(1.0f);
		
		REQUIRE(t.asSeconds() == 1.0f);
		REQUIRE(t.asMilliseconds() == 1000);
		REQUIRE(t.asMicroseconds() == 1000000);
	}
	SECTION("Test non default milliseconds constructor works as REQUIREed")
	{
		zeno::Time t = zeno::Time::milliseconds(1000);
		
		REQUIRE(t.asSeconds() == 1.0f);
		REQUIRE(t.asMilliseconds() == 1000);
		REQUIRE(t.asMicroseconds() == 1000000);
	}
	SECTION("Test non default microseconds constructor works as REQUIREed")
	{
		zeno::Time t = zeno::Time::microseconds(1000000);
		
		REQUIRE(t.asSeconds() == 1.0f);
		REQUIRE(t.asMilliseconds() == 1000);
		REQUIRE(t.asMicroseconds() == 1000000);
	}
	SECTION("Test == operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		REQUIRE(t1 == t2);
		
		t1 = zeno::Time::microseconds(1000);
		t2 = zeno::Time::milliseconds(1);
		REQUIRE(t1 == t2);
		
		t1 = zeno::Time::seconds(12.0f);
		REQUIRE_FALSE(t1 == t2);
	}
	SECTION("Test != operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		REQUIRE_FALSE(t1 != t2);
		
		t1 = zeno::Time::seconds(10.0f);
		REQUIRE(t1 != t2);
	}
	SECTION("Test > operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		REQUIRE_FALSE(t1 > t2);
		
		t1 = zeno::Time::microseconds(100);
		REQUIRE(t1 > t2);
		REQUIRE_FALSE(t2 > t1);
	}
	SECTION("Test >= operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		REQUIRE(t1 >= t2);
		REQUIRE(t2 >= t1);
		
		t1 = zeno::Time::microseconds(10);
		REQUIRE(t1 >= t2);
		REQUIRE_FALSE(t2 >= t1);
	}
	SECTION("Test < operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		REQUIRE_FALSE(t1 < t2);
		
		t1 = zeno::Time::microseconds(10);
		REQUIRE(t2 < t1);
		REQUIRE_FALSE(t1 < t2);
	}
	SECTION("Test <= operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		REQUIRE(t1 <= t2);
		REQUIRE(t2 <= t1);
		
		t1 = zeno::Time::microseconds(10);
		REQUIRE(t2 <= t1);
		REQUIRE_FALSE(t1 <= t2);
	}
	SECTION("Test -(negate) operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		REQUIRE(t1.asMicroseconds() == 1);
		
		t1 = - t1;
		REQUIRE(t1.asMicroseconds() == -1);		
	}
	SECTION("Test - operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		zeno::Time res = t1 - t2;
		REQUIRE(res == zeno::Time::microseconds(0));
		
		t2 = zeno::Time::microseconds(10);
		res = t1 - t2;
		REQUIRE(res == zeno::Time::microseconds(-9));
	}
	SECTION("Test -= operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		t1 -= t2;
		REQUIRE(t1.asMicroseconds() == 0);
		
		t1 -= t2;
		REQUIRE(t1.asMicroseconds() == -1);
	}
	SECTION("Test + operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		zeno::Time res = t1 + t2;
		REQUIRE(res == zeno::Time::microseconds(2));
		
		t1 = zeno::Time::microseconds(-5);
		res = t1 + t2;
		REQUIRE(res == zeno::Time::microseconds(-4));
	}
	SECTION("Test += operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		t1 += t2;
		REQUIRE(t1 == zeno::Time::microseconds(2));
		
		t2 = zeno::Time::microseconds(-5);
		t1 += t2;
		REQUIRE(t1 == zeno::Time::microseconds(-3));
	}
	SECTION("Test / operator")
	{
		zeno::Time t1 = zeno::Time::seconds(1.0f);
		zeno::Time t2 = zeno::Time::seconds(0.5f);
		float tf = 0.1f;
		long long tll = 1000000;
		
		
		REQUIRE((t1 / t2) == 2.0f);
		
		REQUIRE((t1 / tf) == zeno::Time::seconds(10.0f));
		
		REQUIRE((t1 / tll) == zeno::Time::microseconds(1));
	}
	SECTION("Test /= operator")
	{
		zeno::Time t1 = zeno::Time::seconds(100);
		zeno::Time t2 = zeno::Time::microseconds(100);
		
		t1 /= 4.0f;
		REQUIRE(t1 == zeno::Time::seconds(25.0f));
		
		t2 /= 20ll;
		REQUIRE(t2 == zeno::Time::microseconds(5));
	}
	SECTION("Test * operator")
	{
		zeno::Time t1 = zeno::Time::seconds(10);
		zeno::Time t2 = zeno::Time::microseconds(10);
		
		zeno::Time res = t1 * 3.0f;
		REQUIRE(res == zeno::Time::seconds(30.0f));
		
		res = t2 * 3ll;
		REQUIRE(res == zeno::Time::microseconds(30));
		
		res = 3.0f * t1;
		REQUIRE(res == zeno::Time::seconds(30.0f));
		
		res = 3ll * t2;
		REQUIRE(res == zeno::Time::microseconds(30));
	}
	SECTION("Test *= operator")
	{
		zeno::Time t1 = zeno::Time::seconds(1);
		zeno::Time t2 = zeno::Time::microseconds(1);
		
		t1 *= 100.0f;
		REQUIRE(t1 == zeno::Time::seconds(100.0f));
		
		t2 *= 1023ll;
		REQUIRE(t2 == zeno::Time::microseconds(1023));
	}
	SECTION("Test % operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(10);
		zeno::Time t2 = zeno::Time::microseconds(4);
		
		zeno::Time res = t1 % t2;
		REQUIRE(res == zeno::Time::microseconds(2));
		
		t2 = zeno::Time::microseconds(5);
		res = t1 % t2;
		REQUIRE(res == zeno::Time::microseconds(0));
	}
	SECTION("Test %= operator")
	{
		zeno::Time t1 = zeno::Time::microseconds(10);
		zeno::Time t2 = zeno::Time::microseconds(10);
		
		t1 %= t2;
		REQUIRE(t1 == zeno::Time::microseconds(0));
		
		t1 = zeno::Time::microseconds(10);
		t2 = zeno::Time::microseconds(4);
		t1 %= t2;
		REQUIRE(t1 == zeno::Time::microseconds(2));
	}
	
}

TEST_CASE("Rect Test", "[Rect]")
{
	SECTION("Test default constructor")
	{
		zeno::Rect<int> rect = zeno::Rect<int>();
		
		REQUIRE((rect.left == 0 &&
				rect.bot == 0 &&
				rect.width == 0 &&
				rect.height ==0));
	}
	SECTION("Test non-default constructor")
	{
		int l = 1;
		int b = 2;
		int w = 5;
		int h = 6;
		
		zeno::Rect<int> rect = zeno::Rect<int>(l, b, w, h);
		
		REQUIRE((rect.left 		== l 	&&
				rect.bot 		== b 	&&
				rect.width 		== w 	&&
				rect.height 	== h));
	}
	SECTION("Test copy constructor")
	{
		int l = 1;
		int b = 2;
		int w = 5;
		int h = 6;
		
		zeno::Rect<int> recti = zeno::Rect<int>(l, b, w, h);
		
		zeno::Rect<float> rectf = zeno::Rect<float>(recti);
		
		REQUIRE((rectf.left 	== static_cast<float>(recti.left) 	&&
				rectf.bot 		== static_cast<float>(recti.bot) 	&&
				rectf.width 	== static_cast<float>(recti.width) 	&&
				rectf.height 	== static_cast<float>(recti.height)));
	}
	SECTION("Test contains")
	{
		zeno::Rect<int> rect = zeno::Rect<int>(0, 0, 10, 10);
		
		REQUIRE(rect.contains(5, 5));
		REQUIRE(rect.contains(zeno::Vector2<int>(5, 5)));
		
		REQUIRE_FALSE(rect.contains(-5, 15));
		REQUIRE_FALSE(rect.contains(zeno::Vector2<int>(15, -5)));
	}
	SECTION("Test intersects")
	{
		zeno::Rect<int> rect1 = zeno::Rect<int>(0, 0, 10, 10);
		zeno::Rect<int> rect2 = rect1;
		
		zeno::Rect<int> result = zeno::Rect<int>();
		
		REQUIRE(rect1.intersects(rect2, result));
		
		REQUIRE(result == zeno::Rect<int>(0, 0, 10, 10));
		
		rect2 = zeno::Rect<int>(10, 10, 10, 10);
		
		REQUIRE_FALSE(rect1.intersects(rect2, result));
	}
	SECTION("Test == operator")
	{
		zeno::Rect<int> rect = zeno::Rect<int>(1, 2, 3, 4);
		
		REQUIRE(rect == zeno::Rect<int>(1, 2, 3, 4));
		
		REQUIRE_FALSE(rect == zeno::Rect<int>(2, 3, 4, 5));
	}
	SECTION("Test != operator")
	{
		zeno::Rect<int> rect = zeno::Rect<int>(1, 2, 3, 4);
		
		REQUIRE_FALSE(rect != zeno::Rect<int>(1, 2, 3, 4));
		
		REQUIRE(rect != zeno::Rect<int>(2, 3, 4, 5));
	}
}

TEST_CASE("Vector2 Test", "[Vector2]")
{
	SECTION("Test default constructor")
	{
		zeno::Vector2<float> vec = zeno::Vector2<float>();
		
		REQUIRE(vec.x == 0.0f);
		REQUIRE(vec.y == 0.0f);
	}
	SECTION("Test non-default constructor")
	{
		float x = 1.0f;
		float y = 12.0f;
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		
		REQUIRE(vec.x == x);
		REQUIRE(vec.y == y);
	}
	SECTION("Test copy constructor from same type")
	{
		float x = 1.2f;
		float y = 12.2f;
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		zeno::Vector2<float> cpy = zeno::Vector2<float>(vec);
		
		REQUIRE(cpy == vec);
	}
	SECTION("Test copy constructor from different type")
	{
		int x = 12;
		int y = 453;
		zeno::Vector2<int> vec = zeno::Vector2<int>(x, y);
		zeno::Vector2<float> cpy = zeno::Vector2<float>(vec);
		
		REQUIRE(cpy.x == static_cast<float>(x));
		REQUIRE(cpy.y == static_cast<float>(y));
	}
	SECTION("Test -(negate) operator")
	{
		float x = 12.3f;
		float y = -123.7f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec = - vec;
		
		REQUIRE(vec.x == -x);
		REQUIRE(vec.y == -y);
	}
	SECTION("TEST - operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		
		zeno::Vector2<float> res = zeno::Vector2<float>(x, y) - zeno::Vector2<float>(x, y);
		
		REQUIRE(res == zeno::Vector2<float>(0.0f, 0.0f));
	}
	SECTION("Test -= operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		
		zeno::Vector2<float> res = zeno::Vector2<float>(x, y);
		
		res -= zeno::Vector2<float>(x, y);
		
		REQUIRE(res == zeno::Vector2<float>(0.0f, 0.0f));
	}
	SECTION("Test + operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		
		zeno::Vector2<float> res = zeno::Vector2<float>(x, y) + zeno::Vector2<float>(x, y);
		
		REQUIRE(res == zeno::Vector2<float>(2.0f * x, 2.0f * y));
	}
	SECTION("Test += operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		
		zeno::Vector2<float> res = zeno::Vector2<float>(x, y);
		res += res;
		
		REQUIRE(res == zeno::Vector2<float>(2.0f * x, 2.0f * y));
	}	
	SECTION("Test / operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float div = 7.4f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec = vec / div;
		
		REQUIRE(vec == zeno::Vector2<float>(x / div, y / div));
	}
	SECTION("Test /= operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float div = 7.4f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec /= div;
		
		REQUIRE(vec == zeno::Vector2<float>(x / div, y / div));
	}
	SECTION("Test * operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float mul = 2.1f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec = vec * mul;
		
		REQUIRE(vec == zeno::Vector2<float>(x * mul, y * mul));
		
		
		vec = zeno::Vector2<float>(x, y);
		vec = mul * vec;
		
		REQUIRE(vec == zeno::Vector2<float>(x * mul, y * mul));
	}
	SECTION("Test *= operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float mul = 2.1f;
		
		zeno::Vector2<float> vec = zeno::Vector2<float>(x, y);
		vec *= mul;
		
		REQUIRE(vec == zeno::Vector2<float>(x * mul, y * mul));
	}	
	SECTION("Test == operator")
	{
		zeno::Vector2<float> vec1 = zeno::Vector2<float>(123.4f, 11.0f);
		zeno::Vector2<float> vec2 = zeno::Vector2<float>(13.4f, 1121.0f);
		
		REQUIRE_FALSE(vec1 == vec2);
		
		vec2 = vec1;
		REQUIRE(vec1 == vec2);
	}
	SECTION("Test != operator")
	{
		zeno::Vector2<float> vec1 = zeno::Vector2<float>(123.4f, 11.0f);
		zeno::Vector2<float> vec2 = zeno::Vector2<float>(13.4f, 1121.0f);
		
		REQUIRE(vec1 != vec2);
		
		vec2 = vec1;
		REQUIRE_FALSE(vec1 != vec2);
	}
}

TEST_CASE("Vector3 Test", "[Vector3]")
{
	SECTION("Test default constructor")
	{
		zeno::Vector3<float> vec = zeno::Vector3<float>();
		
		REQUIRE(vec.x == 0.0f);
		REQUIRE(vec.y == 0.0f);
		REQUIRE(vec.z == 0.0f);
	}
	SECTION("Test non-default constructor")
	{
		float x = 1.0f;
		float y = 12.0f;
		float z = -12.8f;
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		
		REQUIRE(vec.x == x);
		REQUIRE(vec.y == y);
		REQUIRE(vec.z == z);
	}
	SECTION("Test copy constructor from same type")
	{
		float x = 1.2f;
		float y = 12.2f;
		float z = -12.8f;
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		zeno::Vector3<float> cpy = zeno::Vector3<float>(vec);
		
		REQUIRE(cpy == vec);
	}
	SECTION("Test copy constructor from different type")
	{
		int x = 12;
		int y = 453;
		int z = -18;
		zeno::Vector3<int> vec = zeno::Vector3<int>(x, y, z);
		zeno::Vector3<float> cpy = zeno::Vector3<float>(vec);
		
		REQUIRE(cpy == zeno::Vector3<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
	}
	SECTION("Test -(negate) operator")
	{
		float x = 12.3f;
		float y = -123.7f;
		float z = 88.1f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec = - vec;
		
		REQUIRE(vec == zeno::Vector3<float>(-x, -y, -z));
	}
	SECTION("TEST - operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -12.8f;
		
		zeno::Vector3<float> res = zeno::Vector3<float>(x, y, z) - zeno::Vector3<float>(x, y, z);
		
		REQUIRE(res == zeno::Vector3<float>());
	}
	SECTION("Test -= operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.1f;
		
		zeno::Vector3<float> res = zeno::Vector3<float>(x, y, z);
		
		res -= zeno::Vector3<float>(x, y, z);
		
		REQUIRE(res == zeno::Vector3<float>());
	}
	SECTION("Test + operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.9f;
		
		zeno::Vector3<float> res = zeno::Vector3<float>(x, y, z) + zeno::Vector3<float>(x, y, z);
		
		REQUIRE(res == zeno::Vector3<float>(2.0f * x, 2.0f * y, 2.0f * z));
	}
	SECTION("Test += operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.5f;
		
		zeno::Vector3<float> res = zeno::Vector3<float>(x, y, z);
		res += res;
		
		REQUIRE(res == zeno::Vector3<float>(2.0f * x, 2.0f * y, 2.0f * z));
	}
	SECTION("Test / operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float z = -23.4f;
		float div = 7.4f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec = vec / div;
		
		REQUIRE(vec == zeno::Vector3<float>(x / div, y / div, z / div));
	}
	SECTION("Test /= operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float z = -8.9f;
		float div = 7.4f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec /= div;
		
		REQUIRE(vec == zeno::Vector3<float>(x / div, y / div, z / div));
	}
	SECTION("Test * operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float z = -123.6f;
		float mul = 2.1f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec = vec * mul;
		
		REQUIRE(vec == zeno::Vector3<float>(x * mul, y * mul, z * mul));
		
		
		vec = zeno::Vector3<float>(x, y, z);
		vec = mul * vec;
		
		REQUIRE(vec == zeno::Vector3<float>(x * mul, y * mul, z * mul));
	}
	SECTION("Test *= operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float z = -764.4f;
		float mul = 2.1f;
		
		zeno::Vector3<float> vec = zeno::Vector3<float>(x, y, z);
		vec *= mul;
		
		REQUIRE(vec == zeno::Vector3<float>(x * mul, y * mul, z* mul));
	}
	SECTION("Test == operator")
	{
		zeno::Vector3<float> vec1 = zeno::Vector3<float>(123.4f, 11.0f, -12.0f);
		zeno::Vector3<float> vec2 = zeno::Vector3<float>(13.4f, 1121.0f, -64.4f);
		
		REQUIRE_FALSE(vec1 == vec2);
		
		vec2 = vec1;
		REQUIRE(vec1 == vec2);
	}
	SECTION("Test != operator")
	{
		zeno::Vector3<float> vec1 = zeno::Vector3<float>(123.4f, 11.0f, -12.0f);
		zeno::Vector3<float> vec2 = zeno::Vector3<float>(13.4f, 1121.0f, -64.4f);
		
		REQUIRE(vec1 != vec2);
		
		vec2 = vec1;
		REQUIRE_FALSE(vec1 != vec2);
	}
}

TEST_CASE("Vector4 Test", "[Vector4]")
{
	SECTION("Test default constructor")
	{
		zeno::Vector4<float> vec = zeno::Vector4<float>();
		
		REQUIRE(vec.x == 0.0f);
		REQUIRE(vec.y == 0.0f);
		REQUIRE(vec.z == 0.0f);
		REQUIRE(vec.w == 0.0f);
	}
	SECTION("Test non-default constructor")
	{
		float x = 1.0f;
		float y = 12.0f;
		float z = -12.8f;
		float w = 1.0f;
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		
		REQUIRE(vec.x == x);
		REQUIRE(vec.y == y);
		REQUIRE(vec.z == z);
		REQUIRE(vec.w == w);
	}
	SECTION("Test copy constructor from same type")
	{
		float x = 1.2f;
		float y = 12.2f;
		float z = -12.8f;
		float w = 1.0f;
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		zeno::Vector4<float> cpy = zeno::Vector4<float>(vec);
		
		REQUIRE(cpy == vec);
	}
	SECTION("Test copy constructor from different type")
	{
		int x = 12;
		int y = 453;
		int z = -18;
		int w = 1;
		zeno::Vector4<int> vec = zeno::Vector4<int>(x, y, z, w);
		zeno::Vector4<float> cpy = zeno::Vector4<float>(vec);
		
		REQUIRE(cpy == zeno::Vector4<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)));
	}
	SECTION("Test -(negate) operator")
	{
		float x = 12.3f;
		float y = -123.7f;
		float z = 88.1f;
		float w = 1.0f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec = - vec;
		
		REQUIRE(vec == zeno::Vector4<float>(-x, -y, -z, w));
	}
	SECTION("TEST - operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -12.8f;
		float w = 1.0f;
		
		zeno::Vector4<float> res = zeno::Vector4<float>(x, y, z, w) - zeno::Vector4<float>(x, y, z, w);
		
		REQUIRE(res == zeno::Vector4<float>(0.0f, 0.0f, 0.0f, w));
	}
	SECTION("Test -= operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.1f;
		float w = 1.0f;
		
		zeno::Vector4<float> res = zeno::Vector4<float>(x, y, z, w);
		
		res -= zeno::Vector4<float>(x, y, z, w);
		
		REQUIRE(res == zeno::Vector4<float>(0.0f, 0.0f, 0.0f, w));
	}
	SECTION("Test + operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.9f;
		float w = 1.0f;
		
		zeno::Vector4<float> res = zeno::Vector4<float>(x, y, z, w) + zeno::Vector4<float>(x, y, z, w);
		
		REQUIRE(res == zeno::Vector4<float>(2.0f * x, 2.0f * y, 2.0f * z, w));
	}
	SECTION("Test += operator")
	{
		float x = 12.6f;
		float y = 82.1f;
		float z = -8.5f;
		float w = 1.0f;
		
		zeno::Vector4<float> res = zeno::Vector4<float>(x, y, z, w);
		res += res;
		
		REQUIRE(res == zeno::Vector4<float>(2.0f * x, 2.0f * y, 2.0f * z, w));
	}
	SECTION("Test / operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float z = -23.4f;
		float w = 1.0f;
		float div = 7.4f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec = vec / div;
		
		REQUIRE(vec == zeno::Vector4<float>(x / div, y / div, z / div, w));
	}
	SECTION("Test /= operator")
	{
		float x = 123.75f;
		float y = 12.5f;
		float z = -8.9f;
		float w = 1.0f;
		float div = 7.4f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec /= div;
		
		REQUIRE(vec == zeno::Vector4<float>(x / div, y / div, z / div, w));
	}
	SECTION("Test * operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float z = -123.6f;
		float w = 1.0f;
		float mul = 2.1f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec = vec * mul;
		
		REQUIRE(vec == zeno::Vector4<float>(x * mul, y * mul, z * mul, w));
		
		
		vec = zeno::Vector4<float>(x, y, z, w);
		vec = mul * vec;
		
		REQUIRE(vec == zeno::Vector4<float>(x * mul, y * mul, z * mul, w));
	}
	SECTION("Test *= operator")
	{
		float x = 123.52f;
		float y = 7645.4f;
		float z = -764.4f;
		float w = 1.0f;
		float mul = 2.1f;
		
		zeno::Vector4<float> vec = zeno::Vector4<float>(x, y, z, w);
		vec *= mul;
		
		REQUIRE(vec == zeno::Vector4<float>(x * mul, y * mul, z* mul, w));
	}
	SECTION("Test == operator")
	{
		zeno::Vector4<float> vec1 = zeno::Vector4<float>(123.4f, 11.0f, -12.0f, 0.0f);
		zeno::Vector4<float> vec2 = zeno::Vector4<float>(13.4f, 1121.0f, -64.4f, 0.0f);
		
		REQUIRE_FALSE(vec1 == vec2);
		
		vec2 = vec1;
		REQUIRE(vec1 == vec2);
	}
	SECTION("Test != operator")
	{
		zeno::Vector4<float> vec1 = zeno::Vector4<float>(123.4f, 11.0f, -12.0f, 0.0f);
		zeno::Vector4<float> vec2 = zeno::Vector4<float>(13.4f, 1121.0f, -64.4f, 0.0f);
		
		REQUIRE(vec1 != vec2);
		
		vec2 = vec1;
		REQUIRE_FALSE(vec1 != vec2);
	}
}

TEST_CASE("Keyboard Test", "[Keyboard]")
{
	SECTION("Misc")
	{
		zeno::Clock clock;
		std::cout << "5 Seconds of key pressing." << std::endl;
		while (clock.getElapsedTime().asSeconds() < 0.0f)
		{
			for (int i = 0; i < zeno::Keyboard::Key::NumKeys; i += 1)
			{
				if (zeno::Keyboard::isKeyDown(static_cast<zeno::Keyboard::Key>(i)))
				{
					std::cout << "Key " << i << " is pressed." << std::endl;
				}
			}
		}
	}
}

TEST_CASE("Window Test", "[Window]")
{
	SECTION("MISC")
	{
		zeno::Window window = zeno::Window();

		zeno::VideoMode m;

		m.bitsPerPixel = 32;
		m.width = 1280;
		m.height = 720;

		window.create(m, "zeno::Window::Win32 Test", zeno::WindowStyle::Default);

		int glVersion[2] = { -1, -1 };
		glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
		glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

		std::cout << "OpenGL " << glVersion[0] << "." << glVersion[1] << std::endl;

		glClearColor(100.0f / 255.0f, 149.0f / 255.0f, 247.0f / 255.0f, 1.0f);

		while (window.isOpen())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			window.display();
		}
	}
}