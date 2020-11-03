#include "ins/stack.hpp"

namespace rtasm {
	void Stack::push(reg64 r) {
		emit(0x50 + (r & 0x7));
	}
	void Stack::pop(reg64 r) {
		emit(0x58 + (r & 0x7));
	}
}