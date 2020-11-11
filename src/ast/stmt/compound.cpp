#include "stmt/root.hpp"

#include "decl/var.hpp"

#include <iostream>

namespace voidcore {
	CompoundStmt::CompoundStmt() {}
	CompoundStmt::~CompoundStmt() {}

	void CompoundStmt::build(Assembler *out) {
		bool buildDecls = false;
		for(const Stmt *stmt : children) {
			if(stmt->isInstanceOf<Decl>()) {
				const Decl *decl = dynamic_cast<const Decl*>(stmt);
				buildDecls |= !decl->isInline();
			}
		}
		if(buildDecls) {
			Label declEnd;
			out->jmp(&declEnd);
			for(Stmt *stmt : children) {
				Decl *decl = dynamic_cast<Decl*>(stmt);
				if(decl && !decl->isInline()) {
					stmt->build(out);
				}
			}
			out->bind(declEnd);
		}
		for(Stmt *stmt : children) {
			if(!stmt->isInstanceOf<Decl>()) {
				stmt->build(out);
			}
		}
	}

	void CompoundStmt::dump(std::ostream &out, uint32_t offset) const {
		out<<std::string(offset*2, ' ')<<"<compound-stmt>\n";
		for(const Stmt *stmt : children) {
			stmt->dump(out, offset + 1);
		}
	}

	void CompoundStmt::append(Stmt *stmt) {
		if(std::find(children.begin(), children.end(), stmt) == children.end()) {
			children.push_back(stmt);
		}
	}

	Decl* CompoundStmt::getDeclByName(const std::string &name) {
		for(Stmt *stmt : children) {
			if(stmt->isInstanceOf<Decl>()) {
				Decl *decl = dynamic_cast<Decl*>(stmt);
				if(decl->name() == name) {
					return decl;
				}
			}
		}
		return nullptr;
	}

	Decl* CompoundStmt::getDeclBySignature(const std::string &signature) {
		for(Stmt *stmt : children) {
			if(stmt->isInstanceOf<Decl>()) {
				Decl *decl = dynamic_cast<Decl*>(stmt);
				if(decl->signature() == signature) {
					return decl;
				}
			}
		}
		return nullptr;
	}

	void CompoundStmt::calcStack(size_t offset) {
		struct StackSizeCalculator {
			size_t size;
			std::vector<size_t> children;
			StackSizeCalculator(size_t init = 0) : size(init) {}
			size_t finalize() {
				for(const size_t &s : children) {
					size = std::max(size, s);
				}
				return size;
			}
			StackSizeCalculator& operator+=(const size_t &val) {
				size += val;
				return *this;
			}
			void addChildStack(const size_t &val) {
				children.push_back(size + val);
			}
		} calc;

		for(Stmt *stmt : children) {
			if(stmt->isInstanceOf<VarDecl>()) {
				VarDecl *var = reinterpret_cast<VarDecl*>(stmt);
				var->offset = offset;
				offset += var->size();
				calc += var->size();
			}
			else if(stmt->isInstanceOf<CompoundStmt>()) {
				CompoundStmt *child = reinterpret_cast<CompoundStmt*>(stmt);
				child->calcStack(offset);
				calc.addChildStack(child->stackSize);
			}
		}
		stackSize = calc.finalize();
	}
}