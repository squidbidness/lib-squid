#include "loops.hpp"

#include <catch2/catch.hpp>

#include <array>
#include <sstream>

namespace squid {

	TEST_CASE( "forAndBetween()", "[loops]" ) {

		std::ostringstream o;
		forAndBetween( std::array{ 1, 2, 3 },
				[&] ( auto f ) { o << f; },
				[&] ( auto p, auto n ) { o << "," << (p + n) << ","; }
				);
		REQUIRE( o.str() == "1,3,2,5,3" );
	}
}
