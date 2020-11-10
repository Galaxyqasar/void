#pragma once

#include "../node.hpp"
#include "../decl/function.hpp"

namespace voidcore {
	class CallExpr : public Expr {
	public:
		CallExpr(FunctionDecl *func, const std::vector<Expr*> &args);
		void dump(std::ostream &out, uint32_t offset = 0) const;
		void build(Assembler *out);

	private:
		std::vector<Expr*> args;
		FunctionDecl *func;
	};
}