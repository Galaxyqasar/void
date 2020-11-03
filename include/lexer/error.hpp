#pragma once

#include <stdexcept>
#include <sstream>

namespace voidcore {
	class lexerror : public std::exception {
	public:
		lexerror(const std::string &msg, std::pair<uint32_t, uint32_t> pos);
		const char* what() const throw ();

	private:
		std::string msg;
	};
}