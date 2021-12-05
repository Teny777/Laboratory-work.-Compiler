#include"CIO.h"
#include<iostream>

CIO::CIO(std::string path) {
	fin.open(path);
	line = prevline = "";
	pos.lineNumber = 1;
	pos.charNumber = 0;
}

//Получение следующей литеры
char CIO::GetNextCh() {
	char ch;
	fin.get(ch);
	if (ch == '\n') {
		prevline = line;
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
	if (pos.charNumber == 1) {
		prevPos.lineNumber--;
		prevPos.charNumber = prevline.size();
	}
	else {
		prevPos.charNumber++;
	}
	return prevPos;
}

//Вывод ошибок
void CIO::PrintError(ErrorManager* errManager) {
	Error* curError = errManager->GetError();
	int count = 1;
	while (curError != nullptr) {
		position pos = curError->GetPosition();
		std::cout << "ERROR *" << count << "* -> " << curError->GetIdent() << std::endl;
		std::cout<<	"Position: line=" << pos.lineNumber << " char number=" << pos.charNumber << std::endl;
		std::cout << "Error code=" << curError->GetErrorCode() << ", Discription: " << curError->GetDecryptionOfError() << std::endl;
		curError = errManager->GetError();
		count++;
	}
}