#include"CIO.h"
#include"CLexer.h"
#include "CToken.h"
#include "ErrorManager.h"
#include "Error.h"
#include "CCompiler.h"
int main() {

	ErrorManager* errManager = new ErrorManager();
	CIO* io = new CIO("test.pas");
	CLexer* lex = new CLexer(io, errManager);
	CCompiler* compiler = new CCompiler(lex, errManager);
	compiler->CheckProgram();
	
	io->PrintError(errManager);
}