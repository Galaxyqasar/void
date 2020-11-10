#include <iostream>
#include <string>
#include <vector>

#include "engine.hpp"

int main(int argc, char *argv[]) {
	std::vector<std::string> args(argv, argv + argc);

	voidcore::Engine engine;
	std::ifstream source("test.v");
	std::ofstream binary("test.o");

	auto prog = engine.build(source);
	auto func = prog.get<void()>();

	engine.printAST();
	binary.write(reinterpret_cast<const char*>(prog.data()), prog.size());

	if(func) {
		func();
	}
	return 0;
}