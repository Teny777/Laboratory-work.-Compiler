#include "CToken.h"
#include<iostream>

//Инициализация типов у оперций
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
}

CToken::CToken(TokenType _tt, OperationSymbols _op, std::string val, CVariant* _constVal) {
	tt = _tt;
	op = _op;
	constVal = _constVal;
	ident = val;
	InitTypeOfOp();
}


//Получить тип токена
std::string CToken::GetTokenType() {
	switch (tt) {
	case ttConst:
		return constVal->GetClassType();
	case ttOper:
		return TypeOfOp[op];
	case ttComment:
		return  "Comment";
	case ttKeyWord:
		return "KeyWord";
	case ttIdent:
		return "Variable";
	}
}


void CToken::Print() {
	if (!this) return;
	std::cout << "Type: " << GetTokenType() << "\nValue: " << ident << '\n' << '\n';
}

CToken::~CToken() {
	delete constVal;
}