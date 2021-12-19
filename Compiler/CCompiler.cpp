#include "pch.h"
#include "CCompiler.h"
#include <iostream>
#include <vector>
#include <map>
#include<string>


using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Reflection::Emit;


CType *CCompiler::deriveTo(CType* left, CType* right) {

	if (left == right || left->type == et_integer && right->type == et_double) return right;
	return left;
}

CCompiler::CCompiler(CIO* _io, ErrorManager* _errManager) {
	lexer = new CLexer(_io,_errManager);
	errManager = _errManager;
	curToken = lexer->GetNextToken();
}

void error() {
	std::cout << "Bad\n";
}

// Проверка на одну из операций
bool CCompiler::isOper(std::vector<OperationSymbols> arrayOp) {
	OperationSymbols curOp = curToken->GetOperationSymbol();
	for (auto op : arrayOp)
		if (curOp == op) return true;
	return false;
}

void CCompiler::accept(OperationSymbols oper) {
	if (curToken->GetOperationSymbol() != oper) error();
	curToken = lexer->GetNextToken();
}

void CCompiler::accept(TokenType _tt) {
	if (curToken->GetTokenType() != _tt)  error();
	curToken = lexer->GetNextToken();
}

//проверка программы
void CCompiler::CheckProgram(ILGenerator^ il) {
	/*<программа>:: = program <имя>; <блок>.*/

	accept(programsy);
	accept(ttIdent);
	accept(semicolonSy);
	block(il);
	accept(pointSy);
}


//блок
void CCompiler::block(ILGenerator^ il) {
	/*<блок>:: = <раздел переменных> <раздел операторов>*/
	varpart(il);
	operatorssection(il);
}

//раздел переменных
void CCompiler::varpart(ILGenerator^ il) {
	/*<раздел переменных>:: = var <описание однотипных переменных>;
	{<описание однотипных переменных>; }*/

	accept(varsy);
	sametype(il);
	accept(semicolonSy);
	while (curToken->GetTokenType()== ttIdent) {
		sametype(il);
		accept(semicolonSy);
	}
}



//Добавить переменную в IL
void AddVariable(CType* _type, ILGenerator^ il) {
	switch (_type->type)
	{
	case et_bool:
		il->DeclareLocal(bool::typeid);
		break;
	case et_integer:
		il->DeclareLocal(Int32::typeid);
		break;
	case et_string:
		il->DeclareLocal(String::typeid);
		break;
	case et_double:
		il->DeclareLocal(Double::typeid);
		break;
	}
}


//описание однотипных переменных
void CCompiler::sametype(ILGenerator^ il) {
	/*<описание однотипных переменных>:: = <имя>{ ,<имя> }:<тип>*/
	std::vector<CToken*> variables;
	variables.push_back(curToken);
	accept(ttIdent);
	while (curToken->GetOperationSymbol() == commaSy) {
		curToken = lexer->GetNextToken();
		variables.push_back(curToken);
		accept(ttIdent);
	}


	accept(descriptionOfTypesSy);
	CType* _type = type();
	if (_type) {
		for (auto variable : variables) {

			if (availableVariables[variable->GetIdent()] && !variablesError[variable->GetIdent()]) {
				errManager->AddError(repeatVariable, variable->GetPosition());
				variablesError[variable->GetIdent()] = true;
				continue;
			}

			availableVariables[variable->GetIdent()] = _type;
			indexVariables[variable->GetIdent()] = (int)indexVariables.size()-1;
			AddVariable(_type, il); // Добавить переменную в IL			
		}
	}
	else errManager->AddError(invalidType, curToken->GetPosition());
	curToken = lexer->GetNextToken();

}

//тип
CType* CCompiler::type() {
	/*<тип>:: = <имя типа>*/
	return availableTypes[curToken->GetIdent()];

}

//раздел операторов
void CCompiler::operatorssection(ILGenerator^ il) {
	/*<раздел операторов>:: = <составной оператор>*/

	compoundoperator(il);
}

// составной оператор
void CCompiler::compoundoperator(ILGenerator^ il) {
	/*<составной оператор>:: = begin <оператор>{ ; <оператор> } end*/

	accept(beginsy);
	ooperator(il);
	while (curToken->GetOperationSymbol() == semicolonSy) {
		curToken = lexer->GetNextToken();
		ooperator(il);
	}
	accept(endsy);
}

// оператор
void CCompiler::ooperator(ILGenerator^ il) {
	/*<оператор>::=<непомеченный оператор>*/
	unlabeledoperator(il);
}

//непомеченный оператор
void CCompiler::unlabeledoperator(ILGenerator^ il) {

	/*<непомеченный оператор>:: = <простой оператор> | <сложный оператор>*/	
	if (isOper({ beginsy,ifsy,whilesy }))
		complexoperator(il);
	else simpleoperator(il);
}

//простой оператор
void CCompiler::simpleoperator(ILGenerator^ il) {
	/*<простой оператор>:: = <оператор присваивания>*/
	if (curToken->GetTokenType() == ttIdent)
		assignmentoperator(il);
	if (curToken->GetOperationSymbol() == writelnsy) procedureoperator(il);
}
// оператор процедуры
void CCompiler::procedureoperator(ILGenerator^ il) {
	accept(writelnsy);
	accept(openParSy);
	parameter(il);
	accept(closeParSy);
}



void writeLine(CType* _type, ILGenerator^ il) {
	MethodInfo^ fnWriteLineDouble = Console::typeid->GetMethod("WriteLine", gcnew array<Type^> { Double::typeid });
	MethodInfo^ fnWriteLineInt = Console::typeid->GetMethod("WriteLine", gcnew array<Type^> { Int32::typeid });
	MethodInfo^ fnWriteLineString = Console::typeid->GetMethod("WriteLine", gcnew array<Type^> { String::typeid });
	MethodInfo^ fnWriteLineBool = Console::typeid->GetMethod("WriteLine", gcnew array<Type^> { Boolean::typeid });

	switch (_type->type)
	{
	case et_integer:
		il->Emit(OpCodes::Call, fnWriteLineInt);
		break;
	case et_double:
		il->Emit(OpCodes::Call, fnWriteLineDouble);
		break;
	case et_string:
		il->Emit(OpCodes::Call, fnWriteLineString);
		break;
	case et_bool:
		il->Emit(OpCodes::Call, fnWriteLineBool);
		break;
	default:
		break;
	}
}

//параметр
void CCompiler::parameter(ILGenerator^ il) {
	
	writeLine(expression(il),il);		
}


//сложный оператор
void CCompiler::complexoperator(ILGenerator^ il) {

	switch (curToken->GetOperationSymbol())
	{
	case beginsy:
		compoundoperator(il);
		break;
	case ifsy:
		selectingoperator(il);
		break;
	case whilesy:
		cycleoperator(il);
		break;
	default:
		break;
	}
}

//Приведение типов
void ConvertType(CType* left,CType* right, ILGenerator^ il) {
	if(left->type==et_double&& right->type==et_integer)
		il->Emit(OpCodes::Conv_R8);
}

//оператор присваивания
void CCompiler::assignmentoperator(ILGenerator^ il) {
	/*<оператор присваивания>:: = <переменная>: = <выражение>*/


	CType* left = nullptr;
	int index_ident = 0;
	if (curToken->GetTokenType() == ttIdent) {
		if (!availableVariables[curToken->GetIdent()] && !variablesError[curToken->GetIdent()]) {
			errManager->AddError(undeclaredIdent, curToken->GetPosition());
			variablesError[curToken->GetIdent()] = true;
		}
		left = availableVariables[curToken->GetIdent()];
		index_ident = indexVariables[curToken->GetIdent()];
	}
	curToken = lexer->GetNextToken();
	position posOperation = curToken->GetPosition();
	accept(assignmentSy);
	CType* right = expression(il);
	if (!right || !right->isDerivedTo(left))  errManager->AddError(incompatibleTypes, posOperation);

	//Записывание значение в переменную
	ConvertType(left,right, il);
	il->Emit(OpCodes::Stloc, index_ident);
	

}
void AddOper(OperationSymbols op, ILGenerator^ il) {
	switch (op)
	{
	case notEqualSy:
		il->Emit(OpCodes::Ceq);
		il->Emit(OpCodes::Ldc_I4_0);
		il->Emit(OpCodes::Ceq);
		break;
	case lessEqualSy:
		il->Emit(OpCodes::Cgt);
		il->Emit(OpCodes::Ldc_I4_0);
		il->Emit(OpCodes::Ceq);
		break;
	case lessSy:
		il->Emit(OpCodes::Clt);
		break;
	case moreEqualSy:
		il->Emit(OpCodes::Clt);
		il->Emit(OpCodes::Ldc_I4_0);
		il->Emit(OpCodes::Ceq);
		break;
	case moreSy:
		il->Emit(OpCodes::Cgt);
		break;
	case sumSy:
		il->Emit(OpCodes::Add);
		break;
	case divsy:
		il->Emit(OpCodes::Div);
		break;
	case minusSy:
		il->Emit(OpCodes::Sub);
		break;
	case divisionSy:
		il->Emit(OpCodes::Div);
		break;
	case modsy:
		il->Emit(OpCodes::Rem);
		break;
	case equalSy:
		il->Emit(OpCodes::Ceq);
		break;
	case mulSy:
		il->Emit(OpCodes::Mul);
		break;
	case orsy:
		il->Emit(OpCodes::Or);
		break;
	case andsy:
		il->Emit(OpCodes::And);
		break;

	default:
		break;
	}
}

//выражение
CType* CCompiler::expression(ILGenerator^ il) {
	/*<выражение>:: = <простое выражение> | <простое выражение>
		<операция отношения><простое выражение>

	<операция отношения>::==|<> | <|<=|>=|>*/

	CType* left = simpleexpression(il);
	position posOperation;
	OperationSymbols operation;
	if (isOper({ equalSy ,notEqualSy,lessSy,lessEqualSy,moreEqualSy,moreSy })) {

		posOperation = curToken->GetPosition();
		operation = curToken->GetOperationSymbol();
		curToken = lexer->GetNextToken();

		CType* right = simpleexpression(il);

		if (left && left->isDerivedTo(right) || right && right->isDerivedTo(left)) {
			ConvertType(left,right, il);
			AddOper(operation, il);
			return availableTypes["boolean"];
		}
		else errManager->AddError(incompatibleTypes, posOperation);
	}
	return left;
}





//простое выражение
CType* CCompiler::simpleexpression(ILGenerator^ il) {
	/*<простое выражение>:: = [<знак>]<слагаемое>
	{ <аддитивная операция><слагаемое> }

	<знак>::=+|-

	<аддитивная операция>::=+|-|or*/
	
	if (isOper({ sumSy,minusSy })) curToken = lexer->GetNextToken();
	CType* left = summand(il);
	position posOperation;
	OperationSymbols operation;
	
	while (isOper({ sumSy,minusSy,orsy})) {

		posOperation = curToken->GetPosition();
		operation = curToken->GetOperationSymbol();
		curToken = lexer->GetNextToken();
		CType* right = summand(il);
		if (left && left->isDerivedTo(right) || right && right->isDerivedTo(left)) left = deriveTo(left, right);
		else errManager->AddError(incompatibleTypes, posOperation);

		ConvertType(left, right, il);
		AddOper(operation, il);
	}

	return left;

}

//слагаемое
CType* CCompiler::summand(ILGenerator^ il) {

	/*<слагаемое>::=<множитель>{<мультипликативная операция> <множитель>}

	<мультипликативная операция>::=*|/|div|mod|and*/

	CType* left = factor(il);
	position posOperation;
	OperationSymbols operation;
	
	while (isOper({ mulSy,divisionSy,divsy,modsy,andsy })) {
		operation = curToken->GetOperationSymbol();
		posOperation = curToken->GetPosition();
		curToken = lexer->GetNextToken();
		CType* right = factor(il);
		if (left && left->isDerivedTo(right) || right && right->isDerivedTo(left)) left = deriveTo(left, right);
		else errManager->AddError(incompatibleTypes, posOperation);
		ConvertType(left,right, il);
		AddOper(operation, il);
	}
	return left;
}

void AddConst(CVariant* variant, ILGenerator^ il) {
	if (variant->GetClassType() == "integer") {
		CIntVariant* var = (CIntVariant*)variant;
		il->Emit(OpCodes::Ldc_I4,var->GetValue());
		return;
	}
	if (variant->GetClassType() == "double") {
		CDoubleVariant* var = (CDoubleVariant*)variant;
		il->Emit(OpCodes::Ldc_R8, (double)var->GetValue());
		return;
	}
	if (variant->GetClassType() == "string") {
		CStringVariant* var = (CStringVariant*)variant;
		il->Emit(OpCodes::Ldstr, gcnew System::String(var->GetValue().c_str()));
		return;
	}
}




//множитель
CType* CCompiler::factor(ILGenerator^ il) {
	/*<множитель>::=<переменная>|<константа без знака>| (<выражение>) */

	//Переменная
	if (curToken->GetTokenType() == ttIdent) {

		if (!availableVariables[curToken->GetIdent()] && !variablesError[curToken->GetIdent()]) {
			errManager->AddError(undeclaredIdent, curToken->GetPosition());
			variablesError[curToken->GetIdent()] = true;
		}

		std::string ident = curToken->GetIdent();
		il->Emit(OpCodes::Ldloc, indexVariables[ident]);
		curToken = lexer->GetNextToken();	
		return availableVariables[ident];

	}
	//Константа
	if (curToken->GetTokenType() == ttConst) {

		std::string type = curToken->GetConst()->GetClassType();
		AddConst(curToken->GetConst(), il);
		curToken = lexer->GetNextToken();
		return availableTypes[type];
	}
	//Выражение
	if (curToken->GetOperationSymbol() == openParSy) {
		accept(openParSy);
		CType* left = expression(il);
		accept(closeParSy);
		return left;
	}
	else error();

}

//выбирающий оператор
void CCompiler::selectingoperator(ILGenerator^ il) {
	/*<выбирающий оператор>:: = <условный оператор>*/
	conditionaloperator(il);
}

//оператор цикла
void CCompiler::cycleoperator(ILGenerator^ il) {
	/*<оператор цикла>::=<цикл с предусловием>*/

	whilepart(il);
}

//условный оператор
void CCompiler::conditionaloperator(ILGenerator^ il) {
	/*<условный оператор>:: = if <выражение> then <оператор> |
		if <выражение> then <оператор> else <оператор>*/
	position posOperation = curToken->GetPosition();;
	accept(ifsy);


	Label falseLabel = il->DefineLabel();
	Label continueLabel = il->DefineLabel();

	CType* left = expression(il);
	if (!left || !left->isDerivedTo(availableTypes["boolean"])) errManager->AddError(expressionBool, posOperation);
	accept(thensy);

	il->Emit(OpCodes::Brfalse_S, falseLabel);
	ooperator(il);
	il->Emit(OpCodes::Br_S, continueLabel);

	il->MarkLabel(falseLabel);
	if (curToken->GetOperationSymbol() == elsesy) {
		accept(elsesy);	
		ooperator(il);
	}
	il->MarkLabel(continueLabel);
}

//цикл с предусловием
void CCompiler::whilepart(ILGenerator^ il) {
	/*<цикл с предусловием>:: = while <выражение> do <оператор>*/
	position posOperation = curToken->GetPosition();;
	accept(whilesy);

	Label falseLabel = il->DefineLabel();
	Label continueLabel = il->DefineLabel();

	il->MarkLabel(falseLabel);
	CType* left = expression(il);
	il->Emit(OpCodes::Brfalse_S, continueLabel);
	if (!left || !left->isDerivedTo(availableTypes["boolean"])) errManager->AddError(expressionBool, posOperation);

	accept(dosy);
	ooperator(il);
	il->Emit(OpCodes::Br_S, falseLabel);
	il->MarkLabel(continueLabel);
}



CCompiler::~CCompiler() {
	delete lexer;
	delete curToken;
	delete errManager;
}

