#include "error.hpp"

namespace voidcore {
	lexerror::lexerror(const std::string &msg, std::pair<uint32_t, uint32_t> pos) {
		std::stringstream out;
		out<<"ERROR ["<<pos.first<<":"<<pos.second<<"] "<<msg;
		this->msg = out.str();
	}

	const char* lexerror::what() const throw () {
		return this->msg.c_str();
	}
}