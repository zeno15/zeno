#include <iostream>
#include <cstdlib>

//~ https://github.com/philsquared/Catch
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <Colour.hpp>

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
