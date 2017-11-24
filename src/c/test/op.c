#include <iostream>
#include "../fixedpoint.h"

int main() {
	float fl1, fl2;
	fix16 fix1, fix2;
	int wl, iwl;
	
	printf("WL: ");
	scanf("%d", &wl);
	
	printf("IWL: ");
	scanf("%d", &iwl);

	printf("float1: ");
	scanf("%f1", &fl1);

	printf("float2: ");
	scanf("%f2", &fl2);

	fix1 = float2fix(fl1, wl, iwl);
	fix2 = float2fix(fl2, wl, iwl);

	printf("\n<float>\n");
	printf("%f + %f = %f\n", fl1, fl2, fl1 + fl2);
	printf("%f - %f = %f\n", fl1, fl2, fl1 - fl2);
	printf("%f * %f = %f\n", fl1, fl2, fl1 * fl2);
	printf("%f / %f = %f\n", fl1, fl2, fl1 / fl2);

	printf("\n<fix>\n");
	printd_fix(fix1, wl, iwl);
	printf(" + ");
	printd_fix(fix2, wl, iwl);
	printf(" = ");
	printd_fix(fix1 + fix2, wl, iwl);
	printf("\n");
	printd_fix(fix1, wl, iwl);
	printf(" - ");
	printd_fix(fix2, wl, iwl);
	printf(" = ");
	printd_fix(fix1 - fix2, wl, iwl);
	printf("\n");
	printd_fix(fix1, wl, iwl);
	printf(" * ");
	printd_fix(fix2, wl, iwl);
	printf(" = ");
	printd_fix(mul_fix(fix1, fix2, wl, iwl), wl, iwl);
	printf("\n");
	printd_fix(fix1, wl, iwl);
	printf(" / ");
	printd_fix(fix2, wl, iwl);
	printf(" = ");
	printd_fix(div_fix(fix1, fix2, wl, iwl), wl, iwl);
	printf("\n");

}
