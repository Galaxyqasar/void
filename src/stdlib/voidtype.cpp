#include "voidtype.hpp"

namespace voidcore {
	// this type doesn't hold data
	size_t VoidTypeDecl::size() const {
		return 0;
	}

	void VoidTypeDecl::dump(std::ostream &out, uint32_t depth) const {
		out<<std::string(depth * 2, ' ')<<"<void>\n";
	}
	// this type doesn't do anything
	void VoidTypeDecl::build(Assembler *out) {}

	std::string VoidTypeDecl::name() const {
		return "void";
	}
	std::string VoidTypeDecl::signature() const {
		return "void";
	}

	bool VoidTypeDecl::generatesAssembly() const {
		return false;
	}
}