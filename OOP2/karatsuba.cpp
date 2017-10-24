#include "classVeryLongInt.h"
#include <algorithm>

using namespace std; 


 VeryLongInt karatsuba_mul(VeryLongInt a, VeryLongInt b) {
	 VeryLongInt res;
	 long long len = max(a.digits.size(), b.digits.size());

	 if (len == 1) {
		 return a*b; 
	 }
	 if (len % 2 == 1) len++;
	 a = a.expansion(len);
	 b = b.expansion(len);
	 res = res.expansion(2 * len);
	 
	 int half = len / 2;
	 VeryLongInt a0(half), a1(half), b0(half), b1(half), a01(half), b01(half);

	 for (int i = 0; i < half; i++) {
		 a0.digits[i] = a.digits[i];
		 b0.digits[i] = b.digits[i];
	 }
	 for (int i = half; i < len; i++) {
		 a1.digits[i - half] = a.digits[i];
		 b1.digits[i - half] = b.digits[i];
	 }
	 a01 = a0 + a1;
	 b01 = b0 + b1;

	 VeryLongInt prod0 = karatsuba_mul(a0, b0);
	 VeryLongInt prod1 = karatsuba_mul(a1, b1);
	 VeryLongInt prod2 = karatsuba_mul(a01, b01);

	 prod2 = prod2 - (prod0 + prod1);

	 VeryLongInt one = prod1.rshift(2*half).normalize();
	 VeryLongInt two = prod2.rshift(half).normalize();
	 VeryLongInt three = prod0.normalize();
	 res = one + two + three;

	 res.sign = a.sign*b.sign; 

	 return res;
 }
