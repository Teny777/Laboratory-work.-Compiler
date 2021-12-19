#pragma once
#include<string>
#include<fstream>
#include<vector>
#include "ErrorManager.h"


class CIO {

private:

	std::ifstream fin;

	position pos;

	std::vector<std::string> programText;

public:
	//Получение следующей литеры
	char GetNextCh();

	CIO(std::string path);

	//Получение текущей позиции
	position GetPosition();

	//Получение предыдущей позиции
	position GetPrevPosition();


	//Вывод ошибок
	void PrintError(ErrorManager* errManager);

	~CIO();
};