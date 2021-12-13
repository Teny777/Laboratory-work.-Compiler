#include "CCompiler.h"
#include <iostream>
#include <vector>
#include <map>
#include<string>


CType* CCompiler::deriveTo(CType* left, CType* right) {
	if (left == right || left->type == et_integer && right->type == et_double) return right;
    return left;
}

CCompiler::CCompiler(CLexer* _lexer,ErrorManager* _errManager) {
	lexer =_lexer;
	errManager = _errManager;
	curToken = lexer->GetNextToken();
}

void error() {
	std::cout << "Bad\n";
}

void CCompiler:: accept(OperationSymbols oper) {
	if (curToken->op != oper) error();
	curToken = lexer->GetNextToken();
}

void CCompiler:: accept(TokenType _tt) {
	if(curToken->tt!=_tt)  error();
	curToken = lexer->GetNextToken();
}

//проверка программы
void CCompiler::CheckProgram() {
	/*<программа>:: = program <имя>; <блок>.*/

	accept(programsy);
	accept(ttIdent);
	accept(semicolonSy);
	block();
	accept(pointSy);
}


//блок
void CCompiler::block() {
	/*<блок>:: = <раздел переменных> <раздел операторов>*/
	varpart();
	operatorssection();
}

//раздел переменных
void CCompiler::varpart() {
	/*<раздел переменных>:: = var <описание однотипных переменных>;
	{<описание однотипных переменных>; }*/

	accept(varsy);
	sametype();
	accept(semicolonSy);
	while (curToken->tt == ttIdent) {
		sametype();
		accept(semicolonSy);
	}
}

//описание однотипных переменных
void CCompiler::sametype() {
	/*<описание однотипных переменных>:: = <имя>{ ,<имя> }:<тип>*/
	std::vector<CToken*> variables;
	variables.push_back(curToken);
	accept(ttIdent);
	while (curToken->op == commaSy) {
		curToken = lexer->GetNextToken();
		variables.push_back(curToken);
		accept(ttIdent);
	}


	accept(descriptionOfTypesSy);
	CType * _type = type();
	if (_type) {	
		for (auto variable : variables) {
			if (availableVariables[variable->GetIdent()] && !variablesError[variable->GetIdent()]) {
				errManager->AddError( repeatVariable, variable->GetPosition());
				variablesError[variable->GetIdent()] = true;
				continue;
			}
			availableVariables[variable->GetIdent()] = _type;
		}
	}
	else errManager->AddError( invalidType, curToken->GetPosition());
	curToken = lexer->GetNextToken();


}

//тип
CType* CCompiler::type() {
	/*<тип>:: = <имя типа>*/
	return availableTypes[curToken->GetIdent()];
	
}

//раздел операторов
void CCompiler::operatorssection() {
	/*<раздел операторов>:: = <составной оператор>*/

	compoundoperator();
}

// составной оператор
void CCompiler::compoundoperator() {
	/*<составной оператор>:: = begin <оператор>{ ; <оператор> } end*/

	accept(beginsy);
	ooperator();
	while (curToken->op == semicolonSy) {
		curToken = lexer->GetNextToken();
		ooperator();
	}
	accept(endsy);
}

// оператор
void CCompiler::ooperator() {
	/*<оператор>::=<непомеченный оператор>*/

	unlabeledoperator();
}

//непомеченный оператор
void CCompiler::unlabeledoperator() {

	/*<непомеченный оператор>:: = <простой оператор> | <сложный оператор>*/

	if(curToken->op== beginsy|| curToken->op == ifsy || curToken->op == whilesy )
		complexoperator();
	else simpleoperator();
}

//простой оператор
void CCompiler::simpleoperator() {
	/*<простой оператор>:: = <оператор присваивания>*/
	if(curToken->tt ==ttIdent)
		assignmentoperator();
}



//сложный оператор
void CCompiler::complexoperator() {
	switch (curToken->op)
	{
	case beginsy:
		compoundoperator();
		break;
	case ifsy:
		selectingoperator();
		break;
	case whilesy:
		cycleoperator();
		break;
	default:
		break;
	} 
}

//оператор присваивания
void CCompiler::assignmentoperator() {
	/*<оператор присваивания>:: = <переменная>: = <выражение>*/


	CType* left = nullptr;
	if (curToken->tt == ttIdent) left = availableVariables[curToken->GetIdent()];
	curToken = lexer->GetNextToken();
	position posOperation = curToken->GetPosition();
	accept(assignmentSy);
	CType* right = expression();
	if(!right||!right->isDerivedTo(left))  errManager->AddError(incompatibleTypes, posOperation);
}


//выражение
CType* CCompiler::expression() {
	/*<выражение>:: = <простое выражение> | <простое выражение>
		<операция отношения><простое выражение>

	<операция отношения>::==|<> | <|<=|>=|> | in*/

	CType* left = simpleexpression();
	position posOperation;

	if(curToken->op == equalSy || curToken->op == notEqualSy || curToken->op == lessSy || curToken->op == lessEqualSy ||
		curToken->op == moreEqualSy || curToken->op == moreSy || curToken->op == insy) {

		posOperation = curToken->GetPosition();
		curToken = lexer->GetNextToken();
		CType* right = simpleexpression();

		if (left&&left->isDerivedTo(right)||right&&right->isDerivedTo(left)) return availableTypes["boolean"];
		else errManager->AddError( incompatibleTypes, posOperation);
	}
	return left;
}

//простое выражение
CType* CCompiler::simpleexpression() {
	/*<простое выражение>:: = [<знак>]<слагаемое>
	{ <аддитивная операция><слагаемое> }

	<знак>::=+|-
	
	<аддитивная операция>::=+|-|or*/

	if(curToken->op== sumSy||curToken->op== minusSy) curToken = lexer->GetNextToken();
	CType* left =summand();
	position posOperation;

	while (curToken->op == sumSy || curToken->op == minusSy || curToken->op == orsy) {

		posOperation = curToken->GetPosition();
		curToken = lexer->GetNextToken();
		CType* right = summand();
		if (left && left->isDerivedTo(right) || right && right->isDerivedTo(left)) left = deriveTo(left, right);
		else errManager->AddError( incompatibleTypes, posOperation);
	}

	return left;
	
}

//слагаемое
CType* CCompiler::summand() {

	/*<слагаемое>::=<множитель>{<мультипликативная операция> <множитель>}
	
	<мультипликативная операция>::=*|/|div|mod|and*/

	CType* left = factor();
	position posOperation;

	while (curToken->op == mulSy || curToken->op == divisionSy || curToken->op == divsy || curToken->op == modsy || curToken->op == andsy) {

		posOperation = curToken->GetPosition();
		curToken = lexer->GetNextToken();
		CType* right = factor();
		if (left && left->isDerivedTo(right) || right && right->isDerivedTo(left)) left = deriveTo(left, right);
		else errManager->AddError( incompatibleTypes, posOperation);
	}
	return left;
}

//множитель
CType* CCompiler::factor() {
	/*<множитель>::=<переменная>|<константа без знака>| (<выражение>) */


	if (curToken->tt == ttIdent) { 
		if (!availableVariables[curToken->GetIdent()] && !variablesError[curToken->GetIdent()]) {
			errManager->AddError(undeclaredIdent, curToken->GetPosition());
			variablesError[curToken->GetIdent()] = true;
		}
		std::string ident = curToken->GetIdent();
		curToken = lexer->GetNextToken();
		return availableVariables[ident];
	}
	else if (curToken->tt == ttConst) {

		std::string type = curToken->constVal->GetClassType();
		curToken = lexer->GetNextToken();
		return availableTypes[type];
	}

	else if (curToken->op == openParSy) {
		accept(openParSy);
		CType* left =  expression();
		accept(closeParSy);
		return left;
	}
	else error();

}

//выбирающий оператор
void CCompiler::selectingoperator() {
	/*<выбирающий оператор>:: = <условный оператор>*/
	conditionaloperator();
}

//оператор цикла
void CCompiler::cycleoperator() {
	/*<оператор цикла>::=<цикл с предусловием>*/

	whilepart();
}

//условный оператор
void CCompiler::conditionaloperator() {
	/*<условный оператор>:: = if <выражение> then <оператор> |
		if <выражение> then <оператор> else <оператор>*/
	position posOperation = curToken->GetPosition();;
	accept(ifsy);
	CType* left = expression();
	if(!left||!left->isDerivedTo(availableTypes["boolean"])) errManager->AddError(expressionBool, posOperation);
	accept(thensy);
	ooperator();
	if (curToken->op == elsesy) {
		accept(elsesy);
		ooperator();
	}
}

//цикл с предусловием
void CCompiler::whilepart() {
	/*<цикл с предусловием>:: = while <выражение> do <оператор>*/
	position posOperation = curToken->GetPosition();;
	accept(whilesy);
	CType* left = expression();
	if (!left || !left->isDerivedTo(availableTypes["boolean"])) errManager->AddError(expressionBool, posOperation);
	accept(dosy);
	ooperator();
}