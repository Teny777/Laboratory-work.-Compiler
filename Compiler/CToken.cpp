#include "CToken.h"
#include "Position.h"
#include<iostream>

//Инициализация типов операции
void CToken::InitTypeOfOp() {
	TypeOfOp[assignmentSy] = "Assignment";
	TypeOfOp[descriptionOfTypesSy] = "Description Of Types";
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
	TypeOfOp[divSy] = "Arithmetic Operators";
	TypeOfOp[modSy] = "Arithmetic Operators";
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
	TypeOfOp[charsy] = "KeyWord";
	TypeOfOp[realsy] = "KeyWord";
	TypeOfOp[beginsy] = "KeyWord";
	TypeOfOp[whilesy] = "KeyWord";
	TypeOfOp[arraysy] = "KeyWord";
	TypeOfOp[constsy] = "KeyWord";
	TypeOfOp[labelsy] = "KeyWord";
	TypeOfOp[untilsy] = "KeyWord";
	TypeOfOp[doublesy] = "KeyWord";
	TypeOfOp[stringsy] = "KeyWord";
	TypeOfOp[downtosy] = "KeyWord";
	TypeOfOp[packedsy] = "KeyWord";
	TypeOfOp[recordsy] = "KeyWord";
	TypeOfOp[repeatsy] = "KeyWord";
	TypeOfOp[booleansy] = "KeyWord";
	TypeOfOp[lengthsy] = "KeyWord";
	TypeOfOp[writelnsy] = "KeyWord";
	TypeOfOp[readlnsy] = "KeyWord";
	TypeOfOp[copysy] = "KeyWord";
	TypeOfOp[programsy] = "KeyWord";
	TypeOfOp[fuctionsy] = "KeyWord";
	TypeOfOp[proceduresy] = "KeyWord";
	TypeOfOp[integersy] = "KeyWord";
	TypeOfOp[longintsy] = "KeyWord";
}

CToken::CToken(TokenType _tt, OperationSymbols _op, std::string val,position _pos) {
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
std::string CToken::GetTokenType() {
	switch (tt) {
	case ttConst:
		return constVal->GetClassType();
	case ttOper:
		return TypeOfOp[op];
	case ttIdent:
		return "Variable";
	}
}


void CToken::Print() {
	if (!this||tt==ttSpec) return;
	std::cout << "Type: " << GetTokenType() << "\nValue: " << ident << '\n' << '\n';
}

CToken::~CToken() {
	delete constVal;
}

