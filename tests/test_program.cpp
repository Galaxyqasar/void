#include "asm/program.hpp"

#include <iostream>
#include <cassert>
#include <csignal>
#include <csetjmp>

using namespace voidcore;

void test_emptyProgram() {
	Program prog;
}

void test_initProgram() {
	Program prog(std::vector<uint8_t>({0, 1, 2, 3, 4}));
	// prog.size() is a multiple of the os page size, but should be at least as large as our data
	assert(prog.size() >= 5);
	assert(prog.data()[0] == 0);
	assert(prog.data()[2] == 2);
}

void test_reinitProgram() {
	Program prog(std::vector<uint8_t>({0, 1, 2, 3, 4}));
	prog = std::vector<uint8_t>({5, 4, 3, 2, 1, 0});
	// prog.size() is a multiple of the os page size, but should be at least as large as our data
	assert(prog.size() >= 6);
	assert(prog.data()[0] == 5);
	assert(prog.data()[2] == 3);
}

void test_funcRetVoid() {
	std::vector<uint8_t> code = {
		0xc3	// ret
	};

	Program prog(code);
	funcptr_t<void()> func = prog.get<void()>();

	// function shouldn't be a nullptr
	assert(func);

	// function should be callable, but doesn't do anything
	func();
}

void test_funcRetInt() {
	std::vector<uint8_t> code = {
		0xb8, 0x2a, 0x00, 0x00, 0x00, // mov eax, 0x2a
		0xc3	// ret
	};

	Program prog(code);
	funcptr_t<int()> func = prog.get<int()>();

	// function shouldn't be a nullptr
	assert(func);

	// check return value
	assert(func() == 0x2a);
}

void test_multipleFunctions() {
	std::vector<uint8_t> code = {
		0xb8, 0x2a, 0x00, 0x00, 0x00, // mov eax, 0x2a
		0xc3,	// ret
		0xb8, 0x4c, 0x00, 0x00, 0x00, // mov eax, 0x4c
		0xc3	// ret
	};

	Program prog(code);
	funcptr_t<int()> func1 = prog.get<int()>(0);	// function at offset 0
	funcptr_t<int()> func2 = prog.get<int()>(6);	// function at offset 6

	// functions shouldn't be nullptr
	assert(func1 && func2);

	// check return values
	assert(func1() == 0x2a);
	assert(func2() == 0x4c);
}

void test_copyProgram() {
	std::vector<uint8_t> code = {
		0xb8, 0x2a, 0x00, 0x00, 0x00, // mov eax, 0x2a
		0xc3,	// ret
		0xb8, 0x4c, 0x00, 0x00, 0x00, // mov eax, 0x4c
		0xc3	// ret
	};

	Program original(code);
	Program copy = original;	// copy-constructor
	funcptr_t<int()> func1 = copy.get<int()>(0);	// function at offset 0
	funcptr_t<int()> func2 = copy.get<int()>(6);	// function at offset 6

	// functions shouldn't be nullptr
	assert(func1 && func2);

	// check return values
	assert(func1() == 0x2a);
	assert(func2() == 0x4c);

	Program copy2;
	copy2 = original;	// assignment operator
	funcptr_t<int()> func3 = copy2.get<int()>(0);	// function at offset 0
	funcptr_t<int()> func4 = copy2.get<int()>(6);	// function at offset 6

	// functions shouldn't be nullptr
	assert(func3 && func4);

	// check return values
	assert(func3() == 0x2a);
	assert(func4() == 0x4c);
}

// the memory should be write-protected
// -> on write access a segfault should be thrown
sigjmp_buf segfaultloc;
void test_memoryProtection() {
	std::vector<uint8_t> code(512, 0);
	Program prog(code);

	// const_cast to write, this should not be done in production code and is only for security testing here
	uint8_t *data = const_cast<uint8_t*>(prog.data());
	assert(data);

	// create signal handler to catch segfault
	struct sigaction handler;
	handler.sa_handler = [](int){
		longjmp(segfaultloc, 1);
	};
	sigemptyset(&handler.sa_mask);
	handler.sa_flags = 0;
	sigaction(SIGSEGV, &handler, NULL);

	if(setjmp(segfaultloc) == 0) {
		data[0] = 123;
		// the previous line should throw a segfault and thus the next line shouldn't be run
		// -> test failed
		assert(false);
	}
	// test successfull
}

int main() {
	test_emptyProgram();
	test_initProgram();
	test_reinitProgram();
	test_funcRetVoid();
	test_funcRetInt();
	test_multipleFunctions();
	test_copyProgram();
	test_memoryProtection();
	return 0;
}