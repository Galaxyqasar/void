#include "ins/sub.hpp"

namespace voidcore {
	// sub register to register
	void Sub::sub(reg8 a, reg8 b) {}
	void Sub::sub(reg16 a, reg16 b) {}
	void Sub::sub(reg32 a, reg32 b) {}
	void Sub::sub(reg64 a, reg64 b) {}

	// sub memory to register
	void Sub::sub(reg32 a, disp8<reg32> b) {}
	void Sub::sub(reg64 a, disp8<reg64> b) {}
	void Sub::sub(reg32 a, disp32<reg32> b) {}
	void Sub::sub(reg64 a, disp32<reg64> b) {}

	// sub register to memory
	void Sub::sub(disp8<reg32> a, reg32 b) {}
	void Sub::sub(disp8<reg64> a, reg64 b) {}
	void Sub::sub(disp32<reg32> a, reg32 b) {}
	void Sub::sub(disp32<reg64> a, reg64 b) {}

	// sub immediate to register
	void Sub::sub(reg8 a, imm8 b) {}
	void Sub::sub(reg16 a, imm16 b) {}
	void Sub::sub(reg32 a, imm32 b) {}
	void Sub::sub(reg64 a, imm32 b) {
		if(a < reg64::r8)
			emit(rex(rex::w), 0x81, modrm::calc(a, 0x5), b);
		else
			emit(rex(rex::w | rex::r), 0x81, modrm::calc(a, 0x5), b);
	}
}