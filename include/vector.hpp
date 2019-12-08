#pragma once

#include <array>
#include <type_traits>

namespace squid::hidden_Vector::exposed {

	template< typename T, size_t N >
	struct Vector : std::array<T, N> {

		using Base = std::array<T, N>;

		using Base::operator [];

		constexpr T &x() {
			static_assert( N > 0 );
			return (*this)[0];
		}
		constexpr T const &x() const {
			return x();
		}

		constexpr T &y() {
			static_assert( N > 1 );
			return (*this)[1];
		}
		constexpr T const &y() const {
			return y();
		}

		constexpr T &z() {
			static_assert( N > 2 );
			return (*this)[2];
		}
		constexpr T const &z() const {
			return z();
		}

		constexpr T &w() {
			static_assert( N > 3 );
			return (*this)[3];
		}
		constexpr T const &w() const {
			return w();
		}

	};


	template< typename ...T >
	constexpr auto makeVector( T &&...t ) {
		return Vector< std::common_type_t<T...>, sizeof...(T) >{
				std::forward<T>( t )... };
	}


	template< typename T, typename S, size_t N >
	constexpr auto dot( Vector<T, N> const &a, Vector<S, N> const &b ) {
		using Sum = decltype( std::declval<T>() + std::declval<S>() );
		Sum sum = 0;
		for ( int i = 0; i < N; ++i ) {
			sum += a[i] * b[i];
		}
		return sum;
	}


	template< size_t N > using VectorF = Vector<float, N>;
	template< size_t N > using VectorD = Vector<double, N>;

	template< typename T > using Vector1 = Vector<T, 1>;
	template< typename T > using Vector2 = Vector<T, 2>;
	template< typename T > using Vector3 = Vector<T, 3>;
	template< typename T > using Vector4 = Vector<T, 4>;

	using VectorF1 = VectorF<1>;
	using VectorF2 = VectorF<2>;
	using VectorF3 = VectorF<3>;
	using VectorF4 = VectorF<4>;

	using VectorD1 = VectorD<1>;
	using VectorD2 = VectorD<2>;
	using VectorD3 = VectorD<3>;
	using VectorD4 = VectorD<4>;

	namespace Vector_shorthand {
		constexpr auto V_( auto &&...t ) {
			return makeVector( std::forward<decltype(t)>( t )... );
		};
	}
}

namespace squid {
	using namespace hidden_Vector::exposed;
}
