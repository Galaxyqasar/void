#include "context.hpp"

namespace voidcore {
	ASTContext::ASTContext() {
		m_root = addNode<RootStmt>();
	}

	ASTContext::~ASTContext() {
		for(Node *n : nodes) {
			delete n;
		}
		nodes.clear();
	}

	void ASTContext::clear() {
		for(Node *n : nodes) {
			delete n;
		}
		nodes.clear();
	}

	void ASTContext::dump(std::ostream &out) const {
		m_root->dump(out);
	}
}