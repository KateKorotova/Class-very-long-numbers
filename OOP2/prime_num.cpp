#include "classVeryLongInt.h"
#include <math.h>

using namespace std;


VeryLongInt gcd(VeryLongInt a, VeryLongInt b) {
	VeryLongInt zero(0);
	while (a != zero && b != zero) {
		if (a > b)
			a = a%b;
		else
			b = b%a;
	}
	return a + b;
}

VeryLongInt mod_pow(VeryLongInt a, VeryLongInt b, VeryLongInt c) {
	VeryLongInt res(1);
	VeryLongInt zero(0);
	VeryLongInt one(1);
	VeryLongInt two(2);
	if (b == zero) return one;
	if (b.digits[0] % 2 == 1)
		return (mod_pow(a, b - one, c)*a) % c;
	else {
		VeryLongInt res;
		res = mod_pow(a, b / 2, c);
		return (res*res) % c;
	}
}

VeryLongInt symbol_jac(VeryLongInt a, VeryLongInt b) {
	VeryLongInt one(1);
	VeryLongInt two(2);
	VeryLongInt three(3);
	VeryLongInt four(4);
	VeryLongInt five(5);
	VeryLongInt eight(8);
	VeryLongInt zero(0);
	if (gcd(a, b) != one)
		return zero;
	int r = 1;
	if (a.sign == -1){
		a.sign = 1;
		if (b % four == three)
			r = -r;
	}
	while (a != zero){
		VeryLongInt t(0);
		while (a % two == zero) {
			t = t + one;
			a = a / 2;
		}
		if (t % two != zero) {
			if (b % eight == three || b % eight == five)
				r = -r;
		}
		
		if ((a % four == three) && (b % four == three))
			r = -r;
		VeryLongInt c;
		c = a;
		a = b % c;
		b = c;
	}
	VeryLongInt ans(r);
	return ans; 
}

VeryLongInt rand_() {
	static VeryLongInt x(0);
	VeryLongInt m(100001);
	VeryLongInt a(2);
	VeryLongInt c(23);
	x = (a*x + c);
	x = x % m;
	return x;
}

bool sol_shtr(VeryLongInt a, long long k) {
	VeryLongInt one(1);
	VeryLongInt two(2);
	VeryLongInt three(3);
	VeryLongInt minusone(-1);

	if (a % two == 0)
		return false; 
	for (int i = 0; i < k; i++) {
		VeryLongInt num = (rand_()%(a - three) + two); 
		if (gcd(num, a) > one)
			return false; 
		VeryLongInt j(symbol_jac(num, a));
		VeryLongInt tmp;
		tmp = (a - one) / 2;
		VeryLongInt _j = mod_pow(num, tmp, a);
		if (j == minusone) j = j + a;
		if (_j != j)
			return false;
	}
	return true; 
}

//
//bool lemera() {
//
//}


