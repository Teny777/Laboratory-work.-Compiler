#include "ErrorManager.h"
#include<algorithm>
void ErrorManager::AddError( ErrorCode errCode, position pos) {
	if (!positionError[pos]) {
		errors.push_back(new Error(pos, errCode));
		positionError[pos] = true;
	}
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
	sort(errors.begin(), errors.end(),cmp);
}