#pragma once

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "ast/node.hpp"
#include "ast/context.hpp"
#include "asm/assembler.hpp"

namespace voidcore {
	class Engine {
	public:
		Engine();
		~Engine();

		void load(const std::string &source);
		void load(std::istream &source);
		void parse();
		Program build();
		Program build(std::istream &source);
		Program build(const std::string &source);
		void clear();
		void printAST() const;
		void runLine(const std::string &source);

	private:
		Lexer lexer;
		ASTContext context;
		Parser parser;
		Assembler assembler;
	};
}