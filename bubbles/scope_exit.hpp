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

#ifndef BUBBLES_SCOPE_EXIT_HPP_
#define BUBBLES_SCOPE_EXIT_HPP_

#include <exception>
#include <utility>

/*
 * scope_exit, scope_faiure and scope_success execut arbitrary code
 * at the end of scopes.
 * They use the RAII idiom to do that.
 *
 * This is basically BOOST_SCOPE_EXIT without the preprocessor.
 * Since we have lambdas after C++11 we don't really need the macros anymore.
 *
 * Warning: Don't use scope_failure or scope_success in destructors.
 * When the destructor is called during stack unwinding,
 * scope_failure/success might not behave as expected.
 * see: http://www.gotw.ca/gotw/047.htm
 */

/// executes a callback on destruction, used by scope_exit and variants.
template<class Callback>
class scope_handler {
public:
	explicit scope_handler(Callback callback) :
			c(std::move(callback)) {
	}

	scope_handler(scope_handler&&) = default;

	///we don't allow copying or assignment since that would be very confusing
	scope_handler(const scope_handler&) = delete;
	scope_handler& operator=(scope_handler&&) = delete;
	scope_handler& operator=(const scope_handler&) = delete;

	~scope_handler() {
		c();
	}
private:
	Callback c;
};

/**
 * \brief scope_failure executes if the current scope is left.
 * \param callback is executed on end of scope
 * \return scope_handler which does the execution in its destructor
 */
template<class T>
auto scope_exit(T callback) {
	return scope_handler<T>(std::move(callback));
}

/**
 * \brief scope_failure executes if the current scope is left via an uncaught exception
 * \param callback is executed on end of scope
 * \return scope_handler which does the execution in its destructor
 */
template<class T>
auto scope_failure(T callback) {
	auto call = [callback]() {
		if (std::uncaught_exception()) {
			callback();
		}
		//else simply do nothing
		};

	return scope_handler<decltype(call)>(std::move(call));
}

/**
 * \brief scope_success executes if the current scope is left and no exception is thrown
 * \param callback is executed on end of scope
 * \return scope_handler which does the execution in its destructor
 */
template<class T>
auto scope_success(T callback) {
	auto call = [callback]() {
		if (!std::uncaught_exception()) {
			callback();
		}
		//do nothing in error case
		};

	return scope_handler<decltype(call)>(std::move(call));
}

#endif /* BUBBLES_SCOPE_EXIT_HPP_ */
