#pragma once

#include <cstdint>

#include "value.hpp"

namespace rtasm {
	struct modrm {
		inline modrm(uint8_t value = 0) : m_value(value) {}
		inline modrm(const modrm &other) : m_value(other.m_value) {}
		inline modrm(uint8_t mod, uint8_t reg, uint8_t rm) {
			m_value = (mod<<6) | (reg<<3) | rm;
		}

		inline modrm& operator=(uint8_t value) {
			m_value = value;
			return *this;
		}
		inline modrm& operator=(const modrm &other) {
			m_value = other.m_value;
			return *this;
		}
		inline operator uint8_t() const {
			return m_value;
		}

		bool needsSIB() {
			// mod != 0x3 && r/m == 0x4
			return (m_value ^ 0xc0) && ((m_value & 0x7) == 0x4);
		}

		template<typename reg_t>
		static uint8_t reg(reg_t r) {
			return static_cast<uint8_t>(r) & 0x7;	// last 3 bits of r
		}

		template<typename reg_t> static uint8_t rm(disp8 <reg_t> p) { return (static_cast<uint8_t>(p.reg) & 0x7); }
		template<typename reg_t> static uint8_t rm(disp32<reg_t> p) { return (static_cast<uint8_t>(p.reg) & 0x7); }
		template<typename reg_t> static uint8_t rm(reg_t p) 		 { return (static_cast<uint8_t>(p)     & 0x7); }

		template<typename reg_t> static uint8_t mod(disp8 <reg_t> p) { return 0x1; }
		template<typename reg_t> static uint8_t mod(disp32<reg_t> p) { return 0x2; }
		template<typename reg_t> static uint8_t mod(reg_t p)         { return 0x3; }

		template<typename reg1_t, typename reg2_t>
		static modrm calc(disp8<reg1_t> p1, reg2_t p2) {
			return modrm(mod(p1), reg(p2), rm(p1));
		}
		template<typename reg1_t, typename reg2_t>
		static modrm calc(reg1_t p1, disp8<reg2_t> p2) {
			return modrm(mod(p2), reg(p1), rm(p2));
		}
		template<typename reg1_t, typename reg2_t>
		static modrm calc(disp32<reg1_t> p1, reg2_t p2) {
			return modrm(mod(p1), reg(p2), rm(p1));
		}
		template<typename reg1_t, typename reg2_t>
		static modrm calc(reg1_t p1, disp32<reg2_t> p2) {
			return modrm(mod(p2), reg(p1), rm(p2));
		}
		template<typename reg1_t, typename reg2_t>
		static modrm calc(reg1_t p1, reg2_t p2) {
			return modrm(mod(p1), reg(p2), rm(p1));
		}

	private:
		uint8_t m_value;
	};
}