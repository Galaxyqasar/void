#pragma once

#include "label.hpp"
#include "x86-64/rex.hpp"
#include "x86-64/value.hpp"

#include <array>

template<typename T>
static std::array<uint8_t, sizeof(T)> byte_cast(const T &val) {
	union {
		T in;
		std::array<uint8_t, sizeof(T)> out;
	} converter;
	converter.in = val;
	return converter.out;
}

namespace rtasm {
	struct Emitter {
		inline void bind(Label &label) {
			label.dst = nextAddr();
			for(uint64_t loc : label.uses) {
				uint32_t offset = label.dst - loc - sizeof(uint32_t);
				patch(loc, imm32(offset));
			}
		}

	protected:
		virtual void emit(uint8_t byte) = 0;
		virtual void patch(intptr_t addr, uint8_t byte) = 0;
		virtual intptr_t nextAddr() = 0;

		inline void emit(rex r) {
			if(uint8_t(r) != 0x0) {
				emit(uint8_t(0x40 + uint8_t(r)));
			}
		}

		inline void emit(Label &label) {
			intptr_t loc = nextAddr();
			label.uses.push_back(loc);
			uint32_t offset = label.dst - loc - sizeof(uint32_t);
			emit(imm32(offset));
		}

		template<typename immtype>
		void emit(immval<immtype> imm) {
			for(uint8_t byte : byte_cast(imm.v)) {
				emit(byte);
			}
		}

		template<typename T>
		void emit(const T &val) {
			emit(static_cast<uint8_t>(val));
		}

		template<typename ...Args>
		void emit(Label &label, Args ...args) {
			emit(label);
			emit(args...);
		}

		template<typename T, typename ...Args>
		void emit(const T &val, Args ...args) {
			emit(val);
			emit(args...);
		}

		template<typename T>
		void patch(intptr_t addr, immval<T> imm) {
			for(const uint8_t &v : byte_cast(imm.v)) {
				patch(addr++, v);
			}
		}

		template<typename T>
		void patch(intptr_t addr, T val) {
			for(const uint8_t &v : byte_cast(val)) {
				patch(addr++, v);
			}
		}
	};
}