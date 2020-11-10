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
		virtual bool generatesAssembly() const = 0;
	};

	class TypeDecl : public Decl {
	public:
		virtual size_t size() const = 0;
	};

	class TypeInfo {
	public:
		inline TypeInfo(TypeDecl *type, bool isConst = false, bool isStatic = false, size_t ptrCount = 0)
		: base(type), isConst(isConst), isStatic(isStatic), ptrCount(ptrCount) {}
		inline TypeInfo(const TypeInfo &other) = default;
		inline TypeInfo& operator=(const TypeInfo &other) = default;
		inline size_t size() const { return base->size(); }

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