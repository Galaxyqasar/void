#include "node.hpp"

#include "decl/type.hpp"

namespace voidcore {
	Node::~Node() {}


	TypeInfo::TypeInfo(TypeDecl *type, bool isConst, bool isStatic, size_t ptrCount)
	: base(type), isConst(isConst), isStatic(isStatic), ptrCount(ptrCount) {}

	size_t TypeInfo::size() const {
		return base->size();
	}

	std::string TypeInfo::signature() const {
		std::string result;
		if(isConst) result += "const ";
		if(isStatic) result += "static ";
		result += base->signature();
		result += std::string(ptrCount, '*');
		return result;
	}

	bool TypeInfo::operator==(const TypeInfo &other) const {
		return base == other.base
			&& isConst == other.isConst
			&& isStatic == other.isStatic
			&& ptrCount == other.ptrCount;
	}
}