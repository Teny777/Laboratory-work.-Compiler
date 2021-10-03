#pragma once
#include<string>
#include<map>
#include "CVariant.h"

// Тип токена
enum TokenType {
	ttKeyWord,
	ttIdent,
	ttConst,
	ttOper,
	ttComment
};

//Операции 
enum OperationSymbols {
	null,
	assignmentSy,
	descriptionOfTypesSy,
	notEqualSy,
	lessEqualSy,
	lessSy,
	moreEqualSy,
	moreSy,
	semicolonSy,
	pointSy,
	ellipsisSy,
	sumSy,
	minusSy,
	divisionSy,
	equalSy,
	mulSy,
	openParSy,
	closeParSy,
	openIndSy,
	closeIndSy,
	divSy,
	modSy,
	commaSy
};


class CToken {
private:

	TokenType tt;
	OperationSymbols op;
	std::map<OperationSymbols, std::string> TypeOfOp;
	CVariant* constVal;
	std::string ident;

	//Инициализация типов у оперций
	void InitTypeOfOp();

	//Получить тип токена
	std::string GetTokenType();

public:

	CToken(TokenType _tt, OperationSymbols _op, std::string val, CVariant* _constVal = nullptr);
	void Print();
	~CToken();
};