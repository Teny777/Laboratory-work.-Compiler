#include"CIO.h"
#include"CLexer.h"
#include "CToken.h"
#include "ErrorManager.h"
#include "Error.h"
#include "Syntax.h"
int main() {

	ErrorManager* errManager = new ErrorManager();
	CIO* io = new CIO("test.pas");
	CLexer* lex = new CLexer(io, errManager);
	Syntax* syn = new Syntax(lex, errManager);
	syn->CheckProgram();

	io->PrintError(errManager);
}