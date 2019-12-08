#pragma once

#include "type_traits.hpp"

#include <functional>
#include <type_traits>


namespace squid::loops::detail {

	template< typename Range >
	using RangeValueType = decltype( *std::begin(std::declval<Range>()) );

	template< typename Op >
	using IsNullaryOp =
			std::is_convertible< Op, std::function<void()> >;

	template< typename Range, typename Op >
	using IsRangeValueUnaryOp =
			std::is_convertible<
				Op,
				std::function< void( RangeValueType<Range> ) >
			>;

	template< typename Range, typename Op >
	using IsRangeValueBinaryOp =
			std::is_convertible<
				Op,
				std::function< void(
					RangeValueType<Range>,
					RangeValueType<Range>
				) >
			>;

	template<
			typename Range,
			typename Op,
			typename Value
	>
	std::enable_if_t<
			IsNullaryOp<Op>::value,
			void
	>
	doBetweenOp( Range &&, Op &&op, Value &&, Value && ) {
		op();
	}

	template<
			typename Range,
			typename Op,
			typename Value
	>
	std::enable_if_t<
			IsRangeValueBinaryOp<Range, Op>::value,
			void
	>
	doBetweenOp( Range &&, Op &&op, Value &&a, Value &&b ) {
		op( std::forward<Value>(a), std::forward<Value>(b) );
	}


	template<
			typename Range,
			typename Op
	>
	using IsIndexedForOp =
			std::is_convertible<
				Op,
				std::function< void(RangeValueType<Range>, size_t) >
			>;

}

namespace squid {

	template<
			typename Range,
			typename Op,
			typename BetweenOp,

			typename = typename std::enable_if_t<
				loops::detail::IsRangeValueUnaryOp< Range, Op >::value
			>,
			typename = typename std::enable_if_t<
				disjunction<
					loops::detail::IsNullaryOp< BetweenOp >,
					loops::detail::IsRangeValueBinaryOp< Range, BetweenOp >
				>::value
			>
	>
	void forAndBetween( Range &&range, Op &&op, BetweenOp &&betweenOp ) {

		auto curr = std::begin( std::forward<Range>(range) );
		auto end = std::end( std::forward<Range>(range) );
		decltype(curr) next = curr;

		if ( next != end )
			++next;
		else
			return;

		using loops::detail::doBetweenOp;
		while ( next != end ) {
			op( *curr );
			doBetweenOp(
					std::forward<Range>( range ),
					std::forward<BetweenOp>( betweenOp ),
					*curr,
					*next
			);
			++curr;
			++next;
		}
		op( *curr );
	}


	template<
			typename Range,
			typename Op,

			typename = std::enable_if_t<
				loops::detail::IsIndexedForOp< Range, Op >::value >
	>
	void forIndexed( Range &&range, Op &&op ) {
		size_t i = 0;
		for ( auto &&value : range ) {
			op( value, i++ );
		}
	}

}
