#include "Error.h"


//Конструктор ошибки
Error::Error(Position _pos, ErrorCode _code) {
	pos = _pos;
	code = _code;
}

//Лексические ошибки
LexError::LexError(Position _pos, ErrorCode _code) :Error(_pos, _code) {
}

//Получение типа ошибки
std::string LexError::GetErrorType() {
	return "Lexical error";
}


//Конструктор позиции
Position::Position(int _row, int _column) {
	row = _row;
	column = _column;
}

//Конструктор по умолчанию
Position::Position() {

}

//Получение позиции
Position Error::GetPosition() {
	return pos;
}

//Получение кода ошибки
ErrorCode Error::GetErrorCode() {
	return code;
}
