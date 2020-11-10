#pragma once

#include <unordered_map>
#include <vector>

#include "lexer/lexer.hpp"
#include "lexer/tokens.hpp"

#include "ast/node.hpp"
#include "ast/context.hpp"

#include "ast/decl/function.hpp"
#include "ast/decl/var.hpp"

#include "ast/expr/call.hpp"
#include "ast/expr/constant.hpp"
#include "ast/expr/implicitcast.hpp"
#include "ast/expr/literal.hpp"
#include "ast/expr/varinvoke.hpp"

#include "ast/stmt/compound.hpp"
#include "ast/stmt/return.hpp"
#include "ast/stmt/root.hpp"

#include "module.hpp"

namespace voidcore {
	class Parser {
	public:
		Parser(Lexer &lexer, ASTContext &context);

		// parse next pragma / import / decl / stmt in root (decls are stmts)
		void next();
		void addModule(std::string name, Module &&module);

	protected:
		friend class Engine;

		template<typename T, typename ...Args>
		T* addLocalType(Args ...args) {
			T* type = context.addNode<T>(args...);
			scopeStack.back()->append(type, type->signature());
			return type;
		}

		template<typename T, typename ...Args>
		T* addGlobalType(Args ...args) {
			T* type = context.addNode<T>(args...);
			scopeStack[0]->append(type);
			return type;
		}

		Decl* findDeclByName(const std::string &name);
		Decl* findDeclBySignature(const std::string &signature);

		VarDecl* findVarByName(const std::string &name);
		TypeDecl* findTypeByName(const std::string &name);
		FunctionDecl* findFunctionByName(const std::string &name);

		// parsing functions
		void pragma();
		void import();

		Stmt* stmt();
		Expr* expr();
		Decl* decl();	// generic decl, starts with static / const / type -> function / var

		// specific parsing functions
		TypeInfo parseType();

		ReturnStmt* returnStmt();
		CompoundStmt* compoundStmt();

		IntLitExpr* intLitExpr();
		UIntLitExpr* uintLitExpr();
		VarInvokeExpr* varInvokeExpr();
		CallExpr* callExpr();

	private:
		Lexer &lexer;
		ASTContext &context;

		std::vector<TypeInfo> rtypeStack;
		std::vector<CompoundStmt*> scopeStack;

		std::unordered_map<std::string, Module> modules;
	};
}