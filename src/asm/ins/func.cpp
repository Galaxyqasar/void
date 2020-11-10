#include "ins/func.hpp"

namespace voidcore {
	void Func::call(Label *pos) {
		emit(0xe8, pos);
	}
	void Func::call(reg64 addr) {}
	void Func::ret(imm16 ds) {
		if(ds > 0) {
			emit(0xc2, ds);
		}
		else {
			emit(0xc3);
		}
	}

	void Func::enter(size_t stacksize) {
		stacks.push_back(stacksize);
	}

	size_t Func::currentStackSize() const {
		return stacks.back();
	}

	void Func::leave() {
		stacks.pop_back();
	}
}