#include "lexer/lexer.hpp"

#include <cassert>

void test_empty() {
	voidcore::Lexer lexer(R"()");
	assert(lexer.eof());
}

void test_whitespace() {
	voidcore::Lexer lexer("  \t\t   \n\n  \t  \n");
	assert(lexer.eof());
}

void test_comments() {
	voidcore::Lexer lexer(R"(
this_is_a_identifier
// this is a comment
second_identifier
/*
	multiline comment
*/
another_identifier
)");

	assert(!lexer.eof());

	lexer.expect(voidcore::t_id);
	assert(lexer.literal<std::string>() == "this_is_a_identifier");

	lexer.expect(voidcore::t_id);
	assert(lexer.literal<std::string>() == "second_identifier");

	lexer.expect(voidcore::t_id);
	assert(lexer.literal<std::string>() == "another_identifier");

	assert(lexer.eof());
}

void test_parseNumbers() {
	voidcore::Lexer lexer(R"(
12345	// unsigned int
-1234	// signed int
1.234	// double
1.23f	// float
)");

	assert(!lexer.eof());

	lexer.expect(voidcore::t_uint);
	assert(lexer.literal<uint64_t>() == 12345);

	lexer.expect(voidcore::t_int);
	assert(lexer.literal<uint64_t>() == -1234);

	lexer.expect(voidcore::t_double);
	assert(abs(lexer.literal<uint64_t>() - 1.234) < 0.0001);

	lexer.expect(voidcore::t_float);
	assert(abs(lexer.literal<uint64_t>() - 1.23f) < 0.0001);

	assert(lexer.eof());
}

int main() {
	test_empty();
	return 0;
}