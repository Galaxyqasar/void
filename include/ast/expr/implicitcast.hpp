#pragma once

#include "../node.hpp"

namespace voidcore {
	class ImplicitCastExpr : public Expr {
	public:
		ImplicitCastExpr(Expr *e, TypeInfo dsttype);
		void dump(std::ostream &out, uint32_t offset = 0) const;
		void build(Assembler *out);

	private:
		Expr *expr;
	};
}