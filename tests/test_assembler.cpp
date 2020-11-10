#include "asm/assembler.hpp"

#include <cassert>

using namespace voidcore;

void test_empty() {
	Assembler asmc;
	Program prog = asmc.build();
	assert(prog.size() == 0);
	assert(prog.copy() == std::vector<uint8_t>{});
}

int main() {
	test_empty();
	return 0;
}