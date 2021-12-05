#pragma once
#include<string>
#include<map>
#include "CVariant.h"
#include "Position.h"


enum TokenType {
	ttIdent,
	ttConst,
	ttOper,
	ttSpec
};


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

	
	std::map<OperationSymbols, std::string> TypeOfOp;
	
	std::string ident;
	position pos;
	//Инициализация типов операции
	void InitTypeOfOp();

	//Получение типа токена
	std::string GetTokenType();

public:
	CVariant* constVal;
	TokenType tt;
	OperationSymbols op;
	CToken(TokenType _tt, OperationSymbols _op, std::string val,position _pos);
	CToken(TokenType _tt, CVariant* _constVal, std::string val,position _pos);
	CToken(TokenType _tt, std::string val,position _pos);
	void Print();
	~CToken();

	
};
