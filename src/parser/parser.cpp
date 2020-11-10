#include "parser.hpp"

#include "stdlib/voidtype.hpp"

#include <iostream>

namespace voidcore {
	Parser::Parser(Lexer &lexer, ASTContext &context) : lexer(lexer), context(context) {
		scopeStack.push_back(context.root());

		TypeDecl *void_t = addGlobalType<VoidTypeDecl>();
		rtypeStack.push_back(void_t);
	}

	void Parser::next() {
		switch(lexer.peek()) {
			case t_pragma: {
				pragma();
			} break;
			case t_import: {
				import();
			} break;
			default: {
				Stmt *s = stmt();
				context.root()->append(s);
			} break;
		}
	}

	void Parser::addModule(std::string name, Module &&module) {
		modules[name] = std::move(module);
	}

	Decl* Parser::findDeclByName(const std::string &name) {
		for(int i = scopeStack.size() - 1; i >= 0; i--) {
			CompoundStmt *scope = scopeStack[i];
			Decl *decl = scope->getDeclByName(name);
			if(decl) {
				return decl;
			}
		}
		return nullptr;
	}
	Decl* Parser::findDeclBySignature(const std::string &signature) {
		for(int i = scopeStack.size() - 1; i >= 0; i--) {
			CompoundStmt *scope = scopeStack[i];
			Decl *decl = scope->getDeclBySignature(signature);
			if(decl) {
				return decl;
			}
		}
		return nullptr;
	}

	VarDecl* Parser::findVarByName(const std::string &name) {
		for(int i = scopeStack.size() - 1; i >= 0; i--) {
			CompoundStmt *scope = scopeStack[i];
			Decl *decl = scope->getDeclByName(name);
			if(decl && decl->isInstanceOf<VarDecl>()) {
				return dynamic_cast<VarDecl*>(decl);
			}
		}
		return nullptr;
	}

	TypeDecl* Parser::findTypeByName(const std::string &name) {
		for(int i = scopeStack.size() - 1; i >= 0; i--) {
			CompoundStmt *scope = scopeStack[i];
			Decl *decl = scope->getDeclByName(name);
			if(decl && decl->isInstanceOf<TypeDecl>()) {
				return dynamic_cast<TypeDecl*>(decl);
			}
		}
		return nullptr;
	}

	FunctionDecl* Parser::findFunctionByName(const std::string &name) {
		for(int i = scopeStack.size() - 1; i >= 0; i--) {
			CompoundStmt *scope = scopeStack[i];
			Decl *decl = scope->getDeclByName(name);
			if(decl && decl->isInstanceOf<FunctionDecl>()) {
				return dynamic_cast<FunctionDecl*>(decl);
			}
		}
		return nullptr;
	}

	void Parser::pragma() {
		lexer.expect(t_pragma);
		lexer.expect(t_id);
		std::string name = lexer.get<std::string>();
		if(name == "ret") {
			lexer.expect(t_id);
			std::string typestr = lexer.get<std::string>();
			rtypeStack[0] = findTypeByName(typestr);
		}
		lexer.expect(t_semicolon);
	}

	void Parser::import() {
		lexer.expect(t_import);
		lexer.expect(t_str);
		std::string name = lexer.get<std::string>();
		if(modules.count(name)) {
			Module &module = modules.at(name);
			for(Decl *decl : module) {
				context.root()->append(decl);
			}
		}
		lexer.expect(t_semicolon);
	}

	Stmt* Parser::stmt() {
		switch(lexer.peek()) {
			case t_const:
			case t_static: {
				return decl();
			}
			case t_return: {
				return returnStmt();
			}
			case t_id: {
				std::string id = lexer.peekliteral<std::string>();
				if(findTypeByName(id)) {
					return decl();
				}
				// else default
			}
			default: {
				Stmt *result = expr();
				lexer.expect(t_semicolon);
				return result;
			}
		}
	}

	Expr* Parser::expr() {
		Expr *e = nullptr;
		while(true) {
			switch(lexer.peek()) {
				case t_int: {
					e = intLitExpr();
				} break;
				case t_uint: {
					e = uintLitExpr();
				} break;
				case t_openparen: {
					lexer.next();
					e = expr();
					lexer.expect(t_closeparen);
				} break;
				case t_id: {
					std::string id = lexer.peekliteral<std::string>();
					if(findFunctionByName(id)) {
						e = callExpr();
					}
					else if(findVarByName(id)) {
						e = varInvokeExpr();
					}
					else {
						throw std::runtime_error("error: unexpected identifier '" + id + "'");
					}
				} break;
				case t_closeparen:
				case t_semicolon:
				case t_comma: {
					return e;
				}
				default: {
					lexer.expect(t_semicolon);
				}
			}
		}
	}

	Decl* Parser::decl() {
		TypeInfo type = parseType();
		lexer.expect(t_id);
		std::string name = lexer.get<std::string>();
		if(lexer.accept(t_openparen)) { // function decl
			rtypeStack.push_back(type);
			std::vector<ParamDecl*> params;
			TypeInfo rspptr_t = TypeInfo(findTypeByName("void"), false, false, 1);	// void*
			params.push_back(context.addNode<ParamDecl>(rspptr_t, "<rsp>"));
			while(!lexer.accept(t_closeparen)) {
				TypeInfo paramtype = parseType();
				lexer.expect(t_id);
				std::string name = lexer.get<std::string>();
				if(lexer.accept(t_assign)) {
					Expr *init = expr();
					params.push_back(context.addNode<ParamDecl>(paramtype, name, init));
				}
				else {
					params.push_back(context.addNode<ParamDecl>(paramtype, name));
				}
				if(lexer.peek() != t_closeparen) {
					lexer.expect(t_comma);
				}
			}

			bool isConst = false, isStatic = false;
			isConst |= lexer.accept(t_const);	// isConst 2 times because order doesn't matter
			isStatic |= lexer.accept(t_static);
			isConst |= lexer.accept(t_const);

			FunctionDecl *func = context.addNode<FunctionDecl>(type, name, params, isConst, isStatic);
			scopeStack.back()->append(func);

			if(!lexer.accept(t_semicolon))
				func->setBody(compoundStmt());
			rtypeStack.pop_back();
			return func;
		}
		else {
			VarDecl *var = nullptr;
			if(lexer.accept(t_assign)) {
				Expr *init = expr();
				var = context.addNode<VarDecl>(type, name, init);
			}
			else {
				var = context.addNode<VarDecl>(type, name);
			}
			while(!lexer.accept(t_semicolon)) {
				scopeStack.back()->append(var);
				lexer.expect(t_comma);
				type.ptrCount = 0;
				while(lexer.accept(t_mul)) {
					type.ptrCount++;
				}
				lexer.expect(t_id);
				std::string name = lexer.get<std::string>();
				if(lexer.accept(t_assign)) {
					Expr *init = expr();
					var = context.addNode<VarDecl>(type, name, init);
				}
				else {
					var = context.addNode<VarDecl>(type, name);
				}
			}
			return var;
		}
	}

	TypeInfo Parser::parseType() {
		bool isConst = false, isStatic = false;
		size_t ptrCount = 0;
		TypeDecl *baseType = nullptr;
		isConst |= lexer.accept(t_const);	// 2 times const because order doesn't matter
		isStatic |= lexer.accept(t_static);
		isConst |= lexer.accept(t_const);
		lexer.expect(t_id);
		std::string name = lexer.get<std::string>();
		baseType = findTypeByName(name);
		if(!baseType) {
			throw std::runtime_error("error: unknown type '" + name + "'");
		}
		while(lexer.accept(t_mul)) {
			ptrCount++;
		}
		return TypeInfo(baseType, isConst, isStatic, ptrCount);
	}

	ReturnStmt* Parser::returnStmt() {
		lexer.expect(t_return);
		if(!lexer.accept(t_semicolon)) {
			Expr *val = expr();
			lexer.expect(t_semicolon);
			if(val->type() != rtypeStack.back()) {
				val = context.addNode<ImplicitCastExpr>(val, rtypeStack.back());
			}
			return context.addNode<ReturnStmt>(val);
		}
		return context.addNode<ReturnStmt>();
	}

	CompoundStmt* Parser::compoundStmt() {
		lexer.expect(t_opencurly);
		CompoundStmt *compoundStmt = context.addNode<CompoundStmt>();
		scopeStack.push_back(compoundStmt);
		while(!lexer.accept(t_closecurly)) {
			compoundStmt->append(stmt());
		}
		scopeStack.pop_back();
		return compoundStmt;
	}

	IntLitExpr* Parser::intLitExpr() {
		lexer.expect(t_int);
		return context.addNode<IntLitExpr>(lexer.get<int64_t>(), findTypeByName("int64"));
	}

	UIntLitExpr* Parser::uintLitExpr() {
		lexer.expect(t_uint);
		return context.addNode<UIntLitExpr>(lexer.get<uint64_t>(), findTypeByName("uint64"));
	}

	VarInvokeExpr* Parser::varInvokeExpr() {
		lexer.expect(t_id);
		std::string name = lexer.get<std::string>();
		VarDecl *decl = findVarByName(name);
		return context.addNode<VarInvokeExpr>(decl);
	}

	CallExpr* Parser::callExpr() {
		lexer.expect(t_id);
		std::string name = lexer.get<std::string>();
		FunctionDecl *func = findFunctionByName(name);
		if(!func) {
			throw std::runtime_error("error: unknown function '" + name + "'");
		}
		lexer.expect(t_openparen);
		std::vector<Expr*> args;
		while(!lexer.accept(t_closeparen)) {
			args.push_back(expr());
		}
		return context.addNode<CallExpr>(func, args);
	}
}