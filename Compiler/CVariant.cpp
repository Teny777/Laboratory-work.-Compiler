#include "CVariant.h"
#include<string>


// Константа int
CIntVariant::CIntVariant(int _val) {
	value = _val;
}

std::string CIntVariant::GetClassType(){
	return "IntConst";
}


int CIntVariant::GetValue() {
	return value;
}



// Константа double
CDoubleVariant::CDoubleVariant(double _val) {
	value = _val;
}

std::string CDoubleVariant::GetClassType() {
	return "DoubleConst";
}


double CDoubleVariant::GetValue() {
	return value;
}



// Константа string
CStringVariant::CStringVariant(std::string _val) {
	value = _val;
}

std::string CStringVariant::GetClassType() {
	return "StringConst";
}

std::string CStringVariant::GetValue() {
	return value;
}

