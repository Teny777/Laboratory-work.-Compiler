#pragma once

enum EType {
	et_integer,
	et_string,
	et_double,
	et_bool
};


class CType {
public:
	virtual bool  isDerivedTo(CType* b) = 0;
	EType type;
};

//int
class CIntType :public CType {
public:
	bool  isDerivedTo(CType* b) override;
	CIntType(EType _type);
};

//double
class CDoubleType :public CType {
public:
	bool  isDerivedTo(CType* b) override;
	CDoubleType(EType _type);
};

//string
class CStringType :public CType {
public:
	bool  isDerivedTo(CType* b) override;
	CStringType(EType _type);
};

//bool
class CBoolType :public CType {
public:
	bool  isDerivedTo(CType* b) override;
	CBoolType(EType _type);
};