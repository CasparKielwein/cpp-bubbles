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

#ifndef BUBBLES_NAMED_VALUE_HPP_
#define BUBBLES_NAMED_VALUE_HPP_

#include <utility>

/**
 * \brief NamedValue provides an implementation of the Named Value idiom.
 *
 * NamedValue is a simple typesafe wrapper around any value.
 *
 * It is useful to provide both additional safety and documentation to interfaces
 * consider a call to a function:
 * ~~~{.cpp} auto a = Rectangle{1.2, 3.4}; ~~~
 * It is unclear which parameter is the height, and which is the width.
 * with NamedValue it becomes:
 * ~~~{.cpp}
 * using Height = NamedValue<double>;
 * using Width = NamedValue<double>;
 * auto a = Rectangle{Height{1.2}, Width{3.4}};
 * ~~~
 * It is now impossible to accidently construct the Rectangle
 * with height and width swapped.
 *
 * operator== and operator< are provided for convenience and storage in std::set.
 *
 * \tparam T the Value Type NamedValue is wrapped around
 * \invariant internal storage value is always a valid object.
 * \author ckielwein
 *
 */
template<class T>
class NamedValue {
public:
	/// Require explicit conversion from original value
	explicit NamedValue(T v) :
			value { std::move(v) } {
	}

	NamedValue() = default;

	/// Require explicit conversion to original value
	explicit operator T() const {
		return value;
	}

	/// short call to get original value
	T get() const {
		return value;
	}

private:
	T value;
};

template<class T>
bool operator==(const NamedValue<T>& l, const NamedValue<T>& r) {
	return l.get() == r.get();
}

template<class T>
bool operator<(const NamedValue<T>& l, const NamedValue<T>& r) {
	return l.get() < r.get();
}

#endif /* BUBBLES_NAMED_VALUE_HPP_ */
