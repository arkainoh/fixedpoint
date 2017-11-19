#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#include <iostream>
#include <ieee754.h>
#include <math.h>
#define SIGN 1
#define EXPONENT 8
#define MANTISSA 23
#define EXP_BIAS 127

using namespace std;

typedef short fix16;
typedef char fix8;

void print_binary(int num, int len);

template <typename T>
class FixedPoint {
	public:
	T f;
	int wl;
	int iwl;
	int fwl;
	
	FixedPoint(int wl, int iwl) {
		this->wl = wl;
		this->iwl = iwl;
		this->fwl = wl - 1 - iwl;
	}

	FixedPoint(float f, int wl, int iwl) {
		this->wl = wl;
		this->iwl = iwl;
		this->fwl = wl - 1 - iwl;
		fix(f);
	}

	T fix(float f) {
		T ret = 0;
		ieee754_float standard;
		standard.f = f;

		unsigned int mantissa = standard.ieee.mantissa;
		int exp = standard.ieee.exponent - EXP_BIAS;
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
		this->f = ret;
		return ret;
	}
	
	void printb() {
		int integer = this->f >> fwl;
	
		print_binary(integer, iwl + 1);
		cout << ".";
		print_binary(this->f, fwl);
	}
	
	void printd() {
		int num = this->f;
		if(num >> this->wl - 1) {
			cout << "-";
			num = ~(num - 1);
		}

		int integer = num >> this->fwl;
		float fraction = 0.0;
		float div = 0.5;
		unsigned int mask = 1 << this->fwl - 1;
		for(int i = 0; i < this->fwl; i++) {
			if(mask & num) {
				fraction += div;
			}
			mask = mask >> 1;
			div /= 2;
		}
		cout << (integer + fraction);
	}

	FixedPoint<T> operator+(FixedPoint<T> f) {
		FixedPoint<T> ret(this->wl, this->iwl);
		ret.f = this->f + f.f;
		return ret;
	}

	FixedPoint<T> operator-(FixedPoint<T> f) {
		FixedPoint<T> ret(this->wl, this->iwl);
		ret.f = this->f - f.f;
		return ret;
	}
	
	FixedPoint<T> operator*(FixedPoint<T> f) {
		FixedPoint<T> ret(this->wl, this->iwl);
		int tmp = this->f * f.f;
		ret.f = tmp >> this->fwl;
		return ret;
	}

	FixedPoint<T> operator/(FixedPoint<T> f) {
		FixedPoint<T> ret(this->wl, this->iwl);
		int tmp = this->f << this->fwl;
		ret.f = tmp / f.f;
		return ret;
	}

};

void print_binary(int num, int len) {
	
	unsigned int mask = 1 << len - 1;

	while(len--) {
		if(num & mask) cout << "1";
		else cout << "0";

		mask = mask >> 1;
	}
}

int optiwl(float floats[], int len) {
	int max, iwl = 0;

	for(int i = 0; i < len; i++) {
		int n = floats[i];

		if(n < 0) n *= (-1);
		if(max < n) max = n;
	}

	if(max) iwl = log2(max) + 1;

	return iwl;
}

#endif
