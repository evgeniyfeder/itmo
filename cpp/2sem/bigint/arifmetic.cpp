#include "big_integer.h"
#include <cassert>
#include <algorithm>
#include <stdexcept>

__extension__ typedef __int128 int128_t;

void big_integer::add_with_shift(big_integer const& a, int shift) {
	uint64_t tmp = 0;
	if (a.sign == 0)
		return;

	if (this->digits.size() >= a.digits.size() + shift) {
		for (size_t i = 0; i < a.digits.size(); i++) {
			uint64_t res = uint64_t(a.digits[i]) + this->digits[shift + i] + tmp;
			tmp = (res > big_integer::max_num);
			this->digits[shift + i] = uint32_t(res);
		}

		for (size_t i = a.digits.size(); i < this->digits.size() - shift; i++) {
			uint64_t res = this->digits[shift + i] + tmp;
			this->digits[shift + i] = uint32_t(res);
			tmp = res > big_integer::max_num;
		}
	}
	else if (size_t(shift) >= this->digits.size()) {
		for (int i = this->digits.size(); i < shift; i++)
			this->digits.push_back(0);
		for (size_t i = 0; i < a.digits.size(); i++)
			this->digits.push_back(a.digits[i]);
	}
	else {
		for (size_t i = shift; i < this->digits.size(); i++) {
			uint64_t res = uint64_t(a.digits[i - shift]) + this->digits[i] + tmp;
			tmp = (res > big_integer::max_num);
			this->digits[i] = uint32_t(res);
		}

		for (size_t i = this->digits.size(); i < a.digits.size() + shift; i++) {
			uint64_t res = a.digits[i - shift] + tmp;
			this->digits.push_back(uint32_t(res));
			tmp = res > big_integer::max_num;
		}
	}
	if (tmp > 0)
		this->digits.push_back(uint32_t(tmp));
	sign = 1;
	normalize();
}

big_integer operator+(big_integer const& a, big_integer const& b) {
	if (b.sign < 0)
		return a - (-b);
	else if (a.sign < 0)
		return b - (-a);

	big_integer result = a;
	result.add_with_shift(b, 0);
	return result;
}

big_integer operator-(big_integer const& a, big_integer const& b) {
	if (a.sign < 0)
		return -((-a) + b);
	else if (b.sign < 0)
		return a + (-b);
	
	const big_integer *less, *more;
	int res_sign;
	if (a.digits.size() >= b.digits.size()) {
		res_sign = 1;
		less = &b, more = &a;
	}
	else {
		res_sign = -1;
		less = &a, more = &b;
	}

	big_integer result;
	result.digits.pop_back();
	int reserve = 0;
	for (size_t i = 0; i < less->digits.size(); i++) {
		if (less->digits[i] <= int64_t(more->digits[i]) - reserve) {
			result.digits.push_back(more->digits[i] - reserve - less->digits[i]);
			reserve = 0;
		}
		else {
			uint64_t more_digit = uint64_t(more->digits[i]) + big_integer::base;
			result.digits.push_back(uint32_t(more_digit - reserve - less->digits[i]));
			reserve = 1;
		}
	}
	for (auto i = less->digits.size(); i < more->digits.size(); i++) {
		result.digits.push_back(more->digits[i] - reserve);
		reserve = 0;
	}

	if (more->digits.size() == less->digits.size() && reserve == 1) {
		res_sign = -res_sign;
		result.digits[result.digits.size() - 1] = uint32_t(big_integer::base - result.digits[result.digits.size() - 1]);
	}

	result.sign = res_sign;
	result.normalize();
	return result;
}

big_integer big_integer::mul_short(uint32_t b) const {
	if (b == 0)
		return big_integer();

	big_integer result; result.digits.pop_back();
	uint32_t carry = 0;
	for (size_t i = 0; i < digits.size(); i++) {
		uint64_t res_digit = uint64_t(digits[i]) * b + carry;
		carry = uint32_t(res_digit / big_integer::base);
		result.digits.push_back(uint32_t(res_digit));
	}
	if (carry != 0)
		result.digits.push_back(carry);
	result.sign = sign * (sign > 0 ? 1 : -1);
	return result;
}
big_integer operator*(big_integer const& a, big_integer const& b) {
	if (a.sign == 0 || b.sign == 0)
		return big_integer();
	
	big_integer result;
	for (size_t i = 0; i < b.digits.size(); i++)
		result.add_with_shift(a.mul_short(b.digits[i]), i);
	result.sign = a.sign * b.sign;
	return result;
}

big_integer big_integer::div_short(uint32_t b, uint32_t *ost) const {
	if (b == 0)
		throw std::runtime_error("Divide by zero");
	uint64_t carry = 0;
	big_integer result; result.digits.pop_back();

	result.digits.resize(digits.size());
	for (int i = int(digits.size()) - 1; i >= 0; i--) {
		uint64_t cur = digits[i] + carry * big_integer::base;
		result.digits[i] = uint32_t(cur / b);
		carry = cur % b;
	}
	if (ost != nullptr)
		*ost = uint32_t(carry);
	result.sign = sign * (b > 0 ? 1 : -1);
	result.normalize();
	return result;
}
big_integer operator/(big_integer const& a, big_integer const& b) {
	if (b.sign == 0)
		throw std::runtime_error("Divide by zero");
    if (a.sign == -1 && b.sign == -1)
        return (-a) /(-b);
    if (a.sign == -1)
        return -((-a) / b);
    if (b.sign == -1)
        return -(a / (-b));
	if (b > a)
		return big_integer();
	if (b.digits.size() == 1)
		return a.div_short(b.sign * b.digits[0], nullptr);
    big_integer result; result.digits.pop_back();

    __int128 divident = 0, divisor = 0, res = 0;
	big_integer cur_divident = a;
    int32_t prefix_len = b.digits.size() + 1;

	cur_divident.digits.push_back(0);
    divisor = (int128_t(b.digits[b.digits.size() - 1]) << 32) +
            int128_t(b.digits[b.digits.size() - 2]);
    for (int32_t i = cur_divident.digits.size() - 1; i - prefix_len + 1 >= 0; i--) {
        divident = (int128_t(cur_divident.digits[i]) << 64) +
                (int128_t(cur_divident.digits[i - 1]) << 32) +
                int128_t(cur_divident.digits[i - 2]);

		res = divident / divisor;
        if (res > UINT32_MAX)
            res = UINT32_MAX;

		big_integer check = b.mul_short(uint32_t(res));
        if (cur_divident.check_prefix(check, i - prefix_len + 1) == 1) {
			res--;
			check = b.mul_short(uint32_t(res));
		}
		result.digits.push_back(res);
        cur_divident.sub_prefix(check, i - prefix_len + 1);
	}

    std::reverse(result.digits.begin(), result.digits.end());
	result.sign = a.sign * b.sign;
	result.normalize();
    return result;
}

big_integer operator%(big_integer const& a, big_integer const& b) {
    return a - (a / b) * b;
}


big_integer& big_integer::operator+=(big_integer const& rhs) {
	return (*this = *this + rhs);
}
big_integer& big_integer::operator-=(big_integer const& rhs) {
	return (*this = *this - rhs);
}
big_integer& big_integer::operator*=(big_integer const& rhs) {
	return (*this = *this * rhs);
}
big_integer& big_integer::operator/=(big_integer const& rhs) {
	return (*this = *this / rhs);
}
big_integer& big_integer::operator%=(big_integer const& rhs) {
	return (*this = *this % rhs);
}
