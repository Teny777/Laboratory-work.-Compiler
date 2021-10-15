#pragma once
#include<string>
#include<map>
#include "CVariant.h"

// Тип токена
enum TokenType {
	ttIdent,
	ttConst,
	ttOper
};

//Операции 
enum OperationSymbols {
	null,
	assignmentSy, //:=
	descriptionOfTypesSy, //:
	notEqualSy, //<>
	lessEqualSy, //<=
	lessSy, //<
	moreEqualSy,//>=
	moreSy,//>
	semicolonSy, //;
	pointSy,//.
	ellipsisSy,//..
	sumSy,//+
	minusSy,//-
	divisionSy,// /
	equalSy,// =
	mulSy,//*
	openParSy,//(
	closeParSy,//)
	openIndSy,//[
	closeIndSy,//]
	divSy,// div
	modSy, // mod
	commaSy, //,
	ifsy,
	dosy,
	ofsy,
	orsy,
	insy,
	tosy,
	endsy,
	varsy,
	divsy,
	andsy,
	notsy,
	forsy,
	modsy,
	setsy,
	thensy,
	elsesy,
	casesy,
	filesy,
	gotosy,
	typesy,
	withsy,
	charsy,
	realsy,
	beginsy,
	whilesy,
	arraysy,
	constsy,
	labelsy,
	untilsy,
	doublesy,
	stringsy,
	downtosy,
	packedsy,
	recordsy,
	repeatsy,
	booleansy,
	lengthsy,
	writelnsy,
	readlnsy,
	copysy,
	programsy,
	fuctionsy,
	proceduresy,
	integersy,
	longintsy
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

	
	CToken(TokenType _tt, OperationSymbols _op, std::string val);
	CToken(TokenType _tt, CVariant* _constVal, std::string val);
	CToken(TokenType _tt, std::string val);
	void Print();
	~CToken();
};