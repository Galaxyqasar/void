#pragma once

#include "value.hpp"

namespace rtasm {
	struct rex {
		enum {
			b = 1,
			x = 2,
			r = 4,
			w = 8
		};

		inline rex(uint8_t value = 0) : m_value(value) {}
		inline rex(const rex &other) : m_value(other.m_value) {}

		inline rex& operator=(uint8_t value) {
			m_value = value;
			return *this;
		}
		inline rex& operator=(const rex &other) {
			m_value = other.m_value;
			return *this;
		}
		inline operator uint8_t() {
			return m_value;
		}

		inline rex operator | (const rex &rhs) {
			return m_value | rhs.m_value;
		}

		inline rex& operator |= (const rex &rhs) {
			m_value |= rhs.m_value;
			return *this;
		}

		template<typename reg1_t, typename reg2_t>
		static rex calc(disp8<reg1_t> rm, reg2_t reg, rex base = {}) {
			return calc(rm.reg, reg, base);
		}
		template<typename reg1_t, typename reg2_t>
		static rex calc(disp32<reg1_t> rm, reg2_t reg, rex base = {}) {
			return calc(rm.reg, reg, base);
		}
		template<typename reg1_t, typename reg2_t>
		static rex calc(reg1_t rm, reg2_t reg, rex base = {}) {
			if(uint8_t(rm) >= 0x8)
				base |= rex::b;
			if(uint8_t(reg) >= 0x8)
				base |= rex::r;
			return base;
		}

	private:
		uint8_t m_value;
	};
}