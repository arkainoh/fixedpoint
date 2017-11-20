#include <iostream>
#include "../fixedpoint.h"

int main() {
	int f;
	ieee754_float a;
	int wl, iwl;

	cout << "fix: ";
	cin >> f;
	
	cout << "WL: ";
	cin >> wl;

	cout << "IWL: ";
	cin >> iwl;
	
	FixedPoint<int> fix(wl, iwl);
	fix.f = f;

	cout << endl << "<fix info>" << endl;
	cout << "binary: ";
	fix.printb();
	cout << " (";
	print_binary(fix.f, wl);
	cout << ")" << endl;
	cout << "decimal: ";
	fix.printd();
	cout << " (" << fix.f << ")" << endl;
	
	cout << endl << "<result>" << endl;
	a.f = fix.get_float();
	cout << "float: " << a.f << endl;
	cout << "sign: ";
	print_binary(a.ieee.negative, SIGN);
	cout << endl;

	cout << "exponent: ";
	print_binary(a.ieee.exponent, EXPONENT);
	cout << endl;

	cout << "mantissa: ";
	print_binary(a.ieee.mantissa, MANTISSA);
	cout << endl;

	return 0;
}

