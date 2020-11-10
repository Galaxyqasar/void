#include "engine.hpp"

#include <iostream>

#include "stdlib/stdint.hpp"

namespace voidcore {
	Engine::Engine() : lexer(), context(), parser(lexer, context), assembler() {
		parser.addModule("stdint", stdint::generateModule());
	}
	Engine::~Engine() {}

	void Engine::load(const std::string &source) {
		lexer.load(source);
	}

	void Engine::load(std::istream &source) {
		lexer.load(source);
	}

	void Engine::parse() {
		while(!lexer.eof()) {
			parser.next();
		}
	}

	Program Engine::build() {
		context.root()->build(&assembler);
		return assembler.build();
	}

	Program Engine::build(std::istream &source) {
		load(source);
		parse();
		return build();
	}

	Program Engine::build(const std::string &source) {
		load(source);
		parse();
		return build();
	}

	void Engine::clear() {
		context.clear();
	}

	void Engine::printAST() const {
		context.dump(std::cout);
	}

	void Engine::runLine(const std::string &source) {
		Program prog = build();
		funcptr_t<void()> root = prog.get<void()>();
		if(root) {
			root();
		}
		clear();
	}
}
