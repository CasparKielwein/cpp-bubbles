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

#ifndef BUBBLES_SAFE_CSTRING_HPP_
#define BUBBLES_SAFE_CSTRING_HPP_

#include <cstring>
#include <type_traits>

/**
 * \brief memcpy with a static check if memcpy is safe to use on types
 * \param dest pointer to the memory location to copy to
 * \param src pointer to the memory location to copy from
 * \param count number of bytes to copy
 * \return \p dest
 *
 * safe_memcpy is useful when transfering C Code to C++.
 * When structs are converted to more complex classes it might become
 * unsafe to use memcpy on them.
 * Doing so is not checked by the compiler, but will result in hard to track bugs.
 *
 * safe_memcpy is a complete replacement for memcpy which performs the checks
 * if memcpy is safe to use on the parameter types on compile time.
 *
 * \see http://en.cppreference.com/w/cpp/string/byte/memcpy
 */
template<class T, class S>
void* safe_memcpy(T* dest, const S* src, std::size_t count) {

	static_assert(std::is_trivially_copyable<T>::value,
			"Target type of memcpy needs to be trivially copyable");
	static_assert(std::is_trivially_copyable<S>::value,
			"Source type of memcpy needs to be trivially copyable");

	return std::memcpy(dest, src, count);
}

/**
 * \brief memmove with a static check if memmove is safe to use on types
 * \param dest pointer to the memory location to copy to
 * \param src pointer to the memory location to copy from
 * \param count number of bytes to copy
 * \return \p dest
 *
 * safe_memmove is useful when transfering C Code to C++.
 * When structs are converted to more complex classes it might become
 * unsafe to use memmove on them.
 * Doing so is not checked by the compiler, but will result in hard to track bugs.
 *
 * safe_memmove is a complete replacement for memmove which performs the checks
 * if memmove is safe to use on the parameter types on compile time.
 *
 * \see http://en.cppreference.com/w/cpp/string/byte/memmove
 */
template<class T, class S>
void* safe_memmove(T* dest, const S* src, std::size_t count) {

	static_assert(std::is_trivially_copyable<T>::value,
			"Target type of memmove needs to be trivially copyable");
	static_assert(std::is_trivially_copyable<S>::value,
			"Source type of memmove needs to be trivially copyable");

	return std::memmove(dest, src, count);
}

/**
 * \brief memset with a static check if memset is safe to use on types
 * \param dest pointer to the object to fill
 * \param ch fill byte
 * \param count number of bytes to fill
 * \return \p dest
 *
 * safe_memset is useful when transfering C Code to C++.
 * When structs are converted to more complex classes it might become
 * unsafe to use memset on them.
 * Doing so is not checked by the compiler, but will result in hard to track bugs.
 *
 * safe_memset is a complete replacement for memset which performs the checks
 * if memset is safe to use on the parameter types on compile time.
 *
 * \Note this is for automatic conversion of code.
 * When manually working on code, use a constructor for your types!
 *
 * \see http://en.cppreference.com/w/cpp/string/byte/memset
 */
template<class T>
void* safe_memset(T* dest, int ch, std::size_t count) {

	static_assert(std::is_trivially_copyable<T>::value,
			"Target type of memset needs to be trivially copyable");

	return std::memset(dest, ch, count);
}

#endif /* BUBBLES_SAFE_CSTRING_HPP_ */
