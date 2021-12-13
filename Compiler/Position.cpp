#include "Position.h"

bool position::operator<(const position& pos) const {
	return (lineNumber == pos.lineNumber) ? charNumber < pos.charNumber : lineNumber < pos.lineNumber;
}

bool position :: operator>(const position& pos) const {
	return (lineNumber == pos.lineNumber) ? charNumber > pos.charNumber : lineNumber > pos.lineNumber;
}

bool position :: operator<=(const position& pos) const {
	return *this < pos || *this == pos;
}

bool position :: operator>=(const position& pos) const {
	return *this > pos || *this == pos;
}

bool position :: operator==(const position& pos) const {
	return lineNumber == pos.lineNumber&& charNumber == pos.charNumber;
}

bool position :: operator!=(const position& pos) const {
	return !(*this == pos);
}