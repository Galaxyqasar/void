#include "../node.hpp"

#include "function.hpp"

#include <string>

namespace voidcore {
	class TypeDecl : public Decl {
	public:
		virtual size_t size() const = 0;
		FunctionDecl* getMemberFuncByName(const std::string &name);
		FunctionDecl* getMemberFuncBySignature(const std::string &signature);

	protected:
		std::vector<Decl*> memberDecls;
	};
}