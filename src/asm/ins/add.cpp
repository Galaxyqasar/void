#include "ins/add.hpp"

namespace voidcore {
	// add register to register
	void Add::add(reg8 a, reg8 b) {
		emit(rex::calc(a, b), 0x00, modrm::calc(a, b));
	}
	void Add::add(reg16 a, reg16 b) {
		emit(0x66, 0x01, modrm::calc(a, b));
	}
	void Add::add(reg32 a, reg32 b) {
		emit(rex::calc(a, b), 0x01, modrm::calc(a, b));
	}
	void Add::add(reg64 a, reg64 b) {
		emit(rex::calc(a, b, rex::w), 0x01, modrm::calc(a, b));
	}

	// add memory to register
	void Add::add(reg32 a, disp8<reg32> b) {}
	void Add::add(reg64 a, disp8<reg64> b) {}
	void Add::add(reg32 a, disp32<reg32> b) {}
	void Add::add(reg64 a, disp32<reg64> b) {}

	// add register to memory
	void Add::add(disp8<reg32> a, reg32 b) {}
	void Add::add(disp8<reg64> a, reg64 b) {}
	void Add::add(disp32<reg32> a, reg32 b) {}
	void Add::add(disp32<reg64> a, reg64 b) {}

	// add immediate to register
	void Add::add(reg8 a, imm8 b) {
		if(a == reg8::al)
			emit(0x04, b);
		else if(a < reg8::r8b)
			emit(0x80, modrm::calc(a, 0x0), b);
		else
			emit(rex(rex::r), 0x80, modrm::calc(a, 0x0), b);
	}
	void Add::add(reg16 a, imm16 b) {}
	void Add::add(reg32 a, imm32 b) {
		if(a == reg32::eax)
			emit(0x05, b);
		else if(a < reg32::r8d)
			emit(0x81, modrm::calc(a, 0x0), b);
		else
			emit(rex(rex::r), 0x81, modrm::calc(a, 0x0), b);
	}
	void Add::add(reg64 a, imm32 b) {}
}