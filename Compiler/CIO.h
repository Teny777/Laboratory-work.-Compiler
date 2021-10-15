#pragma once
#include<fstream>
#include<string>
#include<set>
#include "CToken.h"


class CIO {
private:
	std::ifstream fin;
	char cur = -1;
	int ind=0;

	//Ключевые слова
	std::set<std::string> keyWords = {"if","do","of","or","in","to",
										"end","var", "div", "and", "not", "for", "mod","set",
										"then","else", "case", "file", "goto", "type", "with","char","real",
										"begin","while", "array", "const", "label", "until","double","string",
										"downto","packed", "record", "repeat","boolean","length","writeln","readln","copy",
										"program","fuction","procedure","integer", "longint"};
	std::map<std::string, OperationSymbols> GetOperSy = {{ "if",ifsy },
														{ "do",dosy },
														{ "of",ofsy },
														{ "or",orsy },
														{ "in",insy },
														{ "to",tosy },
														{ "end",endsy },
														{ "var",varsy },
														{ "div",divsy },
														{ "and",andsy },
														{ "not",notsy },
														{ "for",forsy },
														{ "mod",modsy },
														{ "set",setsy },
														{ "then",thensy },
														{ "else",elsesy },
														{ "case",casesy },
														{ "file",filesy },
														{ "goto",gotosy },
														{ "type",typesy },
														{ "with",withsy },
														{ "char",charsy },
														{ "real",realsy },
														{ "begin",beginsy },
														{ "while",whilesy },
														{ "array",arraysy },
														{ "const",constsy },
														{ "label",labelsy },
														{ "until",untilsy },
														{ "double",doublesy },
														{ "string",stringsy },
														{ "downto",downtosy },
														{ "packed",packedsy },
														{ "record",recordsy },
														{ "repeat",repeatsy },
														{ "boolean",booleansy },
														{ "length",lengthsy },
														{ "writeln",writelnsy },
														{ "readln",readlnsy },
														{ "copy",copysy },
														{ "program",programsy },
														{ "function",fuctionsy },
														{ "procedure",proceduresy },
														{ "integer",integersy },
														{ "longint",longintsy }
													};



	//Получение символа из файла
	char GetNextCh();

	//Проверка на букву
	bool IsLetter(char cur);

	//Проверка на число
	bool IsDigit(char cur);

	//Удаление комментария
	bool DeleteComment(char &ch);

	//Получение числовой константы
	CToken* GetDigitConst(int sgn);

	//Получение слова
	CToken* GetWord();


public:

	CIO(std::string path);

	//Получение следующего токена
	CToken* GetNextToken();

	~CIO();
};
