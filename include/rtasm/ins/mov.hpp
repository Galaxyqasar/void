#pragma once

#include "../emitter.hpp"
#include "../x86-64.hpp"

namespace rtasm {
	struct Mov : Emitter {
		// move register to other register
		inline void mov(reg8 dst, reg8 src) {
			emit(rex::calc(dst, src), 0x88, modrm::calc(dst, src));
		}
		inline void mov(reg16 dst, reg16 src) {
			emit(0x66, 0x89, modrm::calc(dst, src));
		}
		inline void mov(reg32 dst, reg32 src) {
			emit(rex::calc(dst, src), 0x89, modrm::calc(dst, src));
		}
		inline void mov(reg64 dst, reg64 src) {
			emit(rex::calc(dst, src, rex::w), 0x89, modrm::calc(dst, src));
		}

		// move value in memory at address(register) to register
		inline void mov(reg8 src, disp8<reg64> dst) {
			emit(rex::calc(dst, src), 0x8a, modrm::calc(dst, src), dst);
		}
		inline void mov(reg16 src, disp8<reg64> dst) {
			emit(0x66, 0x8b, modrm::calc(dst, src), dst);
		}
		inline void mov(reg32 src, disp8<reg64> dst) {
			emit(rex::calc(dst, src), 0x8b, modrm::calc(dst, src), dst);
		}
		inline void mov(reg64 src, disp8<reg64> dst) {
			emit(rex::calc(dst, src, rex::w), 0x8b, modrm::calc(dst, src), dst);
		}
		inline void mov(reg8 src, disp32<reg64> dst) {
			emit(rex::calc(dst, src), 0x8a, modrm::calc(dst, src), dst);
		}
		inline void mov(reg16 src, disp32<reg64> dst) {
			emit(0x66, 0x8b, modrm::calc(dst, src), dst);
		}
		inline void mov(reg32 src, disp32<reg64> dst) {
			emit(rex::calc(dst, src), 0x8b, modrm::calc(dst, src), dst);
		}
		inline void mov(reg64 src, disp32<reg64> dst) {
			emit(rex::calc(dst, src, rex::w), 0x8b, modrm::calc(dst, src), dst);
		}

		// move register to memory at address(register)
		void mov(disp8<reg64> dst, reg8 src) {
			emit(rex::calc(dst, src), 0x88, modrm::calc(dst, src), dst);
		}
		void mov(disp8<reg64> dst, reg16 src) {
			emit(0x66, 0x89, modrm::calc(dst, src), dst);
		}
		void mov(disp8<reg64> dst, reg32 src) {
			emit(rex::calc(dst, src), 0x89, modrm::calc(dst, src), dst);
		}
		void mov(disp8<reg64> dst, reg64 src) {
			emit(rex::calc(dst, src, rex::w), 0x89, modrm::calc(dst, src), dst);
		}
		void mov(disp32<reg64> dst, reg8 src) {
			emit(rex::calc(dst, src), 0x88, modrm::calc(dst, src), dst);
		}
		void mov(disp32<reg64> dst, reg16 src) {
			emit(0x66, 0x89, modrm::calc(dst, src), dst);
		}
		void mov(disp32<reg64> dst, reg32 src) {
			emit(rex::calc(dst, src), 0x89, modrm::calc(dst, src), dst);
		}
		void mov(disp32<reg64> dst, reg64 src) {
			emit(rex::calc(dst, src, rex::w), 0x89, modrm::calc(dst, src), dst);
		}

		// move immediate to register
		void mov(reg8 dst, imm8 val) {
			emit(rex::calc(dst, reg8::al), 0xb0 + (dst & 0x7), val);
		}
		void mov(reg16 dst, imm16 val) {
			emit(0x66, 0xb8 + (dst & 0x7), val);
		}
		void mov(reg32 dst, imm32 val) {
			emit(rex::calc(dst, reg32::eax), 0xb8 + (dst & 0x7), val);
		}
		void mov(reg64 dst, imm64 val) {
			emit(rex::calc(dst, reg64::rax, rex::w), 0xb8 + (dst & 0x7), val);
		}

		// move immediate to memory at address(register)
		void mov(disp32<reg64> dst, imm8 src) {
			emit(rex::calc(dst, reg64::rax), 0xc6, modrm::calc(dst, 0x0), dst, src);
		}
		void mov(disp32<reg64> dst, imm16 src) {
			emit(0x66, 0xc7, modrm::calc(dst, 0x0), dst, src);
		}
		void mov(disp32<reg64> dst, imm32 src) {
			emit(rex::calc(dst, reg64::rax), 0xc7, modrm::calc(dst, 0x0), dst, src);
		}
	};
}