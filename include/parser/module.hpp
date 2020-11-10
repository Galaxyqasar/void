#pragma once

#include "asm/assembler.hpp"
#include "ast/context.hpp"

namespace voidcore {
	class Module {
	public:
		Module();
		Module(ASTContext &&context);
		Module(Module &&other);
		~Module();

		Module& operator=(ASTContext &&context);
		Module& operator=(Module &&other);

		std::vector<Decl*>::iterator begin();
		std::vector<Decl*>::iterator end();

		void clear();

	private:
		std::vector<Node*> nodes;
		std::vector<Decl*> decls;

		Module(const ASTContext &context);
		Module(const Module &other);

		Module& operator=(const ASTContext &context);
		Module& operator=(const Module &other);
	};
}