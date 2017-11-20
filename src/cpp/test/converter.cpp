#include <iostream>
#include "../fixedpoint.h"

int main() {
	ieee754_float a;
	int iwl;

	cout << "float: ";
	cin >> a.f;
	
	cout << "IWL: ";
	cin >> iwl;

	cout << "sign: ";
	print_binary(a.ieee.negative, SIGN);
	cout << endl;

	cout << "exponent: ";
	print_binary(a.ieee.exponent, EXPONENT);
	cout << endl;

	cout << "mantissa: ";
	print_binary(a.ieee.mantissa, MANTISSA);
	cout << endl;
	
	FixedPoint<fix16> f16(16, iwl);
	f16.fix(a.f);
	cout << endl << "converted to fix16" << endl;
	f16.printb();
	
	cout << " (";
	print_binary(f16.f, 16);
	cout << ")" << endl;

	f16.printd();
	cout << endl;

	FixedPoint<fix8> f8(8, iwl);
	f8.fix(a.f);
	cout << endl << "converted to fix8" << endl;
	f8.printb();

	cout << " (";
	print_binary(f8.f, 8);
	cout << ")" << endl;

	f8.printd();
	cout << endl;
	return 0;
}

