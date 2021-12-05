#pragma once
#include<string>
#include<fstream>
#include "Position.h"
#include "ErrorManager.h"
class ErrorManager;

class CIO {

private:
	std::ifstream fin;
	position pos;
	std::string line,prevline;
	
public:
	//Получение следующей литеры
	char GetNextCh();

	CIO(std::string path);

	position GetPosition();

	position GetPrevPosition();

	void PrintError(ErrorManager* errManager);

	~CIO();
};