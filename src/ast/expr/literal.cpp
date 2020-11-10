#include "expr/literal.hpp"

namespace voidcore {
	CharLitExpr::CharLitExpr(char v, TypeDecl *type) : val(v), ConstantExpr(type) {}

	void CharLitExpr::dump(std::ostream& out, uint32_t offset) const {
		out<<std::string(offset * 2, ' ')<<"<char-literal> "<<int(val)<<"\n";
	}

	void CharLitExpr::build(Assembler *out) {
		out->mov(reg8::al, imm8(val));
	}

	uint8_t CharLitExpr::toSWord() {
		return uint8_t(val);
	}

	IntLitExpr::IntLitExpr(int64_t v, TypeDecl *type) : val(v), ConstantExpr(type) {}

	void IntLitExpr::dump(std::ostream& out, uint32_t offset) const {
		out<<std::string(offset * 2, ' ')<<"<int-literal> "<<int(val)<<"\n";
	}

	void IntLitExpr::build(Assembler *out) {
		out->mov(reg64::rax, imm64(val));
	}

	uint8_t IntLitExpr::toSWord() {
		return uint8_t(val);
	}
	uint16_t IntLitExpr::toWord() {
		return uint16_t(val);
	}
	uint32_t IntLitExpr::toDWord() {
		return uint32_t(val);
	}
	uint64_t IntLitExpr::toQWord() {
		return uint64_t(val);
	}

	UIntLitExpr::UIntLitExpr(uint64_t v, TypeDecl *type) : val(v), ConstantExpr(type) {}

	void UIntLitExpr::dump(std::ostream& out, uint32_t offset) const {
		out<<std::string(offset * 2, ' ')<<"<uint-literal> "<<int(val)<<"\n";
	}

	void UIntLitExpr::build(Assembler *out) {
		out->mov(reg64::rax, imm64(val));
	}

	uint8_t UIntLitExpr::toSWord() {
		return uint8_t(val);
	}
	uint16_t UIntLitExpr::toWord() {
		return uint16_t(val);
	}
	uint32_t UIntLitExpr::toDWord() {
		return uint32_t(val);
	}
	uint64_t UIntLitExpr::toQWord() {
		return uint64_t(val);
	}
}