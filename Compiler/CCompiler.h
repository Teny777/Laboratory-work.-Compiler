п»ї#pragma once
#include "pch.h"
#include<string>
#include <set>
#include <vector>
#include "CLexer.h"
#include "CToken.h"
#include "ErrorManager.h"
#include "CType.h"

using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Reflection::Emit;

class CCompiler {

private:


	CLexer* lexer;
	CToken* curToken;
	ErrorManager* errManager;

	std::map<std::string, CType*> availableTypes = { // Допустимые типы
	{"integer",new CIntType(et_integer)},
	{"double",new CDoubleType(et_double)},
	{"string",new CStringType(et_string)},
	{"boolean",new CBoolType(et_bool)}
	};
	std::map<std::string, CType*> availableVariables; // Допустимые переменные
	std::map<std::string, int> indexVariables; //Индексы переменных (для генератора)
	std::map<std::string, bool> variablesError;  // Ошибки переменных

	CType* deriveTo(CType* left, CType* right);

	// Проверка на одну из операций
	bool isOper(std::vector<OperationSymbols> arrayOp);


	void accept(OperationSymbols op);

	void accept(TokenType _tt);

	void block(ILGenerator^ il); //блок

	void varpart(ILGenerator^ il); //раздел переменных

	void sametype(ILGenerator^ il); //описание однотипных переменных

	CType* type(); //тип

	void operatorssection(ILGenerator^ il); //раздел операторов

	void compoundoperator(ILGenerator^ il); // составной оператор

	void ooperator(ILGenerator^ il); // оператор

	void unlabeledoperator(ILGenerator^ il); //непомеченный оператор

	void simpleoperator(ILGenerator^ il); //простой оператор

	void complexoperator(ILGenerator^ il);  //сложный оператор

	void assignmentoperator(ILGenerator^ il); //оператор присваивания

	CType* expression(ILGenerator^ il); //выражение

	CType* simpleexpression(ILGenerator^ il); //простое выражение

	CType* summand(ILGenerator^ il); //слагаемое

	CType* factor(ILGenerator^ il); //множитель

	void selectingoperator(ILGenerator^ il); //выбирающий оператор

	void cycleoperator(ILGenerator^ il); //оператор цикла

	void conditionaloperator(ILGenerator^ il); //условный оператор

	void whilepart(ILGenerator^ il); ///цикл с предусловием

	void procedureoperator(ILGenerator^ il); // оператор процедуры

	void parameter(ILGenerator^ il); //Параметр

public:
	CCompiler(CIO* io, ErrorManager* _errManager);

	void CheckProgram(ILGenerator^ il);

	~CCompiler();
};