#pragma once

#include <string>
#include <unordered_map>
#include <variant>

#include "tokens.hpp"

namespace voidcore {
	typedef std::variant<nullptr_t, float, double, int64_t, uint64_t, char, std::string> literal_t;

	const char hextable[] = {
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1, 0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,14,15,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
	};

	const std::unordered_map<std::string, int> keywords = {
		{"pragma", t_pragma}, {"import", t_import},
		{"async", t_async}, {"await", t_await},
		{"delete", t_delete}, {"new", t_new},
		{"if", t_if}, {"else", t_else},
		{"do", t_do}, {"while", t_while}, {"for", t_for},
		{"break", t_break}, {"continue", t_continue},
		{"return", t_return}, {"yield", t_yield},
		{"try", t_try}, {"catch", t_catch}, {"throw", t_throw},
		{"class", t_class}, {"struct", t_struct}, {"union", t_union}, {"enum", t_enum},
		{"typedef", t_typedef}, {"funcdef", t_funcdef},
		{"const", t_const}, {"static", t_static},
		{"inline", t_inline}, {"template", t_template},
		{"sizeof", t_sizeof}, {"typeid", t_typeid},
		{"null", t_null}, {"true", t_true}, {"false", t_false}
	};

	inline std::pair<double, size_t> parseFloat(const char *data) {
		char *end;
		return {strtod(data, &end), end - data};
	}
	inline std::pair<int64_t, size_t> parseInt(const char *data) {
		char *end;
		return {strtol(data, &end, 0), end - data};
	}
	inline std::pair<uint64_t, size_t> parseUInt(const char *data) {
		char *end;
		return {strtoul(data, &end, 0), end - data};
	}

	inline uint8_t parseOct(char upper, char mid, char lower) {
		upper -= '0', lower -= '0', mid -= '0';
		return (upper<<6) + (mid<<3) + lower;	// upper * 8^2 + mid * 8^1 + lower * 8^0
	}
	inline uint8_t parseHex(char upper, char lower) {
		return (hextable[upper]<<4) + hextable[lower];	// upper * 16^1 + lower * 16^0
	}

	std::string parseOct(std::string source);
	std::string parseHex(std::string source);
	std::string parseEscape(std::string source);
}