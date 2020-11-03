#include "utils.hpp"

#include <sstream>

namespace voidcore {
	std::string parseOct(std::string source) {
		std::string result(source.length(), '\0');
		for(unsigned i = 0; i < source.length(); i +=3) {
			result[i/3] = parseOct(source[i], source[i+1], source[i+2]);
		}
		return result;
	}
	std::string parseHex(std::string source) {
		std::string result(source.length() / 2, '\0');
		for(unsigned i = 0; i < source.length(); i += 2) {
			result[i/2] = parseHex(source[i], source[i+1]);
		}
		return result;
	}
	std::string parseEscape(std::string source) {
		std::stringstream result;
		for(unsigned i = 0; i < source.size(); i++) {
			if(source[i] == '\\') {
				switch(source[++i]) {
					case '\'': result<<'\''; break;
					case '\"': result<<'\"'; break;
					case '\\': result<<'\\'; break;
					case '0': result<<'\0'; break;
					case 'a': result<<'\a'; break;
					case 'b': result<<'\b'; break;
					case 'f': result<<'\f'; break;
					case 'n': result<<'\n'; break;
					case 'r': result<<'\r'; break;
					case 't': result<<'\t'; break;
					case 'v': result<<'\v'; break;
					case 'x': {
						char u = source[++i], l = source[++i];
						result<<parseHex(u, l);
					} break;
					case 'u': {	// unicode
					} break;
					case 'U': {	// unicode
					} break;
					default: {
						char c = source[i];
						if(c >= '0' && c <= '9') {
							result<<parseOct(source[i+1], source[i+2], source[i+3]);
							i += 3;
						}
					}
				}
			}
			else {
				result<<source[i];
			}
		}
		return result.str();
	}
}