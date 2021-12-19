#include "pch.h"
#include"CIO.h"
#include"CLexer.h"
#include "CToken.h"
#include "ErrorManager.h"
#include "Error.h"
#include "CCompiler.h"
#include "GeneratorMSIL.h"
#include<iostream>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Reflection::Emit;



int main(array<String ^> ^args)
{
	ErrorManager* errManager = new ErrorManager();
	CIO* io = new CIO("test.pas");

	CCompilerMSIL* compiler = new CCompilerMSIL(io, errManager);

	compiler->CompileMSIL();
	io->PrintError(errManager);	 




    return 0;
}
