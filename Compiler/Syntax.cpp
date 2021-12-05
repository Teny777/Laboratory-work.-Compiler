#include "Syntax.h"
#include <iostream>

Syntax::Syntax(CLexer *_lexer,ErrorManager* _errManager) {
	lexer = _lexer;
	errManager = _errManager;
	curToken = lexer->GetNextToken();
}



void Syntax::accept(OperationSymbols oper) {
	if (curToken==nullptr||curToken->tt != ttOper || curToken->op != oper) std::cout << "Bad\n";
	curToken = lexer->GetNextToken();
}

void Syntax :: accept(TokenType _tt) {
	if(curToken==nullptr||curToken->tt!=_tt)  std::cout << "Bad\n";
	curToken = lexer->GetNextToken();
}

//проверка программы
void Syntax::CheckProgram() {
	accept(programsy);
	accept(ttIdent);
	accept(semicolonSy);
	block();
	accept(pointSy);
}


//блок
void Syntax::block() {
	varpart();
	compoundop();
}


//раздел переменных
void Syntax::varpart() {
	accept(varsy);
	sametype();
	accept(semicolonSy);
	while (curToken->tt == ttIdent) {
		sametype();
		accept(semicolonSy);
	}
}


//описание однотипных переменных
void Syntax::sametype() {
	accept(ttIdent);
	while (curToken->tt == ttOper && curToken->op == commaSy) {
		curToken = lexer->GetNextToken();
		accept(ttIdent);
	}
	accept(descriptionOfTypesSy);
	type();
}


//тип
void Syntax::type() {
	simpletype();
	
}

//простой тип
void Syntax::simpletype() {
	typeName();
}

void Syntax::typeName() {
	if(curToken==nullptr||curToken->tt!=ttOper&&curToken->op!=integersy&&curToken->op!=longintsy&&curToken->op!=stringsy&&curToken->op!=doublesy&&curToken->op!=booleansy) std::cout << "Bad\n";
	curToken = lexer->GetNextToken();
}

void Syntax::compoundop() {
	accept(beginsy);
	operat();
	accept(endsy);
}


void Syntax::operat() {
	if (curToken->tt == ttConst && curToken->constVal->GetClassType() == "IntConst") {
		auto val = (CIntVariant*)(curToken->constVal);
		if (val->GetValue() >= 0) curToken = lexer->GetNextToken();
		else std::cout << "BAD\n";
	}
	unmarkedOper();
}

void Syntax::unmarkedOper() {
	simpleope();
}


void Syntax::simpleope() {
	assignmentop();

}
void Syntax::complexop() {

}

void Syntax::assignmentop() {
	accept(ttIdent);
	accept(assignmentSy);
	expression();
}
void Syntax::expression() {

}
void Syntax::summand() {

}

void Syntax::multiplier() {

}