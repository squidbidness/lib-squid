#include "catch2/catch.hpp"

#include "vector.hpp"

namespace squid {

	using namespace Vector_shorthand;

	template< typename ...S >
	auto testComponents( S &&...s ) -> void {
		auto v = V_( std::forward<S>( s )... );

		if constexpr ( v.size() > 0 ) {
			REQUIRE( v[0] == v.x() );
					// << "v[0] = " << v[0] << ", v.x()=" << v.x();
		}
		if constexpr ( v.size() > 1 ) {
			REQUIRE( v[1] == v.y() );
					// << "v[1] = " << v[1] << ", v.y()=" << v.y();
		}
		if constexpr ( v.size() > 2 ) {
			REQUIRE( v[2] == v.z() );
					// << "v[2] = " << v[2] << ", v.z()=" << v.z();
		}
		if constexpr ( v.size() > 3 ) {
			REQUIRE( v[3] == v.w() );
					// << "v[3] = " << v[3] << ", v.w()=" << v.w();
		}
	}

	TEST_CASE( "component_getters", "[Vector]" ) {

		testComponents( 0.0f );
		testComponents( 0.0f, 1.0f );
		testComponents( 0.0f, 1.0f, 2.0f );
		testComponents( 0.0f, 1.0f, 2.0f, 3.0f );

		testComponents( 0.0f );
		testComponents( 0.0f, 1.0f );
		testComponents( 0.0f, 1.0f, 2.0f );
		testComponents( 0.0f, 1.0f, 2.0f, 3.0f );

		testComponents( 0.0 );
		testComponents( 0.0, 1.0 );
		testComponents( 0.0, 1.0, 2.0 );
		testComponents( 0.0, 1.0, 2.0, 3.0 );

		testComponents( 0 );
		testComponents( 0, 1 );
		testComponents( 0, 1, 2 );
		testComponents( 0, 1, 2, 3 );

		testComponents( 0ul );
		testComponents( 0ul, 1ul );
		testComponents( 0ul, 1ul, 2ul );
		testComponents( 0ul, 1ul, 2ul, 3ul );
	}

	TEST_CASE( "dot", "[Vector]" ) {
		REQUIRE( 4.0f == dot( V_(0.0f, 1.0f, 2.0f, 3.0f), V_(3.0f, 2.0f, 1.0f, 0.0f) ) );
		REQUIRE( 14.0 == dot( V_(1.0, 2.0, 3.0), V_(1.0, 2.0, 3.0) ) );
		REQUIRE( -2 == dot( V_(4, -2), V_(-2, -3) ) );
		REQUIRE( 14u == dot( V_(4, 2), V_(2, 3) ) );
	}

}
