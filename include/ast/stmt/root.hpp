#pragma once

#include "compound.hpp"
#include "return.hpp"

namespace voidcore {
	class RootStmt : public CompoundStmt {
	public:
		void build(Assembler *out);
		void dump(std::ostream &out, uint32_t offset = 0) const;
		void clear();
	};
}