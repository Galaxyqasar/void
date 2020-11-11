#pragma once

#include "../node.hpp"
#include "../stmt/compound.hpp"

#include <optional>

namespace voidcore {
	class ParamDecl : public Decl {
	public:
		ParamDecl(TypeInfo type, const std::string &name, std::optional<Expr*> init = {});
		void build(Assembler *out);
		void dump(std::ostream &out, uint32_t offset = 0) const;
		std::string name() const;
		std::string signature() const;
		bool isInline() const;

	private:
		friend class FunctionDecl;

		TypeInfo type;
		std::string m_name;
		std::optional<Expr*> init;
	};

	class FunctionDecl : public Decl {
	public:
		FunctionDecl(TypeInfo returnType, const std::string &name,
					 const std::vector<ParamDecl*> &parameters,
					 bool isConst, bool isStatic, CompoundStmt *body = nullptr);
		void build(Assembler *out);
		void dump(std::ostream &out, uint32_t offset = 0) const;
		std::string name() const;
		std::string signature() const;
		bool isInline() const;

		inline TypeInfo getReturnType() { return returnType; }
		inline Label* getAddr() { return &addr; }
		inline void setBody(CompoundStmt *body) { this->body = body; }

	private:
		TypeInfo returnType;
		std::string m_name;
		std::vector<ParamDecl*> parameters;
		bool isConst, isStatic;
		CompoundStmt *body;
		Label addr;
	};
}