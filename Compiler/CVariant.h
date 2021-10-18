#pragma once
#include<string>

class CVariant {
public:
	virtual std::string GetClassType() = 0;
};

// ��������� int
class CIntVariant : public CVariant { 
private:
	int value;

public:
	CIntVariant(int _val);
	std::string GetClassType() override;
	int GetValue();

};

// ��������� double
class CDoubleVariant : public CVariant { 
private:
	double value;
public:

	CDoubleVariant(double _val);
	std::string GetClassType() override;
	double GetValue();


};

// ��������� string
class CStringVariant : public CVariant { 
private:
	std::string value;
public:

	CStringVariant(std::string _val);
	std::string GetClassType() override;
	std::string GetValue();


};