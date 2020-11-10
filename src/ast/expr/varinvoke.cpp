#include "expr/varinvoke.hpp"

namespace voidcore {
	VarInvokeExpr::VarInvokeExpr(VarDecl *var)
	: var(var), Expr(var->getType()) {}

	void VarInvokeExpr::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset * 2, ' ')<<"<varinvoke-expr> '"<<var->signature()<<"'\n";
	}

	void VarInvokeExpr::build(Assembler *out) {
		out->mov(reg64::rax, disp32<reg64>(reg64::rbp, - var->offset - var->size()));
	}
}
