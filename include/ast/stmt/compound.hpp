#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "../node.hpp"

namespace voidcore {
	class CompoundStmt : public Stmt {
	public:
		CompoundStmt();
		virtual ~CompoundStmt();

		virtual void build(Assembler *out);
		virtual void dump(std::ostream &out, uint32_t offset = 0) const;

		inline std::vector<Stmt*>::iterator begin() {
			return children.begin();
		}

		inline std::vector<Stmt*>::iterator end() {
			return children.end();
		}

		template<typename T>
		bool contains() const {
			for(const Stmt *child : children) {
				if(child->isInstanceOf<T>()) {
					return true;
				}
			}
			return false;
		}

		void append(Stmt *stmt);

		Decl* getDeclByName(const std::string &name);
		Decl* getDeclBySignature(const std::string &signature);

		void calcStack(size_t offset = 0);

	protected:
		std::unordered_map<std::string, Decl*> declarations = {};
		std::vector<Stmt*> children = {};
		size_t stackSize;

		friend class FunctionDecl;
	};
}