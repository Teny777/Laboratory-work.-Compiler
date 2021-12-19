#pragma once

#include<deque>
#include<string>
#include <queue>
#include <functional>
#include "Error.h"


class ErrorManager {
private:

	std::deque <Error*> errors;

public:
	//Добавление ошибки
	void AddError(ErrorCode errCode, position pos); 
	//Получение ошибки
	Error* GetError();
	//Получение количества ошибок
	int CountErrors();
	//Сортировка ошибок по позиции
	void SortError();

	~ErrorManager();
};

