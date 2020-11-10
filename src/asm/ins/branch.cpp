#include "ins/branch.hpp"

namespace voidcore {
	void Branch::jmp(imm32 offset) {
		emit(0xe9, offset - 0x5);
	}

	void Branch::jmp(Label *label) {
		emit(0xe9, label);
	}
}