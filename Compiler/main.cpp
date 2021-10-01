#include<string>
#include<fstream>
#include<iostream>
#include <cctype> 


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
	openingParSy
};

class CVariant {
public:

};

class CIntVariant : public CVariant {
private:
	int value;

public:
	CIntVariant(int _val) {
		value = _val;
	}
};

class CDoubleVariant : public CVariant {
private:
	double value;
public:
	CDoubleVariant(double _val) {
		value = _val;
	}
};


class CStringVariant : public CVariant {
private:
	std::string value;
public:
	CStringVariant(std::string _val) {
		value = _val;
	}
};


class CToken {
private:
	TokenType tt;
	OperationSymbols op;
	CVariant* constVal;
	std::string comment;

public:

	CToken(TokenType _tt, OperationSymbols _op, CVariant* _constVal=nullptr ,std::string _com="") {
		tt = _tt;
		op = _op;
		constVal = _constVal;
		comment = _com;
	}

};

class CIO {
private:
	std::ifstream fin;
	char cur=-1;

	//Получение символа из файла
	char GetNextCh() {
		char ch;
		fin.get(ch);
		if (fin.eof()) return NULL;
		return ch;
	}

	//Проверка на букву
	bool IsLetter(char cur) {
		return cur>='a'&&cur<='z'||cur>='A'&&cur<='Z';
	}

	

public:

	CIO(std::string path) {
		fin.open(path);
	}

	//Получение следующего токена
	CToken* GetNextToken() {
		if (cur == -1) cur = GetNextCh();
		while (cur == ' '||cur=='\n') cur = GetNextCh();

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
			if (cur != '*') return new CToken(ttOper, openingParSy);
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
		case '{': {
			std::string comment = "{";

			while (cur != '}') {
				
				cur = GetNextCh();
				comment += cur;
			}
			return new CToken(ttComment, null, nullptr, comment); //Многострочный комментарий {..}
		}
			

		}

		cur = GetNextCh();
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
		std::cout << cur << '\n';
	} while (true);


	delete io;
	delete cur;
}