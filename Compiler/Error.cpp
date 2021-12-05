#include "Error.h"

Error::Error(position _pos, ErrorCode _code,std::string _ident) {
	pos = _pos;
	code = _code;
	ident = _ident;
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

std::string Error::GetIdent() {
	return ident;
}