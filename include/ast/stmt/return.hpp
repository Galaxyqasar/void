#pragma once

#include "../node.hpp"

namespace voidcore {
	class ReturnStmt : public Stmt {
	public:
		ReturnStmt(Expr* value = nullptr);

		void build(Assembler *out);
		void dump(std::ostream &out, uint32_t offset = 0) const;

	private:
		Expr* value;
	};
}