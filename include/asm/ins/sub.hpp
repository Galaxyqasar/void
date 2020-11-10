#pragma once

#include "../emitter.hpp"
#include "../x86-64.hpp"

namespace voidcore {
	struct Sub : Emitter {
		// sub register to register
		void sub(reg8 a, reg8 b);
		void sub(reg16 a, reg16 b);
		void sub(reg32 a, reg32 b);
		void sub(reg64 a, reg64 b);

		// sub memory to register
		void sub(reg32 a, disp8<reg32> b);
		void sub(reg64 a, disp8<reg64> b);
		void sub(reg32 a, disp32<reg32> b);
		void sub(reg64 a, disp32<reg64> b);

		// sub register to memory
		void sub(disp8<reg32> a, reg32 b);
		void sub(disp8<reg64> a, reg64 b);
		void sub(disp32<reg32> a, reg32 b);
		void sub(disp32<reg64> a, reg64 b);

		// sub immediate to register
		void sub(reg8 a, imm8 b);
		void sub(reg16 a, imm16 b);
		void sub(reg32 a, imm32 b);
		void sub(reg64 a, imm32 b);
	};
}