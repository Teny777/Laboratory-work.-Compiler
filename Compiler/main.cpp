#include<string>
#include<fstream>
#include<iostream>
#include<map>
#include<set>
#include "CIO.h"
#include "CToken.h"



int main() {
	CIO* io = new CIO("test.pas");
	CToken* cur = nullptr;
	do {
		cur = io->GetNextToken();
		cur->Print();
	} while (cur != nullptr);

	delete io;
	delete cur;
}
