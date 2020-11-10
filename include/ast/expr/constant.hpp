#pragma once

#include "../node.hpp"

namespace voidcore {
	class ConstantExpr : public Expr {
	public:
		inline ConstantExpr(TypeInfo type) : Expr(type) {}
		virtual uint8_t toSWord() = 0;
		virtual uint16_t toWord() = 0;
		virtual uint32_t toDWord() = 0;
		virtual uint64_t toQWord() = 0;
	};
}