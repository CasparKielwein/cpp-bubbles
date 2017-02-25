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

#ifndef BUBBLES_PAIR_RANGE_HPP_
#define BUBBLES_PAIR_RANGE_HPP_

#include <iterator>
#include <utility>

/**
 * \brief PairRange is a simple wrapper around two iterators, which itself forms a valid range
 *
 * pair_range is most useful to feed two iterators and std::pair of iterators
 * to range based for loops.
 * Some std algorithms return std::pair of iterators.
 * By default it is somewhat annoying to use these with range based for loops.
 *
 * \tparam B type of iterator begin
 * \tparam E type of iterator end
 * currently the standard requires B und E to be the same, but this will change with c++17.
 *
 * \author ckielwein
 */
template<class B, class E>
class PairRange {
public:
	PairRange(B b, E e) :
			begin_ { b }, end_ { e } {
	}

	PairRange(std::pair<B, E> p) :
			begin_ { p.first }, end_ { p.second } {
	}

	auto begin() const {
		return begin_;
	}
	auto end() const {
		return end_;
	}
	auto size() const {
		return std::distance(begin_, end_);
	}
private:
	B begin_;
	E end_;
};

template<class B, class E>
auto begin(PairRange<B, E> r) {
	return r.begin();
}

template<class B, class E>
auto end(PairRange<B, E> r) {
	return r.end();
}

///Creates a range from two iterators
template<class B, class E>
auto make_range(B b, E e) {
	return PairRange<B, E> { b, e };
}

///Creates a range from a std::pair of iterators
template<class B, class E>
auto make_range(std::pair<B, E> p) {
	return PairRange<B, E> { p.first, p.second };
}

#endif /* BUBBLES_PAIR_RANGE_HPP_ */
