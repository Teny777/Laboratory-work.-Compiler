#include<string>
#include<fstream>
#include<iostream>
#include<map>

// Тип токена
enum TokenType {
	ttKeyWord,
	ttIdent,
	ttConst,
	ttOper,
	ttComment
};


//Ключевые слова
enum KeyWords {
	being,
	var,
	end
};

//Операции 
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
	closeIndSy
};



class CVariant {
public:
	virtual std::string GetClassType() = 0;
	virtual std::string GetStrValue() = 0;
};


class CIntVariant : public CVariant {
private:
	int value;

public:
	CIntVariant(int _val) {
		value = _val;
	}
	std::string GetClassType() override {
		return "int";
	}
	int GetValue() {
		return value;
	}

	std::string GetStrValue() override {
		return std::to_string(value);
	}
};


class CDoubleVariant : public CVariant {
private:
	double value;
public:
	CDoubleVariant(double _val) {
		value = _val;
	}

	std::string GetClassType() override {
		return "double";
	}
	double GetValue() {
		return value;
	}

	std::string GetStrValue() override {
		return std::to_string(value);
	}

};


class CStringVariant : public CVariant {
private:
	std::string value;
public:
	CStringVariant(std::string _val) {
		value = _val;
	}

	std::string GetClassType() override {
		return "string";
	}
	std::string GetValue() {
		return value;
	}

	std::string GetStrValue() override {
		return value;
	}
};


class CToken {
private:
	TokenType tt;
	OperationSymbols op;
	std::map<OperationSymbols, std::pair<std::string, std::string>> ValueOfOp;
	CVariant* constVal;
	std::string comment;

public:

	void GetValueOfOp() {

		ValueOfOp[assignmentSy] = { "Assignment",":=" };
		ValueOfOp[descriptionOfTypesSy] = { "Description Of Types","::" };
		ValueOfOp[notEqualSy] = { "Comparison","<>" };
		ValueOfOp[lessEqualSy] = { "Comparison","<="};
		ValueOfOp[lessSy] = { "Comparison","<" };
		ValueOfOp[moreEqualSy] = { "Comparison",">=" };
		ValueOfOp[moreSy] = { "Comparison",">" };
		ValueOfOp[semicolonSy] = { "Separator",";" };
		ValueOfOp[pointSy] = { "Separator","." };
		ValueOfOp[ellipsisSy] = { "ellipsis",".." };
		ValueOfOp[sumSy] = { "Arithmetic Operators","+" };
		ValueOfOp[minusSy] = { "Arithmetic Operators","-" };
		ValueOfOp[divisionSy] = { "Arithmetic Operators","/" };
		ValueOfOp[equalSy] = { "Comparison","=" };
		ValueOfOp[mulSy] = { "Arithmetic Operators","*" };
		ValueOfOp[openParSy] = { "Separator","(" };
		ValueOfOp[closeParSy] = { "Separator",")" };
		ValueOfOp[openIndSy] = { "Separator","[" };
		ValueOfOp[closeIndSy] = { "Separator","]" };
	}

	CToken(TokenType _tt, OperationSymbols _op, CVariant* _constVal = nullptr, std::string _com = "") {
		tt = _tt;
		op = _op;
		constVal = _constVal;
		comment = _com;
		GetValueOfOp();
	}

	void Print() {
		if (this == nullptr) return;
		if (tt == ttConst) {
			if (constVal->GetClassType() == "int") {
				std::cout << "Type: IntConst\nValue = " << constVal->GetStrValue() << '\n' << '\n';
				return;
			}
			if (constVal->GetClassType() == "double") {
				std::cout << "Type: DoubleConst\nValue = " << constVal->GetStrValue() << '\n' << '\n';
				return;
			}
			if (constVal->GetClassType() == "string") {
				std::cout << "Type: StringConst\nValue = " << constVal->GetStrValue() << '\n' << '\n';
				return;
			}
		}
		if (tt == ttOper) {
			std::cout <<"Type: "<< ValueOfOp[op].first << '\n' << ValueOfOp[op].second << '\n' << '\n';
			return;
		}
	}

};

class CIO {
private:
	std::ifstream fin;
	char cur = -1;

	//Получение символа из файла
	char GetNextCh() {
		char ch;
		fin.get(ch);
		if (fin.eof()) return NULL;
		return ch;
	}

	//Проверка на букву
	bool IsLetter(char cur) {
		return cur >= 'a' && cur <= 'z' || cur >= 'A' && cur <= 'Z';
	}

	//Проверка на число
	bool IsDigit(char cur) {
		return cur >= '0' && cur <= '9';
	}


public:

	CIO(std::string path) {
		fin.open(path);
	}

	//Получение следующего токена
	CToken* GetNextToken() {
		if (cur == -1) cur = GetNextCh();
		while (cur == ' ' || cur == '\n') cur = GetNextCh();

		switch (cur)
		{
		case ':':
			cur = GetNextCh();
			if (cur == '=') {
				cur = GetNextCh();
				return new CToken(ttOper, assignmentSy);    //Оператор присваивания
			}
			return new CToken(ttOper, descriptionOfTypesSy);  //Оператор определения типа переменных
			break;

		case '<':

			cur = GetNextCh();
			if (cur == '>') {
				cur = GetNextCh();
				return new CToken(ttOper, notEqualSy); //Оператор не равно
			}
			if (cur == '=') {
				cur = GetNextCh();
				return new CToken(ttOper, lessEqualSy); //Оператор меньше или равно
			}
			return new CToken(ttOper, lessSy); //Оператор меньше

		case '>':
			cur = GetNextCh();
			if (cur == '=') {
				cur = GetNextCh();
				return new CToken(ttOper, moreEqualSy); //Оператор больше или равно
			}
			return new CToken(ttOper, moreSy); //Оператор больше

		case ';':
			cur = GetNextCh();
			return new CToken(ttOper, semicolonSy); //Оператор разделения

		case '.':
			cur = GetNextCh();
			if (cur == '.') {
				cur = GetNextCh();
				return new CToken(ttOper, ellipsisSy); //Оператор перечисления
			}
			return new CToken(ttOper, pointSy); //Оператор точка


		case '\'': {
			std::string stringConst = "'";
			do {
				cur = GetNextCh();
				stringConst += cur;
			} while (cur != '\'');
			cur = GetNextCh();
			return new CToken(ttConst, null, new CStringVariant(stringConst)); //Строковая константа
		}

		case '+':
			cur = GetNextCh();
			return new CToken(ttOper, sumSy);

		case '-':
			cur = GetNextCh();
			return new CToken(ttOper, minusSy);

		case '*':
			cur = GetNextCh();
			return new CToken(ttOper, mulSy);

		case '/': {
			cur = GetNextCh();
			if (cur != '/') return new CToken(ttOper, divisionSy); //Деление
			std::string comment = "//";
			cur = GetNextCh();
			while (cur != '\n' && cur != '\0') {
				comment += cur;
				cur = GetNextCh();
			}
			cur = GetNextCh();
			return new CToken(ttComment, null, nullptr, comment); //Однострочный комментарий
		}

		case '=':
			cur = GetNextCh();
			return new CToken(ttOper, equalSy);

		case '(': {

			cur = GetNextCh();
			if (cur != '*') return new CToken(ttOper, openParSy);
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
					return new CToken(ttComment, null, nullptr, comment); //Комментарий (*....*)
				}
			}
		}
		case ')':
			cur = GetNextCh();
			return new CToken(ttOper, closeParSy);



		case '{': {
			std::string comment = "{";

			while (cur != '}') {

				cur = GetNextCh();
				comment += cur;
			}
			return new CToken(ttComment, null, nullptr, comment); //Многострочный комментарий {..}
		}

		case '[':
			cur = GetNextCh();
			return new CToken(ttOper, openIndSy);
		case ']':
			cur = GetNextCh();
			return new CToken(ttOper, closeIndSy);
		case '&':
			cur = GetNextCh();
			return new CToken(ttOper, ellipsisSy);
		}

		//Считывание числовой константы
		if (IsDigit(cur)) {
			double number = 0;
			while (IsDigit(cur)) {
				number = number * 10 + (cur - '0');
				cur = GetNextCh();
			}
			if (cur != '.') return new CToken(ttConst, null, new CIntVariant(int(number))); //константа типа int
			cur = GetNextCh();
			if (cur == '.') {
				cur = '&';
				return new CToken(ttConst, null, new CIntVariant(int(number)));
				
			}
			int count = 0;

			while (IsDigit(cur)) {
				number = number * 10 + (cur - '0');
				count++;
				cur = GetNextCh();
			}
			number /= pow(10, count);
			return new CToken(ttConst, null, new CDoubleVariant(number)); //константа типа double

		}
		return nullptr;
	}


	~CIO() {
		fin.close();
	}


};





int main() {
	CIO* io = new CIO("test.pas");
	CToken* cur = nullptr;
	do {
		cur = io->GetNextToken();
		cur->Print();
	} while (cur != nullptr);


	delete io;
	delete cur;
}
