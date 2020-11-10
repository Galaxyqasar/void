#pragma once

#include "../emitter.hpp"
#include "../label.hpp"
#include "../x86-64.hpp"

namespace voidcore {
	struct Func : Emitter {
		void call(Label *pos);
		void call(reg64 addr);
		void ret(imm16 ds = 0);

		// warning: these functions are not equivalent to the enter / leave instructions,
		// they only store the current stacksize
		void enter(size_t stacksize);
		size_t currentStackSize() const;
		void leave();

	private:
		std::vector<size_t> stacks;
	};
}