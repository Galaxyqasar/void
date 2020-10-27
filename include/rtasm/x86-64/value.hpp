#pragma once

#include <cstdint>

namespace rtasm {
	namespace x86_64 {
		template<typename T>
		struct immval {
			T v;
			immval(T v) : v(v) {}
			operator T() {
				return v;
			}
		};

		typedef immval<uint8_t> imm8;
		typedef immval<uint16_t> imm16;
		typedef immval<uint32_t> imm32;
		typedef immval<uint64_t> imm64;

		template<typename reg_t>
		struct disp8 {
			reg_t reg;
			int8_t displacement;
			inline disp8(reg_t reg, int8_t displacement = 0) : reg(reg), displacement(displacement) {}
			inline disp8 operator+(const int8_t displacement) {
				return disp8(this->reg, this->displacement + displacement);
			}
		};

		template<typename reg_t>
		struct disp32 {
			reg_t reg;
			int32_t displacement;
			inline disp32(reg_t reg, int32_t displacement = 0) : reg(reg), displacement(displacement) {}
			inline disp32 operator+(const int32_t displacement) {
				return disp32(this->reg, this->displacement + displacement);
			}
		};
	}
}