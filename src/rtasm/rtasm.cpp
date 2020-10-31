#include "rtasm.hpp"

namespace rtasm {
	intptr_t Assembler::nextAddr() {
		return buffer.size();
	}

	void Assembler::emit(uint8_t byte) {
		if(buffer.size() == buffer.capacity()) {
			buffer.reserve(Program::pageSize());
		}
		buffer.push_back(byte);
	}

	void Assembler::patch(intptr_t loc, uint8_t byte) {
		buffer[loc] = byte;
	}
}