#include <stdio.h>
#include <ieee754.h>

typedef short fix16;

fix16 new_fix16(float f, int int_len) {
	short ret = 0;
	ieee754_float standard;
	standard.f = f;

	unsigned int mantissa = standard.ieee.mantissa;
	int exp = standard.ieee.exponent - 127;
	int frac_len = 15 - int_len;
	unsigned int integer, fraction;

	if(exp > 0) {
		integer = mantissa >> 23 - exp;
		integer = integer | (1 << exp);

		fraction = mantissa << 9 + exp;
		fraction = fraction >> 32 - frac_len;
		integer = integer << frac_len;

		ret = ret | integer;

	} else {
		integer = 0;
		fraction = mantissa | (1 << 23);
		fraction = fraction >> 23 - frac_len - exp;
	}

	ret = ret | fraction;

	if(standard.ieee.negative) {
		ret = ~ret + 1;
	}

	return ret;
}

void printb(int num, int bits) {
	
	unsigned int mask = 1 << bits - 1;

	while(bits--) {
		if(num & mask) printf("1");
		else printf("0");

		mask = mask >> 1;
	}
}

void printb_fix16(fix16 num, int int_len) {
	int frac_len = 15 - int_len;
	int integer = num >> frac_len;
	
	printb(integer, int_len + 1);
	printf(".");
	printb(num, frac_len);
}

void printd_fix16(unsigned short num, int int_len) {
	int frac_len = 15 - int_len;
	if(num >> 15) {
		printf("-");
		num = ~(num - 1);
	}

	int integer = (num << 1) >> frac_len + 1;
	int fraction = (num << 1 + int_len) >> int_len + 1;
	float f = 0.0;
	float div = 0.5;
	unsigned int mask = 1 << frac_len - 1;
	for(int i = 0; i < frac_len; i++) {
		if(mask & fraction) {
			f += div;
		}
		mask = mask >> 1;
		div /= 2;
	}
	printf("%f", integer + f);

}

fix16 mul_fix16(fix16 a, fix16 b, int int_len) {
	int c = a * b;
	return c >> 15 - int_len;
}

fix16 div_fix16(fix16 a, fix16 b, int int_len) {
	int c = a << 15 - int_len;
	return c / b;
}

int main() {
	ieee754_float a;

	scanf("%f", &a.f);
	
	printf("sign: ");
	printb(a.ieee.negative, 1);
	puts("");

	printf("exponent: ");
	printb(a.ieee.exponent, 8);
	puts("");

	printf("mantissa: ");
	printb(a.ieee.mantissa, 23);
	puts("");

	fix16 f = new_fix16(a.f, 3);
	puts("\nconverted to fix16");
	printb_fix16(f, 3);
	printf(" (");
	printb(f, 16);
	puts(")");
	printd_fix16(f, 3);
	puts("");
	
	return 0;
}

