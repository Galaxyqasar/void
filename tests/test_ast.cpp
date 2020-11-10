#include <cassert>
#include <iostream>

#include "ast/node.hpp"
#include "ast/context.hpp"

using namespace voidcore;

class testStmt : public Stmt {
	void dump(std::ostream &out, uint32_t offset) const {}
	void build(Assembler *out) {}
};
class testExpr : public Expr {
	void dump(std::ostream &out, uint32_t offset) const {}
	void build(Assembler *out) {}
public:
	testExpr() : Expr(TypeInfo(nullptr)) {}
};
class testDecl : public Decl {
	void dump(std::ostream &out, uint32_t offset) const {}
	void build(Assembler *out) {}
	std::string name() const { return ""; }
	std::string signature() const { return ""; }
	bool generatesAssembly() const { return false; }
};
class testStmt2 : public testStmt {};
class testExpr2 : public testExpr {};
class testDecl2 : public testDecl {};

void test_isInstanceOf() {
	Node *test_stmt = new testStmt;
	Node *test_expr = new testExpr;
	Node *test_decl = new testDecl;
	Node *test_stmt_2 = new testStmt2;
	Node *test_expr_2 = new testExpr2;
	Node *test_decl_2 = new testDecl2;

	std::cout<<"testStmt  isInstanceOf Stmt:      "<<(test_stmt  ->isInstanceOf<Stmt     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testStmt  isInstanceOf Expr:      "<<(test_stmt  ->isInstanceOf<Expr     >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testStmt  isInstanceOf Decl:      "<<(test_stmt  ->isInstanceOf<Decl     >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testStmt2 isInstanceOf Stmt:      "<<(test_stmt_2->isInstanceOf<Stmt     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testStmt2 isInstanceOf Expr:      "<<(test_stmt_2->isInstanceOf<Expr     >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testStmt2 isInstanceOf Decl:      "<<(test_stmt_2->isInstanceOf<Decl     >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testStmt  isInstanceOf testStmt:  "<<(test_stmt  ->isInstanceOf<testStmt >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testStmt  isInstanceOf testExpr:  "<<(test_stmt  ->isInstanceOf<testExpr >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testStmt  isInstanceOf testDecl:  "<<(test_stmt  ->isInstanceOf<testDecl >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testStmt2 isInstanceOf testStmt:  "<<(test_stmt_2->isInstanceOf<testStmt >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testStmt2 isInstanceOf testStmt2: "<<(test_stmt_2->isInstanceOf<testStmt2>() ? "true " : "false")<<" (true )\n";
	std::cout<<"testExpr  isInstanceOf Expr:      "<<(test_expr  ->isInstanceOf<Expr     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testExpr  isInstanceOf Stmt:      "<<(test_expr  ->isInstanceOf<Stmt     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testExpr  isInstanceOf Decl:      "<<(test_expr  ->isInstanceOf<Decl     >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testExpr2 isInstanceOf Expr:      "<<(test_expr_2->isInstanceOf<Expr     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testExpr2 isInstanceOf Stmt:      "<<(test_expr_2->isInstanceOf<Stmt     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testExpr2 isInstanceOf Decl:      "<<(test_expr_2->isInstanceOf<Decl     >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testExpr  isInstanceOf testExpr:  "<<(test_expr  ->isInstanceOf<testExpr >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testExpr  isInstanceOf testStmt:  "<<(test_expr  ->isInstanceOf<testStmt >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testExpr  isInstanceOf testDecl:  "<<(test_expr  ->isInstanceOf<testDecl >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testExpr2 isInstanceOf testExpr:  "<<(test_expr_2->isInstanceOf<testExpr >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testExpr2 isInstanceOf testExpr2: "<<(test_expr_2->isInstanceOf<testExpr2>() ? "true " : "false")<<" (true )\n";
	std::cout<<"testDecl  isInstanceOf Decl:      "<<(test_decl  ->isInstanceOf<Decl     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testDecl  isInstanceOf Stmt:      "<<(test_decl  ->isInstanceOf<Stmt     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testDecl  isInstanceOf Expr:      "<<(test_decl  ->isInstanceOf<Expr     >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testDecl2 isInstanceOf Decl:      "<<(test_decl_2->isInstanceOf<Decl     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testDecl2 isInstanceOf Stmt:      "<<(test_decl_2->isInstanceOf<Stmt     >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testDecl2 isInstanceOf Expr:      "<<(test_decl_2->isInstanceOf<Expr     >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testDecl  isInstanceOf testDecl:  "<<(test_decl  ->isInstanceOf<testDecl >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testDecl  isInstanceOf testStmt:  "<<(test_decl  ->isInstanceOf<testStmt >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testDecl  isInstanceOf testExpr:  "<<(test_decl  ->isInstanceOf<testExpr >() ? "true " : "false")<<" (false)\n";
	std::cout<<"testDecl2 isInstanceOf testDecl:  "<<(test_decl_2->isInstanceOf<testDecl >() ? "true " : "false")<<" (true )\n";
	std::cout<<"testDecl2 isInstanceOf testDecl2: "<<(test_decl_2->isInstanceOf<testDecl2>() ? "true " : "false")<<" (true )\n";

	//assert(node->isInstanceOf<Stmt>());
}

int main() {
	test_isInstanceOf();
	return 0;
}