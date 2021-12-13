#include "CCompiler.h"
#include <iostream>
#include <vector>
#include <map>
#include<string>


CType* CCompiler::deriveTo(CType* left, CType* right) {
	if (left == right || left->type == et_integer && right->type == et_double) return right;
    return left;
}

CCompiler::CCompiler(CLexer* _lexer,ErrorManager* _errManager) {
	lexer =_lexer;
	errManager = _errManager;
	curToken = lexer->GetNextToken();
}

void error() {
	std::cout << "Bad\n";
}

void CCompiler:: accept(OperationSymbols oper) {
	if (curToken->op != oper) error();
	curToken = lexer->GetNextToken();
}

void CCompiler:: accept(TokenType _tt) {
	if(curToken->tt!=_tt)  error();
	curToken = lexer->GetNextToken();
}

//�������� ���������
void CCompiler::CheckProgram() {
	/*<���������>:: = program <���>; <����>.*/

	accept(programsy);
	accept(ttIdent);
	accept(semicolonSy);
	block();
	accept(pointSy);
}


//����
void CCompiler::block() {
	/*<����>:: = <������ ����������> <������ ����������>*/
	varpart();
	operatorssection();
}

//������ ����������
void CCompiler::varpart() {
	/*<������ ����������>:: = var <�������� ���������� ����������>;
	{<�������� ���������� ����������>; }*/

	accept(varsy);
	sametype();
	accept(semicolonSy);
	while (curToken->tt == ttIdent) {
		sametype();
		accept(semicolonSy);
	}
}

//�������� ���������� ����������
void CCompiler::sametype() {
	/*<�������� ���������� ����������>:: = <���>{ ,<���> }:<���>*/
	std::vector<CToken*> variables;
	variables.push_back(curToken);
	accept(ttIdent);
	while (curToken->op == commaSy) {
		curToken = lexer->GetNextToken();
		variables.push_back(curToken);
		accept(ttIdent);
	}


	accept(descriptionOfTypesSy);
	CType * _type = type();
	if (_type) {	
		for (auto variable : variables) {
			if (availableVariables[variable->GetIdent()] && !variablesError[variable->GetIdent()]) {
				errManager->AddError( repeatVariable, variable->GetPosition());
				variablesError[variable->GetIdent()] = true;
				continue;
			}
			availableVariables[variable->GetIdent()] = _type;
		}
	}
	else errManager->AddError( invalidType, curToken->GetPosition());
	curToken = lexer->GetNextToken();


}

//���
CType* CCompiler::type() {
	/*<���>:: = <��� ����>*/
	return availableTypes[curToken->GetIdent()];
	
}

//������ ����������
void CCompiler::operatorssection() {
	/*<������ ����������>:: = <��������� ��������>*/

	compoundoperator();
}

// ��������� ��������
void CCompiler::compoundoperator() {
	/*<��������� ��������>:: = begin <��������>{ ; <��������> } end*/

	accept(beginsy);
	ooperator();
	while (curToken->op == semicolonSy) {
		curToken = lexer->GetNextToken();
		ooperator();
	}
	accept(endsy);
}

// ��������
void CCompiler::ooperator() {
	/*<��������>::=<������������ ��������>*/

	unlabeledoperator();
}

//������������ ��������
void CCompiler::unlabeledoperator() {

	/*<������������ ��������>:: = <������� ��������> | <������� ��������>*/

	if(curToken->op== beginsy|| curToken->op == ifsy || curToken->op == whilesy )
		complexoperator();
	else simpleoperator();
}

//������� ��������
void CCompiler::simpleoperator() {
	/*<������� ��������>:: = <�������� ������������>*/
	if(curToken->tt ==ttIdent)
		assignmentoperator();
}



//������� ��������
void CCompiler::complexoperator() {
	switch (curToken->op)
	{
	case beginsy:
		compoundoperator();
		break;
	case ifsy:
		selectingoperator();
		break;
	case whilesy:
		cycleoperator();
		break;
	default:
		break;
	} 
}

//�������� ������������
void CCompiler::assignmentoperator() {
	/*<�������� ������������>:: = <����������>: = <���������>*/


	CType* left = nullptr;
	if (curToken->tt == ttIdent) left = availableVariables[curToken->GetIdent()];
	curToken = lexer->GetNextToken();
	position posOperation = curToken->GetPosition();
	accept(assignmentSy);
	CType* right = expression();
	if(!right||!right->isDerivedTo(left))  errManager->AddError(incompatibleTypes, posOperation);
}


//���������
CType* CCompiler::expression() {
	/*<���������>:: = <������� ���������> | <������� ���������>
		<�������� ���������><������� ���������>

	<�������� ���������>::==|<> | <|<=|>=|> | in*/

	CType* left = simpleexpression();
	position posOperation;

	if(curToken->op == equalSy || curToken->op == notEqualSy || curToken->op == lessSy || curToken->op == lessEqualSy ||
		curToken->op == moreEqualSy || curToken->op == moreSy || curToken->op == insy) {

		posOperation = curToken->GetPosition();
		curToken = lexer->GetNextToken();
		CType* right = simpleexpression();

		if (left&&left->isDerivedTo(right)||right&&right->isDerivedTo(left)) return availableTypes["boolean"];
		else errManager->AddError( incompatibleTypes, posOperation);
	}
	return left;
}

//������� ���������
CType* CCompiler::simpleexpression() {
	/*<������� ���������>:: = [<����>]<���������>
	{ <���������� ��������><���������> }

	<����>::=+|-
	
	<���������� ��������>::=+|-|or*/

	if(curToken->op== sumSy||curToken->op== minusSy) curToken = lexer->GetNextToken();
	CType* left =summand();
	position posOperation;

	while (curToken->op == sumSy || curToken->op == minusSy || curToken->op == orsy) {

		posOperation = curToken->GetPosition();
		curToken = lexer->GetNextToken();
		CType* right = summand();
		if (left && left->isDerivedTo(right) || right && right->isDerivedTo(left)) left = deriveTo(left, right);
		else errManager->AddError( incompatibleTypes, posOperation);
	}

	return left;
	
}

//���������
CType* CCompiler::summand() {

	/*<���������>::=<���������>{<����������������� ��������> <���������>}
	
	<����������������� ��������>::=*|/|div|mod|and*/

	CType* left = factor();
	position posOperation;

	while (curToken->op == mulSy || curToken->op == divisionSy || curToken->op == divsy || curToken->op == modsy || curToken->op == andsy) {

		posOperation = curToken->GetPosition();
		curToken = lexer->GetNextToken();
		CType* right = factor();
		if (left && left->isDerivedTo(right) || right && right->isDerivedTo(left)) left = deriveTo(left, right);
		else errManager->AddError( incompatibleTypes, posOperation);
	}
	return left;
}

//���������
CType* CCompiler::factor() {
	/*<���������>::=<����������>|<��������� ��� �����>| (<���������>) */


	if (curToken->tt == ttIdent) { 
		if (!availableVariables[curToken->GetIdent()] && !variablesError[curToken->GetIdent()]) {
			errManager->AddError(undeclaredIdent, curToken->GetPosition());
			variablesError[curToken->GetIdent()] = true;
		}
		std::string ident = curToken->GetIdent();
		curToken = lexer->GetNextToken();
		return availableVariables[ident];
	}
	else if (curToken->tt == ttConst) {

		std::string type = curToken->constVal->GetClassType();
		curToken = lexer->GetNextToken();
		return availableTypes[type];
	}

	else if (curToken->op == openParSy) {
		accept(openParSy);
		CType* left =  expression();
		accept(closeParSy);
		return left;
	}
	else error();

}

//���������� ��������
void CCompiler::selectingoperator() {
	/*<���������� ��������>:: = <�������� ��������>*/
	conditionaloperator();
}

//�������� �����
void CCompiler::cycleoperator() {
	/*<�������� �����>::=<���� � ������������>*/

	whilepart();
}

//�������� ��������
void CCompiler::conditionaloperator() {
	/*<�������� ��������>:: = if <���������> then <��������> |
		if <���������> then <��������> else <��������>*/
	position posOperation = curToken->GetPosition();;
	accept(ifsy);
	CType* left = expression();
	if(!left||!left->isDerivedTo(availableTypes["boolean"])) errManager->AddError(expressionBool, posOperation);
	accept(thensy);
	ooperator();
	if (curToken->op == elsesy) {
		accept(elsesy);
		ooperator();
	}
}

//���� � ������������
void CCompiler::whilepart() {
	/*<���� � ������������>:: = while <���������> do <��������>*/
	position posOperation = curToken->GetPosition();;
	accept(whilesy);
	CType* left = expression();
	if (!left || !left->isDerivedTo(availableTypes["boolean"])) errManager->AddError(expressionBool, posOperation);
	accept(dosy);
	ooperator();
}