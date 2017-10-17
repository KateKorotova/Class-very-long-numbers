#include "classVeryLongInt.h"
#include <iostream>
#include <cstdlib>


VeryLongInt::VeryLongInt()
{
}

ostream& operator<< (ostream& os, const VeryLongInt& num) {
	for (int i = 0; i < num.digits.size(); i++)
		os<< num.digits[i];
	return os; 
}

istream& operator >> (istream& os, VeryLongInt& num) {
	cin >> num.longInt;
	for (int i = (int)num.longInt.length(); i > 0; i -= num.base)
		if (i < num.base)
			num.digits.push_back(atoi(num.longInt.substr(0, i).c_str()));
		else
			num.digits.push_back(atoi(num.longInt.substr(i - num.base, num.base).c_str()));
	return os;
}

int main() {
	cout << "Enter your number:" << endl;
	VeryLongInt a;
	cin >> a; 
	cout << a; 
	system("pause");
}