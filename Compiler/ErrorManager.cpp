#include "pch.h"
#include "ErrorManager.h"
#include<algorithm>


void ErrorManager::AddError(ErrorCode errCode, position pos) {
		errors.push_back(new Error(pos, errCode));
}


Error* ErrorManager::GetError() {
	Error* curError;
	if (!errors.size()) return nullptr;
	curError = errors.front();
	errors.pop_front();
	return curError;
}

void ErrorManager::SortError() {
	auto cmp = [](Error* a, Error* b) {return *a < *b; };
	sort(errors.begin(), errors.end(), cmp);
}


int ErrorManager::CountErrors() {
	return errors.size();
}


ErrorManager::~ErrorManager() {
	for (int i = 0; i < errors.size(); ++i)
		delete errors[i];
}