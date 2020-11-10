#pragma once

namespace voidcore {
/* // this doesn't work (enums are converted to uints and become indistinguishable)
	struct reg8 {
		enum {
			al, cl, dl, bl, ah, ch, dh, bh,
			spl = ah, bpl, sil, dil,
			r8b, r9b, r10b, r11b,
			r12b, r13b, r14b, r15b
		};

		inline reg8(uint8_t value = 0) : m_value(value) {}
		inline reg8(const reg8 &other) : m_value(other.m_value) {}

		inline reg8& operator=(uint8_t value) {
			m_value = value;
			return *this;
		}
		inline reg8& operator=(const reg8 &other) {
			m_value = other.m_value;
			return *this;
		}
		inline operator uint8_t() {
			return m_value;
		}

	private:
		uint8_t m_value;
	};

	struct reg16 {
		enum {
			ax, cx, dx, bx,
			sp, bp, si, di,
			r8w, r9w, r10w, r11w,
			r12w, r13w, r14w, r15w
		};

		inline reg16(uint8_t value = 0) : m_value(value) {}
		inline reg16(const reg16 &other) : m_value(other.m_value) {}

		inline reg16& operator=(uint8_t value) {
			m_value = value;
			return *this;
		}
		inline reg16& operator=(const reg16 &other) {
			m_value = other.m_value;
			return *this;
		}
		inline operator uint8_t() {
			return m_value;
		}

	private:
		uint8_t m_value;
	};

	struct reg32 {
		enum {
			eax, ecx, edx, ebx,
			esp, ebp, esi, edi,
			r8d, r9d, r10d, r11d,
			r12d, r13d, r14d, r15d
		};

		inline reg32(uint8_t value = 0) : m_value(value) {}
		inline reg32(const reg32 &other) : m_value(other.m_value) {}

		inline reg32& operator=(uint8_t value) {
			m_value = value;
			return *this;
		}
		inline reg32& operator=(const reg32 &other) {
			m_value = other.m_value;
			return *this;
		}
		inline operator uint8_t() {
			return m_value;
		}

	private:
		uint8_t m_value;
	};
	struct reg64 {
		enum {
			rax, rcx, rdx, rbx,
			rsp, rbp, rsi, rdi,
			r8, r9, r10, r11,
			r12, r13, r14, r15
		};

		inline reg64(uint8_t value = 0) : m_value(value) {}
		inline reg64(const reg64 &other) : m_value(other.m_value) {}

		inline reg64& operator=(uint8_t value) {
			m_value = value;
			return *this;
		}
		inline reg64& operator=(const reg64 &other) {
			m_value = other.m_value;
			return *this;
		}
		inline operator uint8_t() {
			return m_value;
		}

	private:
		uint8_t m_value;
	};
*/
	enum class reg8 {
		al, cl, dl, bl, ah, ch, dh, bh,
		spl = ah, bpl, sil, dil,
		r8b, r9b, r10b, r11b,
		r12b, r13b, r14b, r15b
	};
	enum class reg16 {
		ax, cx, dx, bx,
		sp, bp, si, di,
		r8w, r9w, r10w, r11w,
		r12w, r13w, r14w, r15w
	};
	enum class reg32 {
		eax, ecx, edx, ebx,
		esp, ebp, esi, edi,
		r8d, r9d, r10d, r11d,
		r12d, r13d, r14d, r15d
	};
	enum class reg64 {
		rax, rcx, rdx, rbx,
		rsp, rbp, rsi, rdi,
		r8 , r9 , r10, r11,
		r12, r13, r14, r15
	};


	inline uint8_t operator&(const reg8  &rvalue, const uint8_t &lvalue) {
		return static_cast<uint8_t>(rvalue) & lvalue;
	}

	inline uint8_t operator&(const reg16 &rvalue, const uint8_t &lvalue) {
		return static_cast<uint8_t>(rvalue) & lvalue;
	}

	inline uint8_t operator&(const reg32 &rvalue, const uint8_t &lvalue) {
		return static_cast<uint8_t>(rvalue) & lvalue;
	}

	inline uint8_t operator&(const reg64 &rvalue, const uint8_t &lvalue) {
		return static_cast<uint8_t>(rvalue) & lvalue;
	}
}