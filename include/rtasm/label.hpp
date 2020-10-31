#pragma once

#include <cstdint>
#include <limits>
#include <vector>

namespace rtasm {
	struct Label {
		std::vector<uint64_t> uses = {};
		uint64_t dst = std::numeric_limits<uint64_t>::max();

		inline Label() {}
		inline Label(const Label &other) : uses(other.uses), dst(other.dst) {}
		inline Label& operator=(const Label &other) {
			uses = other.uses;
			dst = other.dst;
			return *this;
		}
	};
}