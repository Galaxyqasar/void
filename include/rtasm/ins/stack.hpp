#pragma once

#include "../emitter.hpp"
#include "../x86-64.hpp"

namespace rtasm {
	struct Stack : Emitter {
		inline void push(reg64 r) {
			emit(0x50 + (r & 0x7));
		}
		inline void pop(reg64 r) {
			emit(0x58 + (r & 0x7));
		}
	};
}