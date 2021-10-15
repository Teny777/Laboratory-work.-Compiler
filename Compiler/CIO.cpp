#include "CIO.h"
#include "CToken.h"
#include "CVariant.h"



//Получение символа из файла
char CIO::GetNextCh() {
	char ch;
	fin.get(ch);
	while (DeleteComment(ch));
	if (fin.eof()) return NULL;
	return ch;
}

//Удаление комментария
bool CIO::DeleteComment(char &ch) {
	char nxt;
	if (ch == '/') {
		fin.get(nxt);
		if (nxt == '/') {
			while (ch != '\n')
				fin.get(ch);
			fin.get(ch);
			return true;
		}
		fin.seekg(-1, std::ios::cur);
		return false;
	}
	if (ch == '{') {
		while(ch!='}')
			fin.get(ch);
		fin.get(ch);
		return true;
	}
	if (ch == '(') {
		fin.get(nxt);
		if (nxt != '*') {
			fin.seekg(-1, std::ios::cur);
			return false;
		}
		fin.get(ch);
		while (true) {
			while (ch != '*') {
				fin.get(ch);
			}
			fin.get(ch);
			if (ch == ')') {
				fin.get(ch);
				return true;
			}
		}

	}
	return false;
}

//Проверка на букву
bool CIO::IsLetter(char cur) {
	return cur >= 'a' && cur <= 'z' || cur >= 'A' && cur <= 'Z';
}

//Проверка на число
bool CIO::IsDigit(char cur) {
	return cur >= '0' && cur <= '9';
}

CIO::CIO(std::string path) {
	fin.open(path);
}

//Получение числовой константы
CToken* CIO::GetDigitConst(int sgn) {
	double number = 0;
	while (IsDigit(cur)) {
		number = number * 10 + (cur - '0');
		cur = GetNextCh();
	}
	if (cur != '.') return new CToken(ttConst,  new CIntVariant(int(number * sgn)), std::to_string(int(number* sgn))); //константа типа int
	cur = GetNextCh();
	if (cur == '.') {
		cur = '&';
		return new CToken(ttConst, new CIntVariant(int(number * sgn)), std::to_string(int(number * sgn)) );

	}
	int count = 0;
	while (IsDigit(cur)) {
		number = number * 10 + (cur - '0');
		count++;
		cur = GetNextCh();
	}
	number /= pow(10, count);
	return new CToken(ttConst, new CDoubleVariant(number * sgn), std::to_string(number * sgn)); //константа типа double
}
//Получение слова
CToken* CIO::GetWord() {
	std::string ident;
	ident = cur;
	cur = GetNextCh();
	while (IsLetter(cur) || IsDigit(cur)) {
		ident += cur;
		cur = GetNextCh();
	}
	if (keyWords.count(ident)) {
		return new CToken(ttOper, GetOperSy[ident], ident);
	}
	return new CToken(ttIdent, ident);
}

//Получение следующего токена
CToken* CIO::GetNextToken() {

	if (cur == -1) cur = GetNextCh();
	while (cur == ' ' || cur == '\n') cur = GetNextCh();
	std::string ident;
	
	switch (cur)
	{

	case ':':
		ident = cur;
		cur = GetNextCh();
		if (cur == '=') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, assignmentSy, ident);    //Оператор присваивания
		}
		return new CToken(ttOper, descriptionOfTypesSy, ident);  //Оператор определения типа переменных
		break;

	case '<':
		ident = cur;
		cur = GetNextCh();
		if (cur == '>') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, notEqualSy, ident); //Оператор не равно
		}
		if (cur == '=') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, lessEqualSy, ident); //Оператор меньше или равно
		}
		return new CToken(ttOper, lessSy, ident); //Оператор меньше

	case '>':
		ident = cur;
		cur = GetNextCh();
		if (cur == '=') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, moreEqualSy, ident); //Оператор больше или равно
		}
		return new CToken(ttOper, moreSy, ident); //Оператор больше

	case ';':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, semicolonSy, ident); //Оператор разделения

	case '.':
		ident = cur;
		cur = GetNextCh();
		if (cur == '.') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, ellipsisSy, ident); //Оператор перечисления
		}
		return new CToken(ttOper, pointSy, ident); //Оператор точка

	case ',':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, commaSy, ident);

	case '\'': {
		std::string stringConst = "'";
		do {
			cur = GetNextCh();
			stringConst += cur;
		} while (cur != '\'');
		cur = GetNextCh();
		return new CToken(ttConst, new CStringVariant(stringConst), stringConst); //Строковая константа
	}

	case '+':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, sumSy, ident);

	case '-':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, minusSy, ident);

	case '*':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, mulSy, ident);



	case '=':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, equalSy, ident);


	case ')':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, closeParSy, ident);

	case '[':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, openIndSy, ident);
	case ']':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, closeIndSy, ident);
	case '&':
		ident = "..";
		cur = GetNextCh();
		return new CToken(ttOper, ellipsisSy, ident);

	case '/': {
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, divisionSy, ident); //Деление
	}

	case '(': {
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, openParSy, ident);

	}
	}

	//Считывание числовой константы
	if (IsDigit(cur)) 
		return GetDigitConst(1);

	//Проверка ключевого слова или переменной 
	if (IsLetter(cur)) 
		return GetWord();

	return nullptr;
}


CIO::~CIO() {
	fin.close();
}