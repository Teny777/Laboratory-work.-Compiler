#pragma once
#include<string>
#include<fstream>
#include<vector>
#include "ErrorManager.h"


class CIO {

private:
	std::ifstream fin;
	position pos;
	std::string line;
	std::vector<std::string> programText;
	
public:
	//Получение следующей литеры
	char GetNextCh();

	CIO(std::string path);

	position GetPosition();

	position GetPrevPosition();

	void PrintError(ErrorManager* errManager);

	~CIO();
};