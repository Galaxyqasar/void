#pragma once

#include "../emitter.hpp"
#include "../x86-64.hpp"

namespace voidcore {
	struct Mov : Emitter {
		// move register to other register
		void mov(reg8 dst, reg8 src);
		void mov(reg16 dst, reg16 src);
		void mov(reg32 dst, reg32 src);
		void mov(reg64 dst, reg64 src);

		// move value in memory at address(register) to register
		void mov(reg8 src, disp8<reg64> dst);
		void mov(reg16 src, disp8<reg64> dst);
		void mov(reg32 src, disp8<reg64> dst);
		void mov(reg64 src, disp8<reg64> dst);
		void mov(reg8 src, disp32<reg64> dst);
		void mov(reg16 src, disp32<reg64> dst);
		void mov(reg32 src, disp32<reg64> dst);
		void mov(reg64 src, disp32<reg64> dst);

		// move register to memory at address(register)
		void mov(disp8<reg64> dst, reg8 src);
		void mov(disp8<reg64> dst, reg16 src);
		void mov(disp8<reg64> dst, reg32 src);
		void mov(disp8<reg64> dst, reg64 src);
		void mov(disp32<reg64> dst, reg8 src);
		void mov(disp32<reg64> dst, reg16 src);
		void mov(disp32<reg64> dst, reg32 src);
		void mov(disp32<reg64> dst, reg64 src);

		// move immediate to register
		void mov(reg8 dst, imm8 val);
		void mov(reg16 dst, imm16 val);
		void mov(reg32 dst, imm32 val);
		void mov(reg64 dst, imm64 val);

		// move immediate to memory at address(register)
		void mov(disp32<reg64> dst, imm8 src);
		void mov(disp32<reg64> dst, imm16 src);
		void mov(disp32<reg64> dst, imm32 src);
	};
}