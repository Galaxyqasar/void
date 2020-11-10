#include "expr/call.hpp"

namespace voidcore {
	CallExpr::CallExpr(FunctionDecl *func, const std::vector<Expr*> &args)
	: func(func), args(args), Expr(func->getReturnType()) {}

	void CallExpr::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset*2, ' ')<<"<call-expr> '"<<func->signature()<<"'\n";
		for(const Expr *arg : args) {
			arg->dump(out, offset + 1);
		}
	}

	void CallExpr::build(Assembler *out) {
		for(int i = args.size() - 1; i >= 0; i--) {
			Expr *arg = args[i];
			// build arg and prepare it for function call
		}
		out->mov(reg64::rax, reg64::rsp);
		out->call(func->getAddr());
	}
}