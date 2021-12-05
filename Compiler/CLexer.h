#pragma once
#include "CIO.h"
#include "CToken.h"
#include "ErrorManager.h"
#include<map>
#include<set>

class CLexer {
private:
	char curLiter = -1;
	CIO* IO;
	std::map<std::string, OperationSymbols> GetOperKeySy = { { "if",ifsy },
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

	//Ключевые слова
	std::set<std::string> keyWords = { "if","do","of","or","in","to",
									"end","var", "div", "and", "not", "for", "mod","set",
									"then","else", "case", "file", "goto", "type", "with","char","real",
									"begin","while", "array", "const", "label", "until","double","string",
									"downto","packed", "record", "repeat","boolean","length","writeln","readln","copy",
									"program","fuction","procedure","integer", "longint" };

	//Проверка на букву
	bool IsLetter(char cur);

	//Проверка на цифру
	bool IsDigit(char cur);

	//Пролучение слова
	CToken* GetWord();

	//Получение константы
	CToken* GetDigitConst();

	//Менеджер ошибок
	ErrorManager* errManager;

	bool CheckIntConst(int val);

	bool CheckDoubleConst(double val);

public:
	CLexer(CIO* _IO, ErrorManager* _errManager);
	CToken* GetNextToken();
	~CLexer();
};

