#pragma once
#include<string>
#include <set>
#include "CLexer.h"
#include "CToken.h"
#include "ErrorManager.h"
#include "CType.h"

class CCompiler {



private:

	std::map<std::string, CType*> availableTypes = { // Допустимые типы
	{"integer",new CIntType(et_integer)},
	{"double",new CDoubleType(et_double)},
	{"string",new CStringType(et_string)},
	{"boolean",new CBoolType(et_bool)}
	};
	std::map<std::string, CType*> availableVariables; // Допустимые переменные
	std::map<std::string, bool> variablesError; // Ошибки переменных

	CType* deriveTo(CType* left, CType* right);

	CLexer* lexer;
	CToken* curToken;
	ErrorManager* errManager;

	void accept(OperationSymbols op);
	void accept(TokenType _tt);

	void block(); //блок

	void varpart(); //раздел переменных

	void sametype(); //описание однотипных переменных

	CType* type(); //тип

	void operatorssection(); //раздел операторов

	void compoundoperator(); // составной оператор

	void ooperator(); // оператор

	void unlabeledoperator(); //непомеченный оператор

	void simpleoperator(); //простой оператор

	void complexoperator(); //сложный оператор

	void assignmentoperator(); //оператор присваивания

	CType* expression(); //выражение

	CType* simpleexpression(); //простое выражение

	CType* summand(); //слагаемое

	CType* factor(); //множитель

	void selectingoperator(); //выбирающий оператор

	void cycleoperator(); //оператор цикла

	void conditionaloperator(); //условный оператор

	void whilepart(); //цикл с предусловием

public:
	CCompiler (CLexer* _lexer,ErrorManager* _errManager);
	void CheckProgram();
};