#pragma once
#include<string>
#include "CLexer.h"
#include "CToken.h"
#include "ErrorManager.h"
class Syntax {
private:
	CLexer* lexer;
	CToken* curToken;
	ErrorManager* errManager;

	void accept(OperationSymbols op);
	void accept(TokenType _tt);

	void block(); //блок
	void varpart(); //раздел переменных
	void sametype(); //описание однотипных переменных
	void type(); //тип
	void simpletype(); //простой тип
	void typeName(); //имя типа
	void compoundop(); //составное оператор
	void operat(); //раздел оператороа
	void unmarkedOper(); //непомеченный оператор
	void simpleope(); //простой оператор
	void complexop(); //сложный оператор
	void assignmentop(); //операрот присваивания
	void expression(); //выражение
	void summand(); //слагаемое
	void multiplier(); //множитель

public:
	Syntax(CLexer* _lexer,ErrorManager* _errManager);
	void CheckProgram();
};