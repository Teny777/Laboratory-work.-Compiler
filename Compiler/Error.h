#pragma once
#include<string>
#include <map>
#include "Position.h"

enum ErrorCode {
	constantOverflow = 1,
	invalidCharacter,
	invalidIdent,
	invalidType,
	repeatVariable,
	incompatibleTypes,
	undeclaredIdent,
	expressionBool
};


class Error {
private:
	
	ErrorCode code;
	position pos;
	std::map<ErrorCode, std::string> DecryptionOfError = { {constantOverflow,"Переполнение константы"},
															{invalidCharacter,"Неверный символ"},
															{invalidIdent, "Неверный идентификатор" },
															{invalidType, "Неверный тип" },
															{repeatVariable, "Переменная описана повторно" },
	                                                        {incompatibleTypes, "Несовместимые типы" },
															{undeclaredIdent, "Необъявленный идентификатор" },
															{expressionBool, "Выражение должно иметь тип boolean" } };


public:
	Error(position _pos, ErrorCode _code);
	
	position GetPosition();
	ErrorCode GetErrorCode();
	std::string GetDecryptionOfError();


	bool operator<(const Error&) const;

	bool operator>(const Error&) const;

	bool operator<=(const Error&) const;

	bool operator>=(const Error&) const;

	bool operator==(const Error&) const;

	bool operator!=(const Error&) const;
};
