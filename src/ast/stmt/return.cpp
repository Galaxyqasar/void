#include "stmt/return.hpp"

#include <algorithm>

namespace voidcore {
	ReturnStmt::ReturnStmt(Expr *value) : value(value) {}

	void ReturnStmt::build(Assembler *out) {
		if(value) {
			value->build(out);
		}
		if(out->currentStackSize()) {
			out->mov(reg64::rsp, reg64::rbp);
			out->pop(reg64::rbp);
		}
		out->ret();
	}

	void ReturnStmt::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset*2, ' ')<<"<return>\n";
		if(value) {
			value->dump(out, offset + 1);
		}
	}

}