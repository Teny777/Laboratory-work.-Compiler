#include "CLexer.h"
#include<string>


CLexer::CLexer(CIO* io,ErrorManager* _errManager) {
	IO = io;
	errManager = _errManager;
}


//Проверка на буку
bool CLexer :: IsLetter(char cur) {
	return cur >= 'a' && cur <= 'z' || cur >= 'A' && cur <= 'Z';
}

//Проверка на цифру
bool CLexer :: IsDigit(char cur) {
	return cur >= '0' && cur <= '9';
}

//Неверный идентификатор
CToken* CLexer::IncorrectIdent(std::string ident) {
	while (IsLetter(curLiter) || IsDigit(curLiter)) {
		ident += curLiter;
		curLiter = IO->GetNextCh();
	}
	errManager->AddError(invalidIdent, IO->GetPrevPosition());
	return new CToken(ttSpec, ident, IO->GetPrevPosition());
}

//Пролучение слова
CToken* CLexer ::GetWord() {
	std::string ident;
	ident = curLiter;
	curLiter = IO->GetNextCh();
	while (IsLetter(curLiter) || IsDigit(curLiter)) {
		ident += curLiter;
		curLiter = IO->GetNextCh();
	}
	if (keyWords.count(ident))
		return new CToken(ttOper, GetOperKeySy[ident], ident,IO->GetPrevPosition());

	return new CToken(ttIdent, ident,IO->GetPrevPosition());
}



CToken* CLexer::GetDigitConst() {
	std::string number = "";
	while (IsDigit(curLiter)) {
		number += curLiter;
		curLiter = IO->GetNextCh();
	}

	//Неверный идентификатор
	if (IsLetter(curLiter))
		return IncorrectIdent(number);


	if (curLiter != '.') 
	{
		if (CheckIntConst(std::stoi(number))) {
			errManager->AddError( constantOverflow, IO->GetPrevPosition());
			return new CToken(ttSpec, number, IO->GetPrevPosition());
		}
		return new CToken(ttConst, new CIntVariant(std::stoi(number)), number,IO->GetPrevPosition()); //Константа int
	}
	curLiter = IO->GetNextCh();

	//Для перечисления ..
	if (curLiter == '.') {
		
		if (CheckIntConst(std::stoi(number))) {
			errManager->AddError( constantOverflow, IO->GetPrevPosition());
			return new CToken(ttSpec, number, IO->GetPrevPosition());
		}
		curLiter = 35;
		return new CToken(ttConst, new CIntVariant(std::stoi(number)), number, IO->GetPrevPosition());
	}

	number += '.';

	while (IsDigit(curLiter)) {
		number += curLiter;
		curLiter = IO->GetNextCh();
	}
	//Неверный идентификатор
	if (IsLetter(curLiter))
		return IncorrectIdent(number);

	if (CheckDoubleConst(std::stod(number))) {
		errManager->AddError( constantOverflow, IO->GetPrevPosition());
		return new CToken(ttSpec, number, IO->GetPrevPosition());
	}
	return new CToken(ttConst, new CDoubleVariant(std::stod(number)), number, IO->GetPrevPosition()); //Константа double
}


// Получение следующего токена
CToken* CLexer::GetNextToken() {
	std::string ident;
	if (curLiter == -1) curLiter = IO->GetNextCh();
	while (curLiter == ' ' || curLiter == '\n') curLiter = IO->GetNextCh();
	ident = curLiter;


	switch (curLiter)
	{

	case ':':

		curLiter = IO->GetNextCh();
		if (curLiter == '=') {
			ident += curLiter;
			curLiter = IO->GetNextCh();
			return new CToken(ttOper, assignmentSy, ident, IO->GetPrevPosition());    //Оператор присваивания
		}
		return new CToken(ttOper, descriptionOfTypesSy, ident, IO->GetPrevPosition());  //Оператор определения типа переменных
		break;

	case '<':

		curLiter = IO->GetNextCh();
		if (curLiter == '>') {
			ident += curLiter;
			curLiter = IO->GetNextCh();
			return new CToken(ttOper, notEqualSy, ident, IO->GetPrevPosition()); //Оператор не равно
		}
		if (curLiter == '=') {
			ident += curLiter;
			curLiter = IO->GetNextCh();
			return new CToken(ttOper, lessEqualSy, ident, IO->GetPrevPosition()); //Оператор меньше или равно
		}
		return new CToken(ttOper, lessSy, ident, IO->GetPrevPosition()); //Оператор меньше

	case '>':

		curLiter = IO->GetNextCh();
		if (curLiter == '=') {
			ident += curLiter;
			curLiter = IO->GetNextCh();
			return new CToken(ttOper, moreEqualSy, ident, IO->GetPrevPosition()); //Оператор больше или равно
		}
		return new CToken(ttOper, moreSy, ident, IO->GetPrevPosition()); //Оператор больше

	case ';':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, semicolonSy, ident, IO->GetPrevPosition()); //Оператор разделения

	case '.':

		curLiter = IO->GetNextCh();
		if (curLiter == '.') {
			ident += curLiter;
			curLiter = IO->GetNextCh();
			return new CToken(ttOper, ellipsisSy, ident, IO->GetPrevPosition()); //Оператор перечисления
		}
		return new CToken(ttOper, pointSy, ident, IO->GetPrevPosition()); //Оператор точка

	case ',':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, commaSy, ident, IO->GetPrevPosition());

	case '\'': {
		std::string stringConst = "'";
		do {
			curLiter = IO->GetNextCh();
			stringConst += curLiter;
		} while (curLiter != '\'');
		curLiter = IO->GetNextCh();
		return new CToken(ttConst, new CStringVariant(stringConst), stringConst, IO->GetPrevPosition()); //Строковая константа
	}

	case '+':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, sumSy, ident, IO->GetPrevPosition());

	case '-':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, minusSy, ident, IO->GetPrevPosition());

	case '*':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, mulSy, ident, IO->GetPrevPosition());



	case '=':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, equalSy, ident, IO->GetPrevPosition());


	case ')':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, closeParSy, ident, IO->GetPrevPosition());

	case '[':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, openIndSy, ident, IO->GetPrevPosition());
	case ']':

		curLiter = IO->GetNextCh();
		return new CToken(ttOper, closeIndSy, ident, IO->GetPrevPosition());
	case 35:
		ident = "..";
		curLiter = IO->GetNextCh();
		return new CToken(ttOper, ellipsisSy, ident, IO->GetPrevPosition()); //Перечисление полсе константы int 

	case '/': {

		curLiter = IO->GetNextCh();
		if(curLiter!='/') return new CToken(ttOper, divisionSy, ident, IO->GetPrevPosition()); //Деление
		curLiter = IO->GetNextCh();
		while (curLiter != '\n' && curLiter != '\0') 
			curLiter = IO->GetNextCh();
		curLiter = IO->GetNextCh();
		return GetNextToken();

	}

	case '(': {
		curLiter = IO->GetNextCh();
		if (curLiter != '*') return new CToken(ttOper, openParSy, ident, IO->GetPrevPosition());
		curLiter = IO->GetNextCh();

		while (true) {
			while (curLiter != '*') 
				curLiter = IO->GetNextCh();

			curLiter = IO->GetNextCh();
			if (curLiter == ')') {
				curLiter = IO->GetNextCh();
				return GetNextToken(); // Пропуск многострочного комментария (*...*)
			}
		}
	}

	case '{': {
		while (curLiter != '}') 
			curLiter = IO->GetNextCh();
		curLiter = IO->GetNextCh();
		return GetNextToken(); //Пропуск многострочного комментария {}
	}
	}

	//Получение идентификатора
	if (IsLetter(curLiter)) return GetWord();

	//Получение константы
	if (IsDigit(curLiter)) return GetDigitConst();

	if (curLiter != '\0') {
		errManager->AddError( invalidCharacter, IO->GetPosition());
		curLiter = IO->GetNextCh();
		return new CToken(ttSpec, ident, IO->GetPrevPosition());
	}

	return new CToken(ttSpec, ident, IO->GetPrevPosition());
}


bool CLexer::CheckIntConst(int val) {
	return (val > 32767 || val < -32768);
}

bool CLexer::CheckDoubleConst(double val) {
	return (val > 308 || val < -324);
}

CLexer::~CLexer() {
	delete IO;
}