#include <cstdint>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <stdexcept>
#include "big_integer.h"

big_integer::big_integer() : digits{ 0 }, sign(0) {
}

big_integer::~big_integer() {}

big_integer::big_integer(const big_integer &other) {
    digits = other.digits;
    sign = other.sign;
}

#define ABS_INT_MIN 2147483648u
big_integer::big_integer(int a) : sign(a != 0 ? (a > 0 ? 1 : -1) : 0) {
	if (a == INT_MIN)
		digits.push_back(ABS_INT_MIN);
	else
		digits.push_back(abs(a));
}

big_integer& big_integer::operator=(big_integer const& other) {
    digits = other.digits;
    sign = other.sign;
	return *this;
}


big_integer::big_integer(std::string const& str) : big_integer() {
	int begin_number = (str[0] == '-'), res_sign = (str[0] == '-' ? -1 : 1);
	for (size_t i = begin_number; i < str.size(); i++) {
		*this = *this * 10 + (str[i] - '0');
	}
	sign = res_sign;
    normalize();
}