#pragma once

#include "constant.hpp"

namespace voidcore {
	class CharLitExpr : public ConstantExpr {
	public:
		CharLitExpr(char v, TypeDecl *type);

		void dump(std::ostream& out, uint32_t offset = 0) const;
		void build(Assembler *out);

		uint8_t toSWord();

	private:
		uint8_t val;
	};

	class IntLitExpr : public ConstantExpr {
	public:
		IntLitExpr(int64_t v, TypeDecl *type);

		void dump(std::ostream& out, uint32_t offset = 0) const;
		void build(Assembler *out);

		uint8_t toSWord();
		uint16_t toWord();
		uint32_t toDWord();
		uint64_t toQWord();

	private:
		int64_t val;
	};

	class UIntLitExpr : public ConstantExpr {
	public:
		UIntLitExpr(uint64_t v, TypeDecl *type);

		void dump(std::ostream& out, uint32_t offset = 0) const;
		void build(Assembler *out);

		uint8_t toSWord();
		uint16_t toWord();
		uint32_t toDWord();
		uint64_t toQWord();

	private:
		uint64_t val;
	};
}