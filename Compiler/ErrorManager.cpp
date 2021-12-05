#include "ErrorManager.h"

void ErrorManager::AddError(std::string ident, ErrorCode errCode, position pos) {
	errors.push_back(new Error(pos, errCode, ident));
}


Error* ErrorManager::GetError() {
	Error* curError;
	if (!errors.size()) return nullptr;
	curError = errors.front();
	errors.pop_front();
	return curError;
}