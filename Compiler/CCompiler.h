#pragma once
#include<string>
#include <set>
#include "CLexer.h"
#include "CToken.h"
#include "ErrorManager.h"
#include "CType.h"

class CCompiler {



private:

	std::map<std::string, CType*> availableTypes = { // ���������� ����
	{"integer",new CIntType(et_integer)},
	{"double",new CDoubleType(et_double)},
	{"string",new CStringType(et_string)},
	{"boolean",new CBoolType(et_bool)}
	};
	std::map<std::string, CType*> availableVariables; // ���������� ����������
	std::map<std::string, bool> variablesError; // ������ ����������

	CType* deriveTo(CType* left, CType* right);

	CLexer* lexer;
	CToken* curToken;
	ErrorManager* errManager;

	void accept(OperationSymbols op);
	void accept(TokenType _tt);

	void block(); //����

	void varpart(); //������ ����������

	void sametype(); //�������� ���������� ����������

	CType* type(); //���

	void operatorssection(); //������ ����������

	void compoundoperator(); // ��������� ��������

	void ooperator(); // ��������

	void unlabeledoperator(); //������������ ��������

	void simpleoperator(); //������� ��������

	void complexoperator(); //������� ��������

	void assignmentoperator(); //�������� ������������

	CType* expression(); //���������

	CType* simpleexpression(); //������� ���������

	CType* summand(); //���������

	CType* factor(); //���������

	void selectingoperator(); //���������� ��������

	void cycleoperator(); //�������� �����

	void conditionaloperator(); //�������� ��������

	void whilepart(); //���� � ������������

public:
	CCompiler (CLexer* _lexer,ErrorManager* _errManager);
	void CheckProgram();
};