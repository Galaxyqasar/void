#include "node.hpp"

namespace voidcore {
	Node::~Node() {}

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