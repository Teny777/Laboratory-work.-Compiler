#pragma once
#include<fstream>
#include<string>
#include<set>
#include "CToken.h"


class CIO {
private:
	std::ifstream fin;
	char cur = -1;

	//�������� �����
	std::set<std::string> keyWords = {"if","do","of","or","in","to",
										"end","var", "div", "and", "not", "for", "mod", "nil", "set",
										"then","else", "case", "file", "goto", "type", "with","char","real",
										"begin","while", "array", "const", "label", "until","double","string",
										"downto","packed", "record", "repeat","boolean","length","writeln","readln","copy",
										"program","fuction","procedure","integer", "longint"};

	//����������
	std::set<std::string> variable;

	//��������� ������� �� �����
	char GetNextCh();

	//�������� �� �����
	bool IsLetter(char cur);

	//�������� �� �����
	bool IsDigit(char cur);


public:

	CIO(std::string path);

	//��������� ���������� ������
	CToken* GetNextToken();

	~CIO();
};
