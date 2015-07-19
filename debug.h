#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

namespace debug {
	namespace {
		struct proxy {
			~proxy(){
				std::cout << std::endl;
			}

			template<typename A>
			proxy& operator<<(const A& a){
				std::cout << a;
			}
		};
	}

	// proxy log(){
	// 	return proxy();
	// }

	template<typename A> 
	void log(A a){
		std::cout << a << std::endl;
	}

	template<typename A> 
	void print(A a){
		std::cout << a;
	}

	template<typename A, typename... B>
	void log(A a, B... b){
		debug::print(a);
		debug::log(b...);
	}

	template<typename A, typename... B>
	void print(A a, B... b){
		debug::print(a);
		debug::print(b...);
	}
}

#endif