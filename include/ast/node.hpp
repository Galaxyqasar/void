#pragma once

#include <ostream>
#include <cstdint>

#include "asm/assembler.hpp"

namespace voidcore {
	class Node {
	public:
		virtual ~Node();

		virtual void dump(std::ostream &out, uint32_t depth = 0) const = 0;
		virtual void build(Assembler *out) = 0;

		template<typename T>
		constexpr bool isInstanceOf() const {
			return (dynamic_cast<const T*>(this) != nullptr);
		}
	};

	class Stmt : public Node {};

	class Decl : public Stmt {
	public:
		virtual std::string name() const = 0;
		virtual std::string signature() const = 0;
		virtual bool isInline() const = 0;
	};

	class TypeDecl;

	class TypeInfo {
	public:
		TypeInfo(TypeDecl *type, bool isConst = false, bool isStatic = false, size_t ptrCount = 0);
		TypeInfo(const TypeInfo &other) = default;
		TypeInfo& operator=(const TypeInfo &other) = default;
		size_t size() const;

		std::string signature() const;
		bool operator==(const TypeInfo &other) const;

		TypeDecl *base;
		bool isConst, isStatic;
		size_t ptrCount = 0;
	};

	class Expr : public Stmt {
	public:
		inline Expr(const TypeInfo &type) : m_type(type) {}
		inline TypeInfo type() const {
			return m_type;
		}
	protected:
		TypeInfo m_type;
	};
}