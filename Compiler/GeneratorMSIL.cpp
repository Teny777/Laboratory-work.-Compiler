#include "pch.h"
#include "GeneratorMSIL.h"
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Reflection::Emit;

CCompilerMSIL::CCompilerMSIL(CIO* _io, ErrorManager* _errManager) {
	compiler = new CCompiler(_io, _errManager);
	errManager = _errManager;
}

void CCompilerMSIL::CompileMSIL() {

	String^ assemblyName = "MyProgram";
	String^ modName = "MyProgram.exe";
	String^ typeName = "MyProgram";
	String^ methodName = "Main";

	//Уникальный идентификатор сборки
	AssemblyName^ name = gcnew AssemblyName(assemblyName);

	//Домен приложения
	AppDomain^ domain = Threading::Thread::GetDomain();

	//Определяет и представляет динамическую сборку
	AssemblyBuilder^ builder = domain->DefineDynamicAssembly(name, AssemblyBuilderAccess::RunAndSave);

	//Определяет и представляет модуль в динамической сборке
	ModuleBuilder^ module = builder->DefineDynamicModule(modName, true);

	//Определяет и создает новые экземпляры классов во время выполнения
	TypeBuilder^ typeBuilder = module->DefineType(typeName, TypeAttributes::Public);

	//Определяет и представляет метод для динамического класса
	MethodBuilder^ methodBuilder = typeBuilder->DefineMethod(methodName, MethodAttributes::Static
		| MethodAttributes::Public, void::typeid, gcnew array<Type^>{});

	ILGenerator^ ilGenerator = methodBuilder->GetILGenerator();



	compiler->CheckProgram(ilGenerator);

	//Если есть ошибки, то завершаем компиляцию
	if (errManager->CountErrors() > 0) return;

	ilGenerator->Emit(OpCodes::Ret);


	builder->SetEntryPoint(methodBuilder);

	Type^ myClass = typeBuilder->CreateType();
	//Сохраняем в *.exe
	builder->Save(modName);
}


CCompilerMSIL::~CCompilerMSIL() {
	delete compiler;
	delete errManager;
}