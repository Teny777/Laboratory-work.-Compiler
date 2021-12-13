#include "CType.h"




bool  CIntType::isDerivedTo(CType* b) {
	return b!=nullptr&&(this == b || b->type == et_double);
}

bool  CBoolType::isDerivedTo(CType* b) {
	return b != nullptr &&this == b;
}

bool  CStringType::isDerivedTo(CType* b) {
	return b != nullptr && this == b;
}

bool  CDoubleType::isDerivedTo(CType* b) {
	return b != nullptr && this == b;
}

CIntType::CIntType(EType _type) {
	type = _type;
}
CBoolType::CBoolType(EType _type) {
	type = _type;
}
CStringType::CStringType(EType _type) {
	type = _type;
}
CDoubleType::CDoubleType(EType _type) {
	type = _type;
}