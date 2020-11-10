#pragma once

#include "../node.hpp"
#include "../decl/var.hpp"

namespace voidcore {
	class VarInvokeExpr : public Expr {
	public:
		VarInvokeExpr(VarDecl *var);
		void dump(std::ostream &out, uint32_t offset = 0) const;
		void build(Assembler *out);

	private:
		VarDecl *var;
	};
}