# cpp-bubbles
Collection of independent and useful pieces of C++ 

cpp-bubbles is a collection of small pieces of c++ code (a bubble) which are useful in a lot of different use cases.
cpp-bubbles aims for portability and minimal dependencies. Each bubble can be copied into a codebase and used on its own, or a codebase could link against cpp-bubbles.

A bubble is a single header, or header plus compilation unit.
Each bubble comes with a small description of usage and a test-driver which serves both as example and test.

# Current collection of bubbles:
* NamedValue: a simple template Wrapper for the Named Value idiom
* demangle: functions to demangle typeid if returned mangled by gcc
* pair_range: use std::pair<Iterator> in range based for loop
* power_of_two: check if an integral valus is a power of two, and get next
* prettyprint: convenient print functions for all your printf debugging needs
* reinterpret_copy: reinterpret_cast without the strict alising violation
* safe_cstring: typesafe replacement of cstring functions memcpy, memmove and memset
* scope_exit: automatically call code on end of scopes