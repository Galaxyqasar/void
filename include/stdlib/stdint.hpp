#pragma once

#include "ast/node.hpp"
#include "parser/module.hpp"

namespace voidcore {
	namespace stdint {
		class Int8TypeDecl : public TypeDecl {
			void dump(std::ostream &out, uint32_t offset = 0) const;
			void build(Assembler *out);
			std::string name() const;
			std::string signature() const;
			bool generatesAssembly() const;
			size_t size() const;
		};

		class UInt8TypeDecl : public TypeDecl {
			void dump(std::ostream &out, uint32_t offset = 0) const;
			void build(Assembler *out);
			std::string name() const;
			std::string signature() const;
			bool generatesAssembly() const;
			size_t size() const;
		};

		class Int16TypeDecl : public TypeDecl {
			void dump(std::ostream &out, uint32_t offset = 0) const;
			void build(Assembler *out);
			std::string name() const;
			std::string signature() const;
			bool generatesAssembly() const;
			size_t size() const;
		};

		class UInt16TypeDecl : public TypeDecl {
			void dump(std::ostream &out, uint32_t offset = 0) const;
			void build(Assembler *out);
			std::string name() const;
			std::string signature() const;
			bool generatesAssembly() const;
			size_t size() const;
		};

		class Int32TypeDecl : public TypeDecl {
			void dump(std::ostream &out, uint32_t offset = 0) const;
			void build(Assembler *out);
			std::string name() const;
			std::string signature() const;
			bool generatesAssembly() const;
			size_t size() const;
		};

		class UInt32TypeDecl : public TypeDecl {
			void dump(std::ostream &out, uint32_t offset = 0) const;
			void build(Assembler *out);
			std::string name() const;
			std::string signature() const;
			bool generatesAssembly() const;
			size_t size() const;
		};

		class Int64TypeDecl : public TypeDecl {
			void dump(std::ostream &out, uint32_t offset = 0) const;
			void build(Assembler *out);
			std::string name() const;
			std::string signature() const;
			bool generatesAssembly() const;
			size_t size() const;
		};

		class UInt64TypeDecl : public TypeDecl {
			void dump(std::ostream &out, uint32_t offset = 0) const;
			void build(Assembler *out);
			std::string name() const;
			std::string signature() const;
			bool generatesAssembly() const;
			size_t size() const;
		};

		Module generateModule();
	}
}