#include "CIO.h"
#include "CToken.h"
#include "CVariant.h"



//Получение символа из файла
char CIO::GetNextCh() {
	char ch;
	fin.get(ch);
	if (fin.eof()) return NULL;
	return ch;
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
		return new CToken(ttConst, null, stringConst, new CStringVariant(stringConst)); //Строковая константа
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

	case '/': {
		ident = cur;
		cur = GetNextCh();
		if (cur != '/') return new CToken(ttOper, divisionSy, ident); //Деление
		std::string comment = "//";
		cur = GetNextCh();
		while (cur != '\n' && cur != '\0') {
			comment += cur;
			cur = GetNextCh();
		}
		cur = GetNextCh();
		return new CToken(ttComment, null, comment); //Однострочный комментарий
	}

	case '=':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, equalSy, ident);

	case '(': {
		ident = cur;
		cur = GetNextCh();
		if (cur != '*') return new CToken(ttOper, openParSy, ident);
		cur = GetNextCh();
		std::string comment = "(*";
		comment += cur;

		while (true) {
			while (cur != '*') {
				cur = GetNextCh();
				comment += cur;
			}
			cur = GetNextCh();
			comment += cur;
			if (cur == ')') {
				cur = GetNextCh();
				return new CToken(ttComment, null, comment); //Комментарий (*....*)
			}
		}
	}
	case ')':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, closeParSy, ident);



	case '{': {
		std::string comment = "{";

		while (cur != '}') {

			cur = GetNextCh();
			comment += cur;
		}
		cur = GetNextCh();
		return new CToken(ttComment, null, comment); //Многострочный комментарий {..}
	}

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
	}

	//Считывание числовой константы
	if (IsDigit(cur)) {
		double number = 0;
		while (IsDigit(cur)) {
			number = number * 10 + (cur - '0');
			cur = GetNextCh();
		}
		if (cur != '.') return new CToken(ttConst, null, std::to_string(int(number)), new CIntVariant(int(number))); //константа типа int
		cur = GetNextCh();
		if (cur == '.') {
			cur = '&';
			return new CToken(ttConst, null, std::to_string(int(number)), new CIntVariant(int(number)));

		}
		int count = 0;

		while (IsDigit(cur)) {
			number = number * 10 + (cur - '0');
			count++;
			cur = GetNextCh();
		}
		number /= pow(10, count);
		return new CToken(ttConst, null, std::to_string(number), new CDoubleVariant(number)); //константа типа double

	}
	//Проверка ключевого слова или переменной 
	if (IsLetter(cur)) {
		ident = cur;
		cur = GetNextCh();
		while (IsLetter(cur) || IsDigit(cur)) {
			ident += cur;
			cur = GetNextCh();
		}
		if (keyWords.count(ident)) {
			if (ident == "div") return new CToken(ttOper, divSy, ident);
			if (ident == "mod") return new CToken(ttOper, modSy, ident);
			return new CToken(ttKeyWord, null, ident);
		}
		variable.insert(ident);
		return new CToken(ttIdent, null, ident);

	}
	return nullptr;
}


CIO::~CIO() {
	fin.close();
}