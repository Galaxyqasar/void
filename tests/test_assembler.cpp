#include "rtasm/rtasm.hpp"

#include <cassert>

void test_empty() {
	rtasm::Assembler asmc;
	rtasm::Program prog = asmc.build();
	assert(prog.size() == 0);
}

int main() {
	test_empty();
	return 0;
}