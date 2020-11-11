#include "decl/function.hpp"

#include "stmt/return.hpp"

#include <sstream>

namespace voidcore {
	ParamDecl::ParamDecl(TypeInfo type, const std::string &name, std::optional<Expr*> init)
	: type(type), m_name(name), init(init) {}

	void ParamDecl::build(Assembler *out) {}

	void ParamDecl::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset * 2, ' ')<<"<param-decl> '"<<signature()<<"'\n";
		if(init) {
			init.value()->dump(out, offset + 1);
		}
	}

	std::string ParamDecl::name() const {
		return m_name;
	}

	std::string ParamDecl::signature() const {
		std::stringstream result;
		result<<type.signature() + " " + m_name;
		if(init) {
			result<<" = ";
			init.value()->dump(result, 0);
		}
		return result.str();
	}

	bool ParamDecl::isInline() const {
		return false;
	}


	FunctionDecl::FunctionDecl(TypeInfo returnType, const std::string &name, const std::vector<ParamDecl*> &parameters, bool isConst, bool isStatic, CompoundStmt *body)
	: returnType(returnType), m_name(name), parameters(parameters), isConst(isConst), isStatic(isStatic), body(body) {}

	void FunctionDecl::build(Assembler *out) {
		out->bind(addr);
		body->calcStack();
		out->enter(body->stackSize);
		if(out->currentStackSize() > 0) {
			out->push(reg64::rbp);
			out->mov(reg64::rbp, reg64::rsp);
			out->sub(reg64::rsp, imm32(out->currentStackSize()));
		}
		body->build(out);
		if(!body->contains<ReturnStmt>()) {
			if(out->currentStackSize() > 0) {
				out->mov(reg64::rsp, reg64::rbp);
				out->pop(reg64::rbp);
			}
			out->ret();
		}
		out->leave();
	}

	void FunctionDecl::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset*2, ' ')<<"<function-decl> '"<<signature()<<"'\n";
		for(ParamDecl *p : parameters) {
			p->dump(out, offset + 1);
		}
		body->dump(out, offset + 1);
	}

	std::string FunctionDecl::name() const {
		return m_name;
	}

	std::string FunctionDecl::signature() const {
		std::string result = returnType.signature() + " ";
		result += m_name + "(";
		for(unsigned i = 0; i < parameters.size(); i++) {
			if(i) result += ",";
			result += parameters[i]->signature();
		}
		result += ")";
		if(isConst)
			result += " const";
		if(isStatic)
			result += " static";
		return result;
	}

	bool FunctionDecl::isInline() const {
		return false;
	}
}