#include "module.hpp"

namespace voidcore {
	Module::Module() {}
	Module::Module(ASTContext &&context) {
		nodes = std::move(context.nodes);
		for(Stmt *s : *context.m_root) {
			if(s->isInstanceOf<Decl>()) {
				decls.push_back(dynamic_cast<Decl*>(s));
			}
		}
	}
	Module::Module(Module &&other) {
		nodes = std::move(other.nodes);
	}

	Module::~Module() {
		clear();
	}

	Module& Module::operator=(ASTContext &&context) {
		clear();
		nodes = std::move(context.nodes);
		for(Stmt *s : *context.m_root) {
			if(s->isInstanceOf<Decl>()) {
				decls.push_back(dynamic_cast<Decl*>(s));
			}
		}
		return *this;
	}

	Module& Module::operator=(Module &&other) {
		clear();
		nodes = std::move(other.nodes);
		decls = other.decls;
		return *this;
	}

	std::vector<Decl*>::iterator Module::begin() {
		return decls.begin();
	}

	std::vector<Decl*>::iterator Module::end() {
		return decls.end();
	}

	void Module::clear() {
		decls.clear();
		for(Node *n : nodes) {
			delete n;
		}
		nodes.clear();
	}
}