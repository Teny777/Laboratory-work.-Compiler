#pragma once

#include<deque>
#include<string>
#include "CIO.h"
#include "Error.h"

class ErrorManager {
private:
	std::deque<Error*> errors;
public:
	void AddError(std::string ident, ErrorCode errCode, position pos);

	Error* GetError();
};