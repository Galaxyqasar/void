#pragma once

#include <vector>

#include "virtual.hpp"
#include "program.hpp"

namespace rtasm {
	struct Assembler : VirtualAssembler {
		inline Program build() {
			return Program(buffer);
		}

	protected:
		intptr_t nextAddr();
		void emit(uint8_t byte);
		void patch(intptr_t loc, uint8_t byte);

	private:
		std::vector<uint8_t> buffer;
	};
}