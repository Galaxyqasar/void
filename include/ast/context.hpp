#pragma once

#include <ostream>
#include <vector>

#include "node.hpp"
#include "stmt/root.hpp"

namespace voidcore {
	class ASTContext {
	public:
		ASTContext();
		~ASTContext();

		void clear();
		void dump(std::ostream &out) const;
		inline RootStmt* root() { return m_root; }

		template<typename T, typename ...Args>
		T* addNode(Args ...args) {
			T *n = new T(args...);
			nodes.push_back(n);
			return n;
		}

	private:
		friend class Module;

		std::vector<Node*> nodes;
		RootStmt *m_root;
	};
}