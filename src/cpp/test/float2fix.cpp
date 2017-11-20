#include <iostream>
#include "../fixedpoint.h"

int main() {
	ieee754_float a;
	int wl, iwl;

	cout << "float: ";
	cin >> a.f;
	
	cout << "WL: ";
	cin >> wl;

	cout << "IWL: ";
	cin >> iwl;

	cout << endl << "<float info>" << endl;
	cout << "sign: ";
	print_binary(a.ieee.negative, SIGN);
	cout << endl;

	cout << "exponent: ";
	print_binary(a.ieee.exponent, EXPONENT);
	cout << endl;

	cout << "mantissa: ";
	print_binary(a.ieee.mantissa, MANTISSA);
	cout << endl;
	
	cout << endl << "<result>" << endl;
	FixedPoint<int> ret(wl, iwl);
	ret.fix(a.f);
	cout << "binary: ";
	ret.printb();
	cout << " (";
	print_binary(ret.f, wl);
	cout << ")" << endl;
	cout << "decimal: ";
	ret.printd();
	cout << " (" << ret.f << ")" << endl;

	return 0;
}

