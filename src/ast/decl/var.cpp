#include "decl/var.hpp"
#include "expr/constant.hpp"

namespace voidcore {
	VarDecl::VarDecl(TypeInfo type, const std::string &name, std::optional<Expr*> init)
	: type(type), m_name(name), init(init) {}

	void VarDecl::build(Assembler *out) {
		if(init) {
			Expr *expr = init.value();
			if(expr->isInstanceOf<ConstantExpr>() && type.size() <= 4) {
				ConstantExpr *constant = reinterpret_cast<ConstantExpr*>(expr);
				switch(type.size()) {
					case 1: out->mov(disp32<reg64>(reg64::rbp, - offset - size()), imm8 (constant->toSWord())); break;
					case 2: out->mov(disp32<reg64>(reg64::rbp, - offset - size()), imm16(constant->toWord ())); break;
					case 4: out->mov(disp32<reg64>(reg64::rbp, - offset - size()), imm32(constant->toDWord())); break;
				}
			}
			else {
				init.value()->build(out);
				switch(type.size()) {
					case 1: out->mov(disp32<reg64>(reg64::rbp, - offset - size()), reg8 ::al ); break;
					case 2: out->mov(disp32<reg64>(reg64::rbp, - offset - size()), reg16::ax ); break;
					case 4: out->mov(disp32<reg64>(reg64::rbp, - offset - size()), reg32::eax); break;
					case 8: out->mov(disp32<reg64>(reg64::rbp, - offset - size()), reg64::rax); break;
					default: {} break;
				}
			}
		}
	}

	void VarDecl::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset * 2, ' ')<<"<vardecl> '"<<signature()<<"'\n";
		if(init) {
			init.value()->dump(out, offset + 1);
		}
	}

	std::string VarDecl::name() const {
		return m_name;
	}

	std::string VarDecl::signature() const {
		return type.signature() + " " + m_name;
	}

	bool VarDecl::generatesAssembly() const {
		return true;
	}
}