#include "Error.h"

Error::Error(position _pos, ErrorCode _code) {
	pos = _pos;
	code = _code;
}


position Error::GetPosition() {
	return pos;
}


ErrorCode Error::GetErrorCode() {
	return code;
}


std::string Error::GetDecryptionOfError() {
	return DecryptionOfError[code];
}



bool Error::operator<(const Error& err) const {
	return pos<err.pos;
}
bool  Error :: operator>(const Error& err) const {
	return pos > err.pos;
}
bool  Error :: operator ==(const Error& err) const {
	return pos==err.pos;
}

bool  Error :: operator<=(const Error& err) const {
	return pos<=err.pos;
}
bool  Error :: operator>=(const Error& err) const {
	return  pos >= err.pos;
}
bool Error :: operator !=(const Error& err) const {
	return  pos != err.pos;
}