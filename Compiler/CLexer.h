#pragma once

#include "CIO.h"
#include "CToken.h"
#include<map>
#include<set>
#include<string>

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
														{ "begin",beginsy },
														{ "while",whilesy },
														{ "array",arraysy },
														{ "const",constsy },
														{ "label",labelsy },
														{ "until",untilsy },
														{ "downto",downtosy },
														{ "packed",packedsy },
														{ "record",recordsy },
														{ "repeat",repeatsy },
														{ "length",lengthsy },
														{ "writeln",writelnsy },
														{ "readln",readlnsy },
														{ "copy",copysy },
														{ "program",programsy },
														{ "function",fuctionsy },
														{ "procedure",proceduresy },

	};

	//Ключевые слова
	std::set<std::string> keyWords = { "if","do","of","or","in","to",
									"end","var", "div", "and", "not", "for", "mod","set",
									"then","else", "case", "file", "goto", "type", "with",
									"begin","while", "array", "const", "label", "until",
									"downto","packed", "record", "repeat","length","writeln","readln","copy",
									"program","fuction","procedure" };

	//Проверка на букву
	bool IsLetter(char cur);

	//Проверка на цифру
	bool IsDigit(char cur);

	//Проверка слова
	CToken* GetWord();

	//Провекра числовой константы
	CToken* GetDigitConst();

	//Менеджер ошибок
	ErrorManager* errManager;

	//Неверный идентификатор
	CToken* IncorrectIdent(std::string ident);


	//Проверка на переполнение
	bool CheckIntConst(int val);

	bool CheckDoubleConst(double val);

public:
	CLexer(CIO* io, ErrorManager* _errManager);
	CToken* GetNextToken();
	~CLexer();
};

