#include "fixedpoint.h"

int fix(float f, int wl, int iwl) {
	int ret = 0;
	ieee754_float standard;
	standard.f = f;

	unsigned int mantissa = standard.ieee.mantissa;
	int exp = standard.ieee.exponent - EXP_BIAS;
	int fwl = wl - 1 - iwl;
	unsigned int integer, fraction;

	if(exp > 0) {
		integer = mantissa >> MANTISSA - exp;
		integer = integer | (1 << exp);

		fraction = mantissa << SIGN + EXPONENT + exp;
		fraction = fraction >> sizeof(unsigned int) * 8 - fwl;
		integer = integer << fwl;

		ret = ret | integer;

	} else {
		integer = 0;
		fraction = mantissa | (1 << MANTISSA);
		fraction = fraction >> MANTISSA - fwl - exp;
	}

	ret = ret | fraction;

	if(standard.ieee.negative) {
		ret = ~ret + 1;
	}

	return ret;
}

void print_binary(int num, int len) {
	
	unsigned int mask = 1 << len - 1;

	while(len--) {
		if(num & mask) printf("1");
		else printf("0");

		mask = mask >> 1;
	}
}

void printb_fix(int num, int wl, int iwl) {
	int fwl = wl - 1 - iwl;
	int integer = num >> fwl;
	
	print_binary(integer, iwl + 1);
	printf(".");
	print_binary(num, fwl);
}

void printd_fix(unsigned int num, int wl, int iwl) {
	int fwl = wl - 1 - iwl;
	if(num >> wl - 1) {
		printf("-");
		num = ~(num - 1);
	}

	int integer = num >> fwl;

	float fraction = 0.0;
	float div = 0.5;
	unsigned int mask = 1 << fwl - 1;
	for(int i = 0; i < fwl; i++) {
		if(mask & num) {
			fraction += div;
		}
		mask = mask >> 1;
		div /= 2;
	}
	printf("%f", integer + fraction);

}

int mul_fix(int a, int b, int wl, int iwl) {
	int c = a * b;
	return c >> wl - 1 - iwl;
}

int div_fix(int a, int b, int wl, int iwl) {
	int c = a << wl - 1 - iwl;
	return c / b;
}

