#pragma once
#include<string>
#include <map>
#include "Position.h"

enum ErrorCode {
	constantOverflow = 1,
	invalidCharacter
};


class Error {
private:
	position pos;
	ErrorCode code;
	std::string ident;
	std::map<ErrorCode, std::string> DecryptionOfError = { {constantOverflow,"Constant overflow"},
															{invalidCharacter,"Invalid character entered"} };
public:
	Error(position _pos, ErrorCode _code,std::string _ident);
	
	position GetPosition();
	ErrorCode GetErrorCode();
	std::string GetDecryptionOfError();
	std::string GetIdent();

};