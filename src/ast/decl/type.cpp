#include "decl/type.hpp"

namespace voidcore {
	FunctionDecl* TypeDecl::getMemberFuncByName(const std::string &name) {
		for(Decl *member : memberDecls) {
			if(member->isInstanceOf<FunctionDecl>()) {
				FunctionDecl *decl = dynamic_cast<FunctionDecl*>(member);
				if(decl->name() == name) {
					return decl;
				}
			}
		}
		return nullptr;
	}

	FunctionDecl* TypeDecl::getMemberFuncBySignature(const std::string &signature) {
		for(Decl *member : memberDecls) {
			if(member->isInstanceOf<FunctionDecl>()) {
				FunctionDecl *decl = dynamic_cast<FunctionDecl*>(member);
				if(decl->signature() == signature) {
					return decl;
				}
			}
		}
		return nullptr;
	}
}