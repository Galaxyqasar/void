#pragma once

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
		t_lor, t_land,
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
}