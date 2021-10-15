#include "CIO.h"
#include "CToken.h"
#include "CVariant.h"



//��������� ������� �� �����
char CIO::GetNextCh() {
	char ch;
	fin.get(ch);
	while (DeleteComment(ch));
	if (fin.eof()) return NULL;
	return ch;
}

//�������� �����������
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

//�������� �� �����
bool CIO::IsLetter(char cur) {
	return cur >= 'a' && cur <= 'z' || cur >= 'A' && cur <= 'Z';
}

//�������� �� �����
bool CIO::IsDigit(char cur) {
	return cur >= '0' && cur <= '9';
}

CIO::CIO(std::string path) {
	fin.open(path);
}

//��������� �������� ���������
CToken* CIO::GetDigitConst(int sgn) {
	double number = 0;
	while (IsDigit(cur)) {
		number = number * 10 + (cur - '0');
		cur = GetNextCh();
	}
	if (cur != '.') return new CToken(ttConst,  new CIntVariant(int(number * sgn)), std::to_string(int(number* sgn))); //��������� ���� int
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
	return new CToken(ttConst, new CDoubleVariant(number * sgn), std::to_string(number * sgn)); //��������� ���� double
}
//��������� �����
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

//��������� ���������� ������
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
			return new CToken(ttOper, assignmentSy, ident);    //�������� ������������
		}
		return new CToken(ttOper, descriptionOfTypesSy, ident);  //�������� ����������� ���� ����������
		break;

	case '<':
		ident = cur;
		cur = GetNextCh();
		if (cur == '>') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, notEqualSy, ident); //�������� �� �����
		}
		if (cur == '=') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, lessEqualSy, ident); //�������� ������ ��� �����
		}
		return new CToken(ttOper, lessSy, ident); //�������� ������

	case '>':
		ident = cur;
		cur = GetNextCh();
		if (cur == '=') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, moreEqualSy, ident); //�������� ������ ��� �����
		}
		return new CToken(ttOper, moreSy, ident); //�������� ������

	case ';':
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, semicolonSy, ident); //�������� ����������

	case '.':
		ident = cur;
		cur = GetNextCh();
		if (cur == '.') {
			ident += cur;
			cur = GetNextCh();
			return new CToken(ttOper, ellipsisSy, ident); //�������� ������������
		}
		return new CToken(ttOper, pointSy, ident); //�������� �����

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
		return new CToken(ttConst, new CStringVariant(stringConst), stringConst); //��������� ���������
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
		return new CToken(ttOper, divisionSy, ident); //�������
	}

	case '(': {
		ident = cur;
		cur = GetNextCh();
		return new CToken(ttOper, openParSy, ident);

	}
	}

	//���������� �������� ���������
	if (IsDigit(cur)) 
		return GetDigitConst(1);

	//�������� ��������� ����� ��� ���������� 
	if (IsLetter(cur)) 
		return GetWord();

	return nullptr;
}


CIO::~CIO() {
	fin.close();
}