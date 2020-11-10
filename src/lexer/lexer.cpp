#include "lexer.hpp"

#include <algorithm>

namespace voidcore {
	Lexer::Lexer() {}

	Lexer::Lexer(std::istream &src) {
		load(src);
	}

	Lexer::Lexer(const std::string &src) {
		load(src);
	}

	void Lexer::load(std::istream &src) {
		this->src = std::string((std::istreambuf_iterator<char>(src)), std::istreambuf_iterator<char>());
		p = start = this->src.c_str();
		end = start + this->src.length();
	}

	void Lexer::load(const std::string &src) {
		this->src = src;
		p = start = this->src.c_str();
		end = start + this->src.length();
	}

	uint32_t Lexer::next() {
		char c = '\0';
		while(p < end && (c = *p++)) {
			switch(c) {
				case '\0': return t_eof;
				case '(': return t_openparen;
				case ')': return t_closeparen;
				case '[': return t_openbrak;
				case ']': return t_closebrak;
				case '{': return t_opencurly;
				case '}': return t_closecurly;
				case '?': return t_ternary;
				case ';': return t_semicolon;
				case ',': return t_comma;
				case ' ': case '\t': case '\r': case '\n': break;
				case '.': if(p[0] == '.' && p[1] == '.') return t_expand; else return t_dot;
				case '*': if(*p == '=') { *p++; return t_mula; } else return t_mul;
				case '%': if(*p == '=') { *p++; return t_moda; } else return t_mod;
				case '&': if(*p == '=') { *p++; return t_anda; } else if(*p == '&') { *p++; return t_land; } else return t_and;
				case '|': if(*p == '=') { *p++; return t_ora; } else if(*p == '|') { *p++; return t_lor; } else return t_or;
				case '^': if(*p == '=') { *p++; return t_xora; } else return t_xor;
				case '~': return t_not;
				case '=': if(*p == '=') { *p++; return t_eq; } else return t_assign;
				case '!': if(*p == '=') { *p++; return t_neq; } else return t_lnot;
				case '<': if(*p == '=') { *p++; if(*p == '>') { *p++; return t_comp; } else return t_lseq; } else if(*p == '<') { *p++; if(*p == '=') { *p++; return t_shla; } else return t_shl; } else return t_ls;
				case '>': if(*p == '=') { *p++; return t_greq; } else if(*p == '>') { *p++; if(*p == '=') { *p++; return t_shra; } else return t_shr; } else return t_gr;
				case ':': if(*p == ':') { *p++; return t_scope; } else return t_colon;
				case '\"': {
					const char *tmp = p;
					while(*p && *p != '\"' && p < end) {
						p += (*p == '\\') + 1;
					}
					l = parseEscape(std::string(tmp, p++));
					return t_str;
				} break;
				case '\'': {
					const char *tmp = p;
					while(*p && *p != '\'' && p < end) {
						p += (*p == '\\') + 1;
					}
					l = parseEscape(std::string(tmp, p++))[0];
					return t_char;
				} break;
				case '/': {
					char n = *p++;
					if(n == '/') {	// single line comment until \n or eof
						while(n != '\n' && p < end) {
							n = *p++;
						}
					}
					else if(n == '*') {	// multiline comment until */ or eof
						char current = *p++, n = *p++;
						while(current != '*' && n !='/' && p < end) {
							current = n;
							n = *p++;
						}
					}
					else if(n == '=') {
						return t_diva;
					}
					else {
						return t_div;
					}
				} break;
				default: {
					if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') {
						const char *istart = p - 1;
						while(((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9') || *p == '_') && p <= end) {
							p++;
						}
						std::string id = std::string(istart, p);
						if(keywords.count(id)) {
							return keywords.at(id);
						}
						else {
							l = id;
							return t_id;
						}
					}
					else {	// try to parse number or '+' / '-'
						// parse number
						auto [f, sf] = parseFloat(p - 1);
						auto [i, si] = parseInt(p - 1);
						auto [u, su] = parseUInt(p - 1);
						size_t s = std::max({sf, si, su});
						if(s) {	// number found!
							p += s - 1;
							if(s == su && c != '-') {
								l = uint64_t(u);
								return t_uint;
							}
							else if(s == si) {
								l = int64_t(i);
								return t_int;
							}
							else if(s == sf) {
								if(*p == 'f') {
									p++;
									l = float(f);
									return t_float;
								}
								else {
									l = f;
									return t_double;
								}
							}
						}
						else if(c == '+') {
							if(*p == '=') {
								p++;
								return t_adda;
							}
							else if(*p == '+') {
								p++;
								return t_inc;
							}
							return t_add;
						}
						else if(c == '-') {
							if(*p == '=') {
								p++;
								return t_suba;
							}
							else if(*p == '-') {
								p++;
								return t_dec;
							}
							else if(*p == '>') {
								p++;
								return t_arrow;
							}
							return t_sub;
						}
					}
				}
			}
		}
		return t_eof;
	}

	uint32_t Lexer::peek() {
		const char *ptmp = p;
		literal_t ltmp = l;
		uint32_t tk = next();
		p = ptmp;
		l = ltmp;
		return tk;
	}
	bool Lexer::accept(uint32_t token) {
		if(peek() == token) {
			next();
			return true;
		}
		return false;
	}
	void Lexer::expect(uint32_t token) {
		int current = next();
		if(current != token) {
			throw lexerror("unexpected token " + tokenMap.at(current) + " expected " + tokenMap.at(token), getCursorPos());
		}
	}
	bool Lexer::eof() {
		return peek() == t_eof;
	}

	void Lexer::clear() {
		src.clear();
		start = p = end = nullptr;
		l = nullptr;
	}

	std::pair<uint32_t, uint32_t> Lexer::getCursorPos() {
		uint32_t line = 0, col = 0;
		for(const char *cursor = start; cursor <= p; cursor++, col++) {
			if(*cursor == '\n') {
				line++;
				col = 0;
			}
		}
		return {line, col};
	}
}