#include "stmt/root.hpp"

#include <algorithm>

namespace voidcore {
	void RootStmt::build(Assembler *out) {
		calcStack();
		out->enter(stackSize);
		if(stackSize > 0) {
			out->push(reg64::rbp);
			out->mov(reg64::rbp, reg64::rsp);
			out->sub(reg64::rsp, uint32_t(stackSize));
		}
		CompoundStmt::build(out);
		if(!contains<ReturnStmt>()) {
			if(stackSize > 0) {
				out->mov(reg64::rsp, reg64::rbp);
				out->pop(reg64::rbp);
			}
			out->ret();
		}
		out->leave();
	}

	void RootStmt::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset*2, ' ')<<"<root-stmt>\n";
		for(const Stmt *stmt : children) {
			stmt->dump(out, offset + 1);
		}
	}

	void RootStmt::clear() {
		children.erase(
			std::remove_if(
				children.begin(),
				children.end(),
				[](const Stmt *stmt) -> bool {
					return !stmt->isInstanceOf<Decl>();
				}
			)
		);
	}
}