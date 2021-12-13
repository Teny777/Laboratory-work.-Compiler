#pragma once

#include<deque>
#include<string>
#include <queue>
#include <functional>
#include "Error.h"


class ErrorManager {
private:
	
	std::deque <Error*> errors;
	std::map<position, bool> positionError; // ������ � �������
public:
	void AddError(ErrorCode errCode, position pos);
	Error* GetError();
	void SortError();
	
};

