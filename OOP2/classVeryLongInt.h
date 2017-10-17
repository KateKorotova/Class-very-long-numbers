#pragma once
#include <string>
#include <vector>
#include <iostream>


using namespace std; 

class VeryLongInt {
private: 
	string longInt;
	vector <long long> digits; 
	static const int base = 10; 
public:  
	VeryLongInt();
	//void operator + (const vector <long long> &c); 
	//void operator - (const vector <long long> &c);
	//void operator * (const vector <long long> &c);
	//void operator / (const vector <long long> &c);

	friend ostream& operator <<(ostream& os, const VeryLongInt& num);
	friend istream& operator >>(istream& os, VeryLongInt& num);
};
