#pragma once

#include "../ast/node.hpp"
#include "ast/decl/type.hpp"

namespace voidcore {
	class VoidTypeDecl : public TypeDecl {
	public:
		void dump(std::ostream &out, uint32_t depth = 0) const;
		void build(Assembler *out);
		std::string name() const;
		std::string signature() const;
		bool isInline() const;
		size_t size() const;
	};
}