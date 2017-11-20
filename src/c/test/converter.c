#include "../fixedpoint.h"
#include <stdio.h>

int main() {
	ieee754_float a;
	int iwl;

	printf("float: ");
	scanf("%f", &a.f);
	
	printf("IWL: ");
	scanf("%d", &iwl);

	printf("sign: ");
	print_binary(a.ieee.negative, SIGN);
	puts("");

	printf("exponent: ");
	print_binary(a.ieee.exponent, EXPONENT);
	puts("");

	printf("mantissa: ");
	print_binary(a.ieee.mantissa, MANTISSA);
	puts("");
	
	

	fix16 f16 = fix(a.f, 16, iwl);
	puts("\nconverted to fix16");
	printb_fix(f16, 16, iwl);
	printf(" (");
	print_binary(f16, 16);
	puts(")");
	printd_fix(f16, 16, iwl);
	puts("");
	
	fix8 f8 = fix(a.f, 8, iwl);
	puts("\nconverted to fix8");
	printb_fix(f8, 8, iwl);
	printf(" (");
	print_binary(f8, 8);
	puts(")");
	printd_fix(f8, 8, iwl);
	puts("");

	return 0;
}

