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
	beginsy,
	whilesy,
	arraysy,
	constsy,
	labelsy,
	untilsy,
	downtosy,
	packedsy,
	recordsy,
	repeatsy,
	lengthsy,
	writelnsy,
	readlnsy,
	copysy,
	programsy,
	fuctionsy,
	proceduresy
};


class CToken {
private:


	std::map<OperationSymbols, std::string> TypeOfOp;

	std::string ident;

	position pos;

	//Инициализация типов операции
	void InitTypeOfOp();

	CVariant* constVal;

	TokenType tt;

	OperationSymbols op;

	//Получение названия токена
	std::string GetTokenTypeName();


public:

	CToken(TokenType _tt, OperationSymbols _op, std::string val, position _pos);
	CToken(TokenType _tt, CVariant* _constVal, std::string val, position _pos);
	CToken(TokenType _tt, std::string val, position _pos);

	//Получение позиции
	position GetPosition();

	//Вывод токена
	void Print();

	//Получение лексемы
	std::string GetIdent();

	//Получение константы
	CVariant* GetConst();

	//Получение типа токена
	TokenType GetTokenType();

	//Получение кода операции
	OperationSymbols GetOperationSymbol();

	~CToken();
};
