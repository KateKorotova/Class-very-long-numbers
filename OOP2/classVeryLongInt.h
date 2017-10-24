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
	VeryLongInt normalize();
	VeryLongInt expansion(long long size);
	VeryLongInt rshift(long long size);

public:
	VeryLongInt();
	VeryLongInt(long long n);
	VeryLongInt operator -()const;

	VeryLongInt operator +(const VeryLongInt& b);
	VeryLongInt operator -(const VeryLongInt& b);
	VeryLongInt operator *(const VeryLongInt& b)const;
	VeryLongInt operator /(const VeryLongInt& b); 
	VeryLongInt operator /(long long num); 
	bool operator >(const VeryLongInt& b);
	bool operator <(const VeryLongInt& b);
	bool operator <=(const VeryLongInt& b);
	bool operator >=(const VeryLongInt& b);
	bool operator !=(const VeryLongInt& b);
	bool operator ==(const VeryLongInt& b);

	friend istream& operator >> (istream& os, VeryLongInt& num);
	friend ostream& operator<< (ostream& os, const VeryLongInt& num);

	friend VeryLongInt karatsuba_mul(VeryLongInt a, VeryLongInt b);
};

