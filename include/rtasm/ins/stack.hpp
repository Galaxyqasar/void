#pragma once

#include "../emitter.hpp"
#include "../x86-64.hpp"

namespace rtasm {
	struct Stack : Emitter {
		void push(reg64 r);
		void pop(reg64 r);
	};
}