#include "pch.h"
#include "CToken.h"
#include<iostream>

//Инициализация типов операции
void CToken::InitTypeOfOp() {
	TypeOfOp[assignmentSy] = "Assignment";
	TypeOfOp[descriptionOfTypesSy] = "Separator";
	TypeOfOp[notEqualSy] = "Comparison";
	TypeOfOp[lessEqualSy] = "Comparison";
	TypeOfOp[lessSy] = "Comparison";
	TypeOfOp[moreEqualSy] = "Comparison";
	TypeOfOp[moreSy] = "Comparison";
	TypeOfOp[semicolonSy] = "Separator";
	TypeOfOp[pointSy] = "Separator";
	TypeOfOp[ellipsisSy] = "Ellipsis";
	TypeOfOp[sumSy] = "Arithmetic Operators";
	TypeOfOp[minusSy] = "Arithmetic Operators";
	TypeOfOp[divisionSy] = "Arithmetic Operators";
	TypeOfOp[equalSy] = "Comparison";
	TypeOfOp[mulSy] = "Arithmetic Operators";
	TypeOfOp[openParSy] = "Separator";
	TypeOfOp[closeParSy] = "Separator";
	TypeOfOp[openIndSy] = "Separator";
	TypeOfOp[closeIndSy] = "Separator";
	TypeOfOp[commaSy] = "Separator";
	TypeOfOp[ifsy] = "KeyWord";
	TypeOfOp[dosy] = "KeyWord";
	TypeOfOp[ofsy] = "KeyWord";
	TypeOfOp[orsy] = "KeyWord";
	TypeOfOp[insy] = "KeyWord";
	TypeOfOp[tosy] = "KeyWord";
	TypeOfOp[endsy] = "KeyWord";
	TypeOfOp[varsy] = "KeyWord";
	TypeOfOp[divsy] = "Arithmetic Operators";
	TypeOfOp[andsy] = "KeyWord";
	TypeOfOp[notsy] = "KeyWord";
	TypeOfOp[forsy] = "KeyWord";
	TypeOfOp[modsy] = "Arithmetic Operators";
	TypeOfOp[setsy] = "KeyWord";
	TypeOfOp[thensy] = "KeyWord";
	TypeOfOp[elsesy] = "KeyWord";
	TypeOfOp[casesy] = "KeyWord";
	TypeOfOp[filesy] = "KeyWord";
	TypeOfOp[gotosy] = "KeyWord";
	TypeOfOp[typesy] = "KeyWord";
	TypeOfOp[withsy] = "KeyWord";
	TypeOfOp[beginsy] = "KeyWord";
	TypeOfOp[whilesy] = "KeyWord";
	TypeOfOp[arraysy] = "KeyWord";
	TypeOfOp[constsy] = "KeyWord";
	TypeOfOp[labelsy] = "KeyWord";
	TypeOfOp[untilsy] = "KeyWord";
	TypeOfOp[downtosy] = "KeyWord";
	TypeOfOp[packedsy] = "KeyWord";
	TypeOfOp[recordsy] = "KeyWord";
	TypeOfOp[repeatsy] = "KeyWord";
	TypeOfOp[lengthsy] = "KeyWord";
	TypeOfOp[writelnsy] = "KeyWord";
	TypeOfOp[readlnsy] = "KeyWord";
	TypeOfOp[copysy] = "KeyWord";
	TypeOfOp[programsy] = "KeyWord";
	TypeOfOp[fuctionsy] = "KeyWord";
	TypeOfOp[proceduresy] = "KeyWord";

}

CToken::CToken(TokenType _tt, OperationSymbols _op, std::string val, position _pos) {
	tt = _tt;
	op = _op;
	constVal = nullptr;
	ident = val;
	pos = _pos;
	InitTypeOfOp();
}

CToken::CToken(TokenType _tt, CVariant* _constVal, std::string val, position _pos) {
	tt = _tt;
	op = null;
	constVal = _constVal;
	ident = val;
	pos = _pos;
	InitTypeOfOp();
}

CToken::CToken(TokenType _tt, std::string val, position _pos) {
	tt = _tt;
	op = null;
	constVal = nullptr;
	ident = val;
	pos = _pos;
	InitTypeOfOp();
}


// Получение типа токена
std::string CToken::GetTokenTypeName() {
	switch (tt) {
	case ttConst:
		return constVal->GetClassType();
	case ttOper:
		return TypeOfOp[op];
	case ttIdent:
		return "Variable";
	case ttSpec:
		return "Special";
	}
}


void CToken::Print() {
	if (!this) return;
	std::cout << "Type: " << GetTokenTypeName() << "\nValue: " << ident << '\n' << '\n';
}


std::string CToken::GetIdent() {
	return ident;
}

CToken::~CToken() {
	delete constVal;
}

//Получение позиции
position CToken::GetPosition() {
	return pos;
}


CVariant* CToken::GetConst() {
	return constVal;
}

TokenType CToken::GetTokenType() {
	return tt;
}

OperationSymbols CToken::GetOperationSymbol() {
	return op;
}