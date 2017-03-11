/*
 * BSD 2-Clause License
 *
 * Copyright (c) 2017, Caspar Kielwein
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BUBBLES_PRETTYPRINT_HPP_
#define BUBBLES_PRETTYPRINT_HPP_

#include <iostream>
#include <utility>

namespace detail {

static constexpr auto deliminiter = "; ";

template<class T>
void print_impl(const T& v) {
	std::cout << v;
}

void print_impl(const bool v) {
	std::cout << std::boolalpha << v;
}

template<class U, class V>
void print_impl(const std::pair<U, V> v) {
	std::cout << '<' << v.first << ", " << v.second << ">\n";
}

} // namespace detail

/**
 * \brief pretty printa a value to cout
 * \param t1
 * base case for the variadic version
 */
template<class T1>
void print(const T1& t1) {
	detail::print_impl(t1);
	std::cout << '\n';
}

/// prints any number of tokens to cout
template<class T1, class ... T>
void print(const T1& t1, const T&... t) {
	detail::print_impl(t1);
	detail::print_impl(+detail::deliminiter);
	print(t...);
}

/// prints contents of any container or other range
template<class T>
void print_range(const T& v) {
	if (v.empty()) {
		std::cout << "range empty";
		return;
	}
	std::cout << '[';
	detail::print_impl(*begin(v));
	for (auto i = std::next(begin(v)); i != end(v); ++i) {
		std::cout << ", ";
		detail::print_impl(*i);
	}
	std::cout << "]\n";
}

/// prints file, function and line number to cout
#define PRINT_TRACE() \
	std::cout << __FILE__ << ':' <<__LINE__ << ' ' <<  __FUNCTION__ << '\n';

#endif /* BUBBLES_PRETTYPRINT_HPP_ */
