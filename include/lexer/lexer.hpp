#pragma once

#include <istream>
#include <string>
#include <unordered_map>
#include <variant>

#include "error.hpp"
#include "tokens.hpp"
#include "utils.hpp"

namespace voidcore {
	class Lexer {
	public:
		Lexer();
		Lexer(std::istream &src);
		Lexer(const std::string &src);

		void setSource(std::istream &src);
		void setSource(const std::string &src);

		uint32_t next();
		uint32_t peek();
		bool accept(uint32_t token);
		void expect(uint32_t token);

		template<typename T>
		T literal() {
			return std::get<T>(l);
		}
		template<typename T>
		T peekliteral() {
			const char *ptmp = p;
			literal_t ltmp = l;
			next();
			literal_t lit = l;
			p = ptmp;
			l = ltmp;
			return lit;
		}

		bool eof();
		void clear();

		std::pair<uint32_t, uint32_t> getCursorPos();

	private:
		std::string src;
		const char *start, *p, *end;
		literal_t l;
	};
}