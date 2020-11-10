#pragma once

#include <string>
#include <unordered_map>

namespace voidcore {
	enum token : uint32_t {
		t_eof,	// end of file
		t_id,	// identifier
		// literals:
		t_int, t_uint,
		t_float, t_double,
		t_str, t_char,
		// keywords:
		t_pragma, t_import,
		t_async, t_await,
		t_delete, t_new,
		t_if, t_else,
		t_do, t_while, t_for,
		t_break, t_continue,
		t_return, t_yield,
		t_try, t_catch, t_throw,
		t_class, t_struct, t_union, t_enum,
		t_typedef, t_funcdef,
		t_const, t_static,
		t_inline, t_template,
		t_sizeof, t_typeid,
		t_null, t_true, t_false,
		// operators
		t_comma, t_semicolon,
		t_assign,
		t_adda, t_suba,
		t_mula, t_diva, t_moda,
		t_anda, t_ora, t_xora,
		t_shla, t_shra,
		t_ternary, t_colon,
		t_land, t_lor,
		t_and, t_or, t_xor,
		t_eq, t_neq,
		t_ls, t_lseq, t_gr, t_greq,
		t_comp,
		t_shl, t_shr,
		t_add, t_sub,
		t_mul, t_div, t_mod,
		t_not, t_lnot,
		t_inc, t_dec,
		t_dot, t_arrow,
		t_scope, t_expand,
		// brackets:
		t_openparen, t_closeparen,
		t_openbrak, t_closebrak,
		t_opencurly, t_closecurly
	};

	static const std::unordered_map<int, std::string> tokenMap = {
		{t_eof, "eof"},
		{t_id, "identifier"},
		{t_int, "int-literal"}, {t_uint, "uint-literal"},
		{t_float, "float-literal"}, {t_double, "float-literal"},
		{t_str, "string-literal"}, {t_char, "char-literal"},
		{t_pragma, "pragma"}, {t_import, "import"},
		{t_async, "async"}, {t_await, "await"},
		{t_delete, "delete"}, {t_new, "new"},
		{t_if, "if"}, {t_else, "else"},
		{t_do, "do"}, {t_while, "while"}, {t_for, "for"},
		{t_break, "break"}, {t_continue, "continue"},
		{t_return, "return"}, {t_yield, "yield"},
		{t_try, "try"}, {t_catch, "catch"}, {t_throw, "throw"},
		{t_class, "class"}, {t_struct, "struct"},
		{t_union, "union"}, {t_enum, "enum"},
		{t_typedef, "typedef"}, {t_funcdef, "funcdef"},
		{t_const, "const"}, {t_static, "static"},
		{t_inline, "inline"}, {t_template, "template"},
		{t_sizeof, "sizeof"}, {t_typeid, "typeid"},
		{t_null, "null"}, {t_true, "true"}, {t_false, "false"},
		{t_comma, ","}, {t_semicolon, ";"},
		{t_assign, "="},
		{t_adda, "+="}, {t_suba, "-="},
		{t_mula, "*="}, {t_diva, "/="}, {t_moda, "%="},
		{t_anda, "&="}, {t_ora, "|="}, {t_xora, "^="},
		{t_shla, "<<="}, {t_shra, ">>="},
		{t_ternary, "?"}, {t_colon, ":"},
		{t_land, "&&"}, {t_lor, "||"},
		{t_and, "&"}, {t_or, "|"}, {t_xor, "^"},
		{t_eq, "=="}, {t_neq, "!="},
		{t_ls, "<"}, {t_lseq, "<="}, {t_gr, ">"}, {t_greq, ">="},
		{t_comp, "<=>"},
		{t_shl, "<<"}, {t_shr, ">>"},
		{t_add, "+"}, {t_sub, "-"},
		{t_mul, "*"}, {t_div, "/"}, {t_mod, "%"},
		{t_not, "~"}, {t_lnot, "!"},
		{t_inc, "++"}, {t_dec, "--"},
		{t_dot, "."}, {t_arrow, "->"},
		{t_scope, "::"}, {t_expand, "..."},
		{t_openparen, "("}, {t_closeparen, ")"},
		{t_openbrak, "["}, {t_closebrak, "]"},
		{t_opencurly, "{"}, {t_closecurly, "}"}
	};
}