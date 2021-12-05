#pragma once
#include<string>
#include "CLexer.h"
#include "CToken.h"
#include "ErrorManager.h"
class Syntax {
private:
	CLexer* lexer;
	CToken* curToken;
	ErrorManager* errManager;

	void accept(OperationSymbols op);
	void accept(TokenType _tt);

	void block(); //����
	void varpart(); //������ ����������
	void sametype(); //�������� ���������� ����������
	void type(); //���
	void simpletype(); //������� ���
	void typeName(); //��� ����
	void compoundop(); //��������� ��������
	void operat(); //������ ����������
	void unmarkedOper(); //������������ ��������
	void simpleope(); //������� ��������
	void complexop(); //������� ��������
	void assignmentop(); //�������� ������������
	void expression(); //���������
	void summand(); //���������
	void multiplier(); //���������

public:
	Syntax(CLexer* _lexer,ErrorManager* _errManager);
	void CheckProgram();
};