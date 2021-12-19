#pragma once
#include "CCompiler.h"
#include "CIO.h"
#include "ErrorManager.h"


class CCompilerMSIL {
private:
	CCompiler* compiler;
	ErrorManager* errManager;
public:
	CCompilerMSIL(CIO* _io,ErrorManager* _errManager);
	void CompileMSIL();

	~CCompilerMSIL();
};