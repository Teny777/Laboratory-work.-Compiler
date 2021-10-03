#pragma once
#include<string>
#include<map>
#include "CVariant.h"

// ��� ������
enum TokenType {
	ttKeyWord,
	ttIdent,
	ttConst,
	ttOper,
	ttComment
};

//�������� 
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

	//������������� ����� � �������
	void InitTypeOfOp();

	//�������� ��� ������
	std::string GetTokenType();

public:

	CToken(TokenType _tt, OperationSymbols _op, std::string val, CVariant* _constVal = nullptr);
	void Print();
	~CToken();
};