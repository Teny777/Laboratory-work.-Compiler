#include "CIO.h"
#include "CToken.h"
#include "CVariant.h"
#include "Error.h"
#include<iostream>

//Обновление строки
void CIO::UpdateStr(char u) {

	if (u== '\n'||fin.eof()) {
		std::cout << row << ' ' << line << std::endl;;
		ShowError();
		line = "";
		row++;
		ind = 0;
		errList.clear();
		return;
	}
	line += u;
	ind++;
	
}
//Вывод ошибок
void CIO::ShowError() {
	int ind = -(int)std::to_string(row).size();
	for (auto u : errList) {
		while (ind != u->GetPosition().column) {
			std::cout << ' ';
			ind++;
		}
		std::cout << '^';
	}
	std::cout << std::endl;
	for (auto u : errList) {
		std::cout << "**" << errCount++ << "**:  Rows: " << u->GetPosition().row << "  Index: " << u->GetPosition().column << std::endl;
		std::cout << "Error Code is " << u->GetErrorCode() << std::endl;
		std::cout << u->DecryptionOfError[u->GetErrorCode()] << std::endl;
	}
	std::cout << std::endl << std::endl;
}

//Получение символа из файла
char CIO::GetNextCh() {
	char ch;
	fin.get(ch);
	UpdateStr(ch);
	while (DeleteComment(ch));
	if (fin.eof()) {
		std::cout << "Total Errors is " << errCount-1 << std::endl;
		return NULL;
	}
	return ch;
}

//Удаление комментария
bool CIO::DeleteComment(char &ch) {
	char nxt;
	
	// Однострочный комментария
	if (ch == '/') {
		fin.get(nxt);
		if (nxt == '/') {
			UpdateStr(nxt);
			while (ch != '\n') {
				fin.get(ch);
				UpdateStr(ch);
			}
			fin.get(ch);
			UpdateStr(ch);
			return true;
		}
		fin.seekg(-1, std::ios::cur);
		return false;
	}
	// Многострочный комментарий {.....}
	if (ch == '{') {
		while (ch != '}') {
			fin.get(ch);
			UpdateStr(ch);
		}
		fin.get(ch);
		UpdateStr(ch);
		return true;
	}
	// Многострочный комментарий (*....*)
	if (ch == '(') {
		fin.get(nxt);
		if (nxt != '*') {
			fin.seekg(-1, std::ios::cur);
			return false;
		}
		UpdateStr(nxt);
		fin.get(ch);
		UpdateStr(ch);
		while (true) {
			while (ch != '*') {
				fin.get(ch);
				UpdateStr(ch);
			}
			fin.get(ch);
			UpdateStr(ch);
			if (ch == ')') {
				fin.get(ch);
				UpdateStr(ch);
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
	int len = 0;
	while (IsDigit(cur)) {
		number = number * 10 + (cur - '0');
		len++;
		cur = GetNextCh();
	}
	//Проверка на неверно описанную переменную
	if (IsLetter(cur)) errList.push_back(new LexError(Position(row, ind-len), invalidToken));
	if (cur != '.') {
		if (number * sgn > 32767 || number * sgn < -32768) errList.push_back(new LexError(Position(row, ind-len-1), constantOverflow));
		return new CToken(ttConst, new CIntVariant(int(number * sgn)), std::to_string(int(number * sgn))); //константа типа int
	}
	cur = GetNextCh();
	if (cur == '.') {
		cur = 35;
		if (number * sgn > 32767 || number * sgn < -32768) errList.push_back(new LexError(Position(row, ind-len-1), constantOverflow));
		return new CToken(ttConst, new CIntVariant(int(number * sgn)), std::to_string(int(number * sgn)) );

	}
	int count = 0;
	len++;
	while (IsDigit(cur)) {
		number = number * 10 + (cur - '0');
		count++;
		len++;
		cur = GetNextCh();
	}
	//Проверка на неверно описанную переменную
	if (IsLetter(cur)) errList.push_back(new LexError(Position(row, ind-len), invalidToken));
	number /= pow(10, count);
	if (number * sgn > 308 || number * sgn < -324) errList.push_back(new LexError(Position(row, ind - len-1), constantOverflow));
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
	ident = cur;
	switch (cur)
	{

		case ':':
			
			cur = GetNextCh();
			if (cur == '=') {
				ident += cur;
				cur = GetNextCh();
				return new CToken(ttOper, assignmentSy, ident);    //Оператор присваивания
			}
			return new CToken(ttOper, descriptionOfTypesSy, ident);  //Оператор определения типа переменных
			break;

		case '<':
			
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
		
			cur = GetNextCh();
			if (cur == '=') {
				ident += cur;
				cur = GetNextCh();
				return new CToken(ttOper, moreEqualSy, ident); //Оператор больше или равно
			}
			return new CToken(ttOper, moreSy, ident); //Оператор больше

		case ';':
			
			cur = GetNextCh();
			return new CToken(ttOper, semicolonSy, ident); //Оператор разделения

		case '.':
			
			cur = GetNextCh();
			if (cur == '.') {
				ident += cur;
				cur = GetNextCh();
				return new CToken(ttOper, ellipsisSy, ident); //Оператор перечисления
			}
			return new CToken(ttOper, pointSy, ident); //Оператор точка

		case ',':
			
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
			
			cur = GetNextCh();
			return new CToken(ttOper, sumSy, ident);

		case '-':
		
			cur = GetNextCh();
			return new CToken(ttOper, minusSy, ident);

		case '*':
	
			cur = GetNextCh();
			return new CToken(ttOper, mulSy, ident);



		case '=':

			cur = GetNextCh();
			return new CToken(ttOper, equalSy, ident);


		case ')':
	
			cur = GetNextCh();
			return new CToken(ttOper, closeParSy, ident);

		case '[':

			cur = GetNextCh();
			return new CToken(ttOper, openIndSy, ident);
		case ']':
	
			cur = GetNextCh();
			return new CToken(ttOper, closeIndSy, ident);
		case 35:
			ident = "..";
			cur = GetNextCh();
			return new CToken(ttOper, ellipsisSy, ident);

		case '/': {

			cur = GetNextCh();
			return new CToken(ttOper, divisionSy, ident); //Деление
		}

		case '(': {

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
	if (cur != '\0') {
		errList.push_back(new LexError(Position(row, ind), invalidCharacter));
		cur = GetNextCh();
		return new CToken(ttIdent, ident);
	}

	return nullptr;
}


CIO::~CIO() {
	fin.close();
}