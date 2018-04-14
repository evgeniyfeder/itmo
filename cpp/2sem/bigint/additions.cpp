#include <cstdint>
#include <string>
#include <algorithm>
#include "big_integer.h"

big_integer big_integer::reverse_like_adding_code() const {
	big_integer result; result.digits.pop_back();
	for (size_t i = 0; i < digits.size(); ++i) {
		result.digits.push_back(~digits[i]);
	}
	result.sign = 1;
	return result;
}

big_integer big_integer::to_adding_code() const {
	if (sign >= 0)
		return *this;
	big_integer result = (*this).reverse_like_adding_code() + 1;
	result.sign = sign;
	return result;
}

big_integer big_integer::to_sign_bit() const {
	if (sign >= 0)
		return *this;
	big_integer result = (*this).reverse_like_adding_code() + 1;
	result.sign = sign;
	return result;
}

void big_integer::normalize() {
	while (digits[digits.size() - 1] == 0 && digits.size() > 1)
		digits.pop_back();
	check_for_zero();
}

void big_integer::check_for_zero() {
	if (digits.size() == 1 && digits[0] == 0)
		sign = 0;
}

int big_integer::check_prefix(big_integer const& checker, uint32_t begin_ind) const {
    if (begin_ind + checker.digits.size() < digits.size() && digits[begin_ind + checker.digits.size()] != 0)
        return -1;
    for (size_t i = 0; i < checker.digits.size(); i++) {
        if (digits[checker.digits.size() - 1 - i + begin_ind] < checker.digits[checker.digits.size() - 1 - i])
			return 1;
        else if (digits[checker.digits.size() - 1 - i + begin_ind] > checker.digits[checker.digits.size() - 1 - i])
			return -1;
	}
	return 0;
}

void big_integer::sub_prefix(big_integer const& b, size_t begin_ind) {
    int64_t carry = 0;
	for (size_t i = 0; i < b.digits.size(); i++) {
        int64_t res = int64_t(digits[begin_ind + i]) - carry - b.digits[i];
        carry = res < 0;
        if (res < 0)
            res += big_integer::base;
        digits[begin_ind + i] = uint32_t(res);
	}
}

std::string to_string(big_integer const& a) {
	std::string result;
	big_integer tmp = a;
	if (a.sign == 0)
		return std::string("0");
	while (tmp.sign != 0) {
		uint32_t cur;
		tmp = tmp.div_short(10, &cur);
        result.push_back('0' + char(cur));
	}
	if (a.sign == -1)
		result.push_back('-');
	std::reverse(result.begin(), result.end());
	return result;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a) {
    s << to_string(a);
    return s;
}
