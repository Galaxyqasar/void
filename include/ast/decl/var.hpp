#pragma once

#include <optional>
#include <string>

#include "../node.hpp"

namespace voidcore {
	class VarDecl : public Decl {
	public:
		size_t offset = 0;

		VarDecl(TypeInfo type, const std::string &name, std::optional<Expr*> init = {});
		void build(Assembler *out);
		void dump(std::ostream &out, uint32_t offset = 0) const;
		std::string name() const;
		std::string signature() const;
		bool generatesAssembly() const;

		inline TypeInfo getType() const { return type; }
		inline size_t size() const { return type.size(); }

	private:
		TypeInfo type;
		std::string m_name;
		std::optional<Expr*> init;
	};
}