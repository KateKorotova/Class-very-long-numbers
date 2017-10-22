#pragma once
#include <string>
#include <vector>
#include <iostream>


using namespace std; 


static const int base = 100;
static const int base_pow = 2;


class VeryLongInt {
private:
	int sign;
	vector <long long> digits;
	VeryLongInt add_module(const VeryLongInt& b)const;
	VeryLongInt sub_module(const VeryLongInt& b)const;
	int cmp_module(const VeryLongInt& b);

public:
	VeryLongInt();
	VeryLongInt operator -()const;
	VeryLongInt operator +(const VeryLongInt& b);
	VeryLongInt operator -(const VeryLongInt& b);
	VeryLongInt operator *(const VeryLongInt& b);
	VeryLongInt operator /(const VeryLongInt& b);
	bool operator >(const VeryLongInt& b);
	bool operator <(const VeryLongInt& b);
	bool operator <=(const VeryLongInt& b);
	bool operator >=(const VeryLongInt& b);
	bool operator !=(const VeryLongInt& b);
	bool operator ==(const VeryLongInt& b);

	friend istream& operator >> (istream& os, VeryLongInt& num);
	friend ostream& operator<< (ostream& os, const VeryLongInt& num);
};

