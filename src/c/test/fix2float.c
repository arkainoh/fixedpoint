#include <iostream>
#include "../fixedpoint.h"

int main() {
	int f;
	ieee754_float a;
	int wl, iwl;

	printf("fix: ");
	scanf("%d", &f);
	
	printf("WL: ");
	scanf("%d", &wl);

	printf("IWL: ");
	scanf("%d", &iwl);

	printf("\n<fix info>\n");
	printf("binary: ");
	printb_fix(f, wl, iwl);
	printf(" (");
	print_binary(f, wl);
	printf(")\n");
	printf("decimal: ");
	printd_fix(f, wl, iwl);
	printf(" (%d)\n", f);
	
	printf("\n<result>\n");
	a.f = fix2float(f, wl, iwl);
	printf("float: %f\n", a.f);
	printf("sign: ");
	print_binary(a.ieee.negative, SIGN);
	printf("\n");

	printf("exponent: ");
	print_binary(a.ieee.exponent, EXPONENT);
	printf("\n");

	printf("mantissa: ");
	print_binary(a.ieee.mantissa, MANTISSA);
	printf("\n");

	return 0;
}

