#include"CIO.h"
#include<iostream>

CIO::CIO(std::string path) {
	fin.open(path);
	line = "";
	pos.lineNumber = 1;
	pos.charNumber = 0;
	programText.push_back("");
}

//Получение следующей литеры
char CIO::GetNextCh() {
	char ch;
	fin.get(ch);
	if (ch == '\n'|| fin.eof()) {
		programText[pos.lineNumber-1] = line;
		programText.push_back("");
		line = "";
		pos.lineNumber++;
		pos.charNumber = 0;
	}
	else pos.charNumber++, line += ch;
	if (fin.eof()) 
		return NULL;



	return ch;

}
CIO::~CIO() {
	fin.close();
}

//Получение позиции
position CIO::GetPosition() {
	return pos;
}

position CIO::GetPrevPosition() {
	position prevPos = pos;;
	if (pos.charNumber == 0) {
		prevPos.lineNumber--;
		prevPos.charNumber = programText[pos.lineNumber - 2].size();
	}
	else {
		prevPos.charNumber--;
	}
	return prevPos;
}

//Вывод ошибок
void CIO::PrintError(ErrorManager* errManager) {

	setlocale(LC_ALL, "Russian");
	int count = 1;
	errManager->SortError();
	Error* curError = errManager->GetError();
	for (int i = 0; i < programText.size(); ++i) {
		std::cout << programText[i] << std::endl;
		for (int j = 0; j < programText[i].size(); ++j) {

			if (curError != nullptr && curError->GetPosition().lineNumber == i + 1 && curError->GetPosition().charNumber == j + 1) {
				for (int z = 0; z < j; ++z) std::cout << ' ';
				std::cout << "^ " << "Error code=" << curError->GetErrorCode() << std::endl;
				std::cout << "ERROR *" << count << "*"  << std::endl;
				std::cout <<"Discription: " << curError->GetDecryptionOfError() << std::endl;
				curError = errManager->GetError();
				count++;
			}
			
		}
	}
}