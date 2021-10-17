#include "Error.h"


//����������� ������
Error::Error(Position _pos, ErrorCode _code) {
	pos = _pos;
	code = _code;
}

//����������� ������
LexError::LexError(Position _pos, ErrorCode _code) :Error(_pos, _code) {
}

//��������� ���� ������
std::string LexError::GetErrorType() {
	return "Lexical error";
}


//����������� �������
Position::Position(int _row, int _column) {
	row = _row;
	column = _column;
}

//����������� �� ���������
Position::Position() {

}

//��������� �������
Position Error::GetPosition() {
	return pos;
}

//��������� ���� ������
ErrorCode Error::GetErrorCode() {
	return code;
}
