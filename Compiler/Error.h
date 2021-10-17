#pragma once
#include<string>
#include<map>

//���� ������
enum ErrorCode {
	constantOverflow = 1,
	invalidCharacter,
	invalidToken
};

// ������� ������
struct Position {
	int row, column;
	Position(int _row, int _column);
	Position();
};


//������
class Error {
protected:
	Position pos;
	ErrorCode code;
	virtual std::string GetErrorType() = 0;
	Error(Position _pos, ErrorCode _code);
public:
	// ����������� ������
	std::map<ErrorCode, std::string> DecryptionOfError = { {constantOverflow,"Constant overflow"},
															{invalidCharacter,"Invalid character entered"},
															{invalidToken,"Incorrect variable has been entered"}};
	Position GetPosition();
	ErrorCode GetErrorCode();

};


//����������� ������
class LexError: public Error {
public:
	LexError(Position _pos, ErrorCode _code);

	std::string GetErrorType();

};