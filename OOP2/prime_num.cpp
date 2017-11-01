#include "classVeryLongInt.h"
#include <math.h>

using namespace std;


VeryLongInt gcd(VeryLongInt a, VeryLongInt b) {
	while (a != 0 && b != 0) {
		if (a > b)
			a = a%b;
		else
			b = b%a;
	}
	return a + b;
}

VeryLongInt mod_pow(VeryLongInt a, VeryLongInt b, VeryLongInt c) {
	if (b == 0) return 1;
	if (b.digits[0] % 2 == 1)
		return (mod_pow(a, b - 1, c)*a) % c;
	else {
		VeryLongInt res;
		res = mod_pow(a, b / 2, c);
		return (res*res) % c;
	}
}

VeryLongInt symbol_jac(VeryLongInt a, VeryLongInt b) {
	if (gcd(a, b) != 1)
		return 0;
	int r = 1;
	if (a.sign == -1){
		a.sign = 1;
		if (b % 4 == 3)
			r = -r;
	}
	while (a != 0){
		VeryLongInt t(0);
		while (a % 2 == 0) {
			t = t + 1;
			a = a / 2;
		}
		if (t % 2 != 0) {
			if (b % 8 == 3 || b % 8 == 5)
				r = -r;
		}
		
		if ((a % 4 == 3) && (b % 4 == 3))
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

	if (a % 2 == 0)
		return false; 
	for (int i = 0; i < k; i++) {
		VeryLongInt num = (rand_()%(a - 3) + 2); 
		if (gcd(num, a) > 1)
			return false; 
		VeryLongInt j(symbol_jac(num, a));
		VeryLongInt tmp;
		tmp = (a - 1) / 2;
		VeryLongInt _j = mod_pow(num, tmp, a);
		if (j == (-1)) j = j + a;
		if (_j != j)
			return false;
	}
	return true; 
}


bool lehmann(VeryLongInt a, int t) {
	for (int i = 0; i < t; i++) {
		VeryLongInt num = rand_();
		VeryLongInt res = mod_pow(num, (a - 1) / 2, a);
		if (res != a - 1 && res != 1) 
			return false;
	}
	return true; 
}

bool rabin_miller(VeryLongInt p, int t) {
	for (int i = 0; i < t; i++) {
		VeryLongInt b = (p - 1) / 2;
		VeryLongInt m = (p - 1) / mod_pow(b, 2, 1);
		VeryLongInt a = rand_();
		VeryLongInt j = 0;
		VeryLongInt z = (a*m) % p;
		if (z == 1 || z == p - 1)
			continue;
		for (; j < b; j = j+1)
		{
			z = (z * z) % p;
			if (z == 1)
				return false;
			if (z == p - 1)
				break;
		}

		if (j == b && z != p - 1)
			return false;
	}

	return true;
}





