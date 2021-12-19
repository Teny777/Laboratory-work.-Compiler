﻿#include "pch.h"
#include "CVariant.h"
#include"CToken.h"
#include<string>



// Константа типа int
CIntVariant::CIntVariant(int _val) {
	value = _val;
}

std::string CIntVariant::GetClassType() {
	return "integer";
}


int CIntVariant::GetValue() {
	return value;
}


// Константа типа double
CDoubleVariant::CDoubleVariant(double _val) {
	value = _val;
}

std::string CDoubleVariant::GetClassType() {
	return "double";
}


double CDoubleVariant::GetValue() {
	return value;
}


// Константа типа string
CStringVariant::CStringVariant(std::string _val) {
	value = _val;
}

std::string CStringVariant::GetClassType() {
	return "string";
}

std::string CStringVariant::GetValue() {
	return value;
}