#pragma once

#include "../emitter.hpp"
#include "../x86-64.hpp"

namespace voidcore {
	struct Add : Emitter {
		// add register to register
		void add(reg8 a, reg8 b);
		void add(reg16 a, reg16 b);
		void add(reg32 a, reg32 b);
		void add(reg64 a, reg64 b);

		// add memory to register
		void add(reg32 a, disp8<reg32> b);
		void add(reg64 a, disp8<reg64> b);
		void add(reg32 a, disp32<reg32> b);
		void add(reg64 a, disp32<reg64> b);

		// add register to memory
		void add(disp8<reg32> a, reg32 b);
		void add(disp8<reg64> a, reg64 b);
		void add(disp32<reg32> a, reg32 b);
		void add(disp32<reg64> a, reg64 b);

		// add immediate to register
		void add(reg8 a, imm8 b);
		void add(reg16 a, imm16 b);
		void add(reg32 a, imm32 b);
		void add(reg64 a, imm32 b);
	};
}