#pragma once
#include<string>
#include<map>

//Коды ошибок
enum ErrorCode {
	constantOverflow = 1,
	invalidCharacter,
	invalidToken
};

// Позиция ошибки
struct Position {
	int row, column;
	Position(int _row, int _column);
	Position();
};


//Ошибки
class Error {
protected:
	Position pos;
	ErrorCode code;
	virtual std::string GetErrorType() = 0;
	Error(Position _pos, ErrorCode _code);
public:
	// Расшифровка ошибок
	std::map<ErrorCode, std::string> DecryptionOfError = { {constantOverflow,"Constant overflow"},
															{invalidCharacter,"Invalid character entered"},
															{invalidToken,"Incorrect variable has been entered"}};
	Position GetPosition();
	ErrorCode GetErrorCode();

};


//Лексические ошибки
class LexError: public Error {
public:
	LexError(Position _pos, ErrorCode _code);

	std::string GetErrorType();

};