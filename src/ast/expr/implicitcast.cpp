#include "expr/implicitcast.hpp"

namespace voidcore {
	ImplicitCastExpr::ImplicitCastExpr(Expr *e, TypeInfo dsttype)
	: expr(e), Expr(dsttype) {}

	void ImplicitCastExpr::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset * 2, ' ')<<"<implicitcast-expr> ";
		out<<expr->type().signature()<<" -> "<<type().signature()<<"\n";
		expr->dump(out, offset + 1);
	}

	void ImplicitCastExpr::build(Assembler *out) {
		expr->build(out);
	}
}