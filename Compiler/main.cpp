#include<string>
#include<fstream>
#include<iostream>
#include <cctype> 


// ��� ������
enum TokenType {
	ttKeyWord,
	ttIdent,
	ttConst,
	ttOper,
	ttComment
};


//�������� �����
enum KeyWords {
	being,
	var,
	end
};

//�������� 
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

	//��������� ������� �� �����
	char GetNextCh() {
		char ch;
		fin.get(ch);
		if (fin.eof()) return NULL;
		return ch;
	}

	//�������� �� �����
	bool IsLetter(char cur) {
		return cur>='a'&&cur<='z'||cur>='A'&&cur<='Z';
	}

	

public:

	CIO(std::string path) {
		fin.open(path);
	}

	//��������� ���������� ������
	CToken* GetNextToken() {
		if (cur == -1) cur = GetNextCh();
		while (cur == ' '||cur=='\n') cur = GetNextCh();

		switch (cur) 
		{	
		case ':':
			cur = GetNextCh();
			if (cur == '=') {	
				cur = GetNextCh();
				return new CToken(ttOper, assignmentSy);    //�������� ������������
			}
			return new CToken(ttOper, descriptionOfTypesSy);  //�������� ����������� ���� ����������
			break;

		case '<':

			cur = GetNextCh();
			if (cur == '>') {
				cur = GetNextCh();
				return new CToken(ttOper, notEqualSy); //�������� �� �����
			}
			if (cur == '=') {
				cur = GetNextCh();
				return new CToken(ttOper, lessEqualSy); //�������� ������ ��� �����
			}
			return new CToken(ttOper, lessSy); //�������� ������

		case '>':
			cur = GetNextCh();
			if (cur == '=') {
				cur = GetNextCh();
				return new CToken(ttOper, moreEqualSy); //�������� ������ ��� �����
			}
			return new CToken(ttOper, moreSy); //�������� ������

		case ';':
			cur = GetNextCh();
			return new CToken(ttOper, semicolonSy); //�������� ����������

		case '.':
			cur = GetNextCh();
			if (cur == '.') {
				cur = GetNextCh();
				return new CToken(ttOper, ellipsisSy); //�������� ������������
			}
			return new CToken(ttOper, pointSy); //�������� �����

		
		case '\'': {
			std::string stringConst = "'";
			do {
				cur = GetNextCh();
				stringConst += cur;
			} while (cur != '\'');
			cur = GetNextCh();
			return new CToken(ttConst, null, new CStringVariant(stringConst)); //��������� ���������
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
			if (cur != '/') return new CToken(ttOper, divisionSy); //�������
			std::string comment = "//";
			cur = GetNextCh();
			while (cur != '\n' && cur != '\0') {
				comment += cur;
				cur = GetNextCh();
			}
			cur = GetNextCh();
			return new CToken(ttComment, null, nullptr, comment); //������������ �����������
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
					return new CToken(ttComment, null, nullptr, comment); //����������� (*....*)
				}
			}
		}
		case '{': {
			std::string comment = "{";

			while (cur != '}') {
				
				cur = GetNextCh();
				comment += cur;
			}
			return new CToken(ttComment, null, nullptr, comment); //������������� ����������� {..}
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