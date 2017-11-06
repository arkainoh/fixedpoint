#include "fixedpoint.h"
#include <stdio.h>

int main() {
	ieee754_float a;

	scanf("%f", &a.f);
	
	printf("sign: ");
	print_binary(a.ieee.negative, SIGN);
	puts("");

	printf("exponent: ");
	print_binary(a.ieee.exponent, EXPONENT);
	puts("");

	printf("mantissa: ");
	print_binary(a.ieee.mantissa, MANTISSA);
	puts("");

	fix16 f16 = fix(a.f, 16, 3);
	puts("\nconverted to fix16");
	printb_fix(f16, 16, 3);
	printf(" (");
	print_binary(f16, 16);
	puts(")");
	printd_fix(f16, 16, 3);
	puts("");
	
	fix8 f8 = fix(a.f, 8, 3);
	puts("\nconverted to fix8");
	printb_fix(f8, 8, 3);
	printf(" (");
	print_binary(f8, 8);
	puts(")");
	printd_fix(f8, 8, 3);
	puts("");

	return 0;
}

