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

#ifndef BUBBLES_REINTERPRET_COPY_HPP_
#define BUBBLES_REINTERPRET_COPY_HPP_

#include <cstring>

/**
 * \brief reinterpret conversion between two types and no strict aliasing violation
 * \param s value of source type, to convert from
 * \tparam T target type, s is converted to.
 * \return value of type T, which is the converted value of s
 *
 * reinterpet_copy does bitwise conversion, just like reinterpret_cast.
 * It uses memcopy to "copy" the bytes.
 * With optimizations enabled, at least gcc, 4.5+, clang 3.5+ and msvc for x86_64
 * will completely remove the copy.
 *
 * reinterpret copy (or similar versions using copies of char arrays)
 * are the only completely standard compliant way to do bitwise conversions
 * between types.
 * reinterpret_cast violates the strict aliasing rule.
 * Unions must only be read through the same type, they where written.
 * In reality at least of early 2017, neither of these options will actually cause a bug.
 * But why not be strict here, it doesn't cost anything on a good compiler.
 *
 * \see lots of stackoverflow discussion like:
 * http://stackoverflow.com/questions/20762952/most-efficient-standard-compliant-way-of-reinterpreting-int-as-float
 *
 * \author ckielwein
 */
template<class T, class S>
T reinterpret_copy(S s) {
	static_assert(sizeof(T)==sizeof(S),
			"reinterpret_copy demands that Source and Target Types are the same size");
	T result{};
	std::memcpy(&result, &s, sizeof(s));
	return result;
}

#endif /* BUBBLES_REINTERPRET_COPY_HPP_ */
