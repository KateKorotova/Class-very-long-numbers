#include "classVeryLongInt.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>


using namespace std;

VeryLongInt::VeryLongInt(){
	sign = 1;
}


istream& operator >> (istream& os, VeryLongInt& num) {
	string longInt;
	cin >> longInt;
	num.sign = (longInt[0] == '-' ? -1 : 1);
	if (longInt[0] == '-' || longInt[0] == '+')
		longInt.erase(0,1);

	int blocks = longInt.length() / base_pow;
	int last = longInt.length() % base_pow;
	for (int i = 1; i <= blocks; i++) {
		string part_str = longInt.substr( longInt.length() - i*base_pow, base_pow);
		num.digits.push_back(atoi(part_str.c_str()));
	}
	if (last > 0) {
		string part_str = longInt.substr(0, last);
		num.digits.push_back(atoi(part_str.c_str()));
	}
	return os;
}

ostream& operator<< (ostream& os, const VeryLongInt& num) {
	if (num.digits.size() > 0) {
		if (num.sign < 0)
			os << '-';
		os << num.digits[num.digits.size() - 1];
		for (int i = num.digits.size() - 2; i >= 0; i--) {
			string res = to_string(num.digits[i]);
			for (int j = 0; j < base_pow - res.length(); j++)
				os << 0;
			os << num.digits[i];
		}
	}
	return os;
}  

VeryLongInt VeryLongInt::add_module(const VeryLongInt& b)const {
	VeryLongInt res;

	int p = 0;
	for (int i = 0; i < max(b.digits.size(), (*this).digits.size()); i++){
		int ost = (i < (*this).digits.size() ? (*this).digits[i] : 0) + (i < b.digits.size() ? b.digits[i] : 0) + p;
		res.digits.push_back(ost % base);
		p = ost / base; 
	}
	if (p > 0) {
		res.digits.push_back(p);
	}
	return res;
}// add without sign

VeryLongInt VeryLongInt::sub_module(const VeryLongInt& b)const {
	VeryLongInt c;
	int p = 0;
	for (int i = 0; i < (*this).digits.size(); i++) {
		int number = (i < b.digits.size() ? b.digits[i] : 0);
		if ((*this).digits[i] + p >= number) {
			c.digits.push_back((*this).digits[i] + p - number);
			p = 0;
		}
		else{
			c.digits.push_back(base + (*this).digits[i] + p - number);
			p = -1;
		}
	}
	while (c.digits.size() > 1 && c.digits.back() == 0) {
		c.digits.pop_back();
	}
	return c;

} // sub without sign

int VeryLongInt::cmp_module(const VeryLongInt& b) {
	if ((*this).digits.size() < b.digits.size())
		return -1;
	if ((*this).digits.size() > b.digits.size())
		return 1;
	for (int i = b.digits.size()-1; i >=0 ; i--)
		if ((*this).digits[i] < b.digits[i])
			return -1;
		else if ((*this).digits[i] > b.digits[i])
				return 1;
	return 0;
}  // which number is longer or if they have same length - compare which one is greater in magnitude 

bool VeryLongInt::operator == (const VeryLongInt& b) {
	if ((*this).sign == b.sign && (*this).cmp_module(b) == 0)
		return true;
	return false;
}
bool VeryLongInt::operator != (const VeryLongInt& b) {
	return !((*this) == b);
}
bool VeryLongInt::operator >(const VeryLongInt& b) {
	int cmp = (*this).cmp_module(b);
	if ((*this).sign > 0 && b.sign > 0 && cmp > 0)
		return true;
	if ((*this).sign > 0 && b.sign < 0)
		return true;
	if ((*this).sign < 0 && b.sign < 0 && cmp < 0)
		return true;
	return false;
}
bool VeryLongInt::operator <(const VeryLongInt& b) {
	return !((*this) > b || (*this) == b);
}
bool VeryLongInt::operator >=(const VeryLongInt& b) {
	return !((*this) < b);
}
bool VeryLongInt::operator <=(const VeryLongInt& b) {
	return !((*this) > b);
}
VeryLongInt VeryLongInt::operator -()const{
	VeryLongInt ans = *this;
	ans.sign *= -1;
	return ans;
}

VeryLongInt VeryLongInt::operator+(const VeryLongInt& b) {
	VeryLongInt ans;
	if ((*this).sign == b.sign) {
		ans = (*this).add_module(b);
		ans.sign = b.sign;
	}
	else {
		int cmp = (*this).cmp_module(b);
		ans = (cmp == -1 ? b.sub_module((*this)) : (*this).sub_module(b));
		ans.sign = (cmp < 0 ? b.sign : (*this).sign);
		if (ans.digits.size() == 1 && ans.digits[0] == 0)
			ans.sign = 1;
	}
	return ans;
}

VeryLongInt::VeryLongInt(long long n) {
	(*this).sign = (n < 0 ? -1 : 1);
	n = abs(n);
	if (n == 0)
		(*this).digits.push_back(0);
	else {
		while (n > 0) {
			(*this).digits.push_back(n % base);
			n /= base;
		}
	}
}

VeryLongInt VeryLongInt::operator-(const VeryLongInt& b) {
	return (*this) + (-b);
}


VeryLongInt VeryLongInt::operator*(const VeryLongInt& b)const {
	VeryLongInt res;
	VeryLongInt final;

	for (int i = 0; i < b.digits.size(); i++) {
		for (int j = 0; j < (*this).digits.size(); j++) {
			if (!((j + i) < res.digits.size()))
				res.digits.push_back((*this).digits[j] * b.digits[i]);
			else
				res.digits[j + i] += (*this).digits[j] * b.digits[i];
		}
	}
	int p = 0;
	for (int i = 0; i < res.digits.size(); i++) {
		int ost = res.digits[i] + p;
		res.digits[i] = ost % base;
		p = ost / base;
	}
	if (p > 0)
		res.digits.push_back(p);
	res.sign = (*this).sign * b.sign;
	return res;
}

VeryLongInt VeryLongInt::expansion(long long size) {
	VeryLongInt ans = *this;
	while (ans.digits.size() < size)
		ans.digits.push_back(0);
	return ans;
}

VeryLongInt VeryLongInt::normalize() {
	VeryLongInt ans = *this;
	while (ans.digits.size() > 1 && ans.digits.back() == 0) {
		ans.digits.erase(ans.digits.end()-1);
	}
	return ans;
}

VeryLongInt VeryLongInt::rshift(long long size){
	VeryLongInt ans = (*this);
	for (int i = 0; i < size; i++)
		ans.digits.insert(ans.digits.begin(), 0);
	return ans;
}

VeryLongInt VeryLongInt::operator/(long long num) {
	int ost = 0;
	VeryLongInt res;
	for (long long i = (*this).digits.size() - 1; i >= 0; i--) {
		ost = ost*base + (*this).digits[i];
		res.digits.insert(res.digits.begin(), ost / num);
		ost %= num; 
	}
	res = res.normalize();
	return res; 
}


VeryLongInt VeryLongInt::operator/(const VeryLongInt& b) {
	VeryLongInt l = 0;	 
	VeryLongInt r = (*this);
	VeryLongInt one(1);
	while ( l + one < r) {
		VeryLongInt midl = (l + r) / 2;
		if (midl*b> (*this))
			r = midl;
		else
			l = midl;
	}
	if (r*b > (*this))
		return l;
	else
		return r; 
} // (*this) = b*c; c - our result; 



int main() {
	cout << "Enter your number:" << endl;
	VeryLongInt a;
	VeryLongInt b;
	cin >> a; 
	cin >> b;

	cout << karatsuba_mul(a, b) << endl;
	cout << a*b << endl;
	cout << a / b << endl; 

	 

	system("pause");
}

