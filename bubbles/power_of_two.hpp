/*
 * power_of_two.hpp
 *
 *  Created on: Feb 25, 2017
 *      Author: ckielwein
 */

#ifndef BUBBLES_POWER_OF_TWO_HPP_
#define BUBBLES_POWER_OF_TWO_HPP_

#include <cassert>
#include <type_traits>

/**
 * \brief checks if any integer is a power of two
 * \param x
 * \return true it t is a power of two, false otherwise
 * \pre x >= 0
 *
 * A nice explanation of how the algorithm works can be found on Rick Regans blog:
 * http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
 */
template<class T>
bool is_power_of_two(const T x) {
	static_assert(std::is_integral<T>::value, "power_of_two works only for integers");
	assert(x >= 0);
	return (x != 0) && ((x & (~x + 1)) == x);
}

namespace detail {
template<int size>
struct size_tag {
};

//constexpr if will really make this much nicer
template<class T>
T power_of_two_impl(T x, size_tag<1>) {
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x++;
	return x;
}

template<class T>
T power_of_two_impl(T x, size_tag<2>) {
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x++;
	return x;
}

template<class T>
T power_of_two_impl(T x, size_tag<4>) {
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return x;
}

template<class T>
T power_of_two_impl(T x, size_tag<8>) {
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	x++;
	return x;
}

} //namespace detail

/**
 * \brief get the next power_of_two for a given integer
 *
 * implementation is based on http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
 * This code just provides it for integers of arbitrary size
 *
 * \param x
 * \return the smallest value for which is_power_of_two(return) && return >= x holds
 * \pre x >=  0
 */
template<class T>
T next_power_of_two(const T x) {
	static_assert(std::is_integral<T>::value, "power_of_two works only for integers");
	assert(x >= 0);
	return detail::power_of_two_impl(x, detail::size_tag<sizeof(T)> { });
}

#endif /* BUBBLES_POWER_OF_TWO_HPP_ */
