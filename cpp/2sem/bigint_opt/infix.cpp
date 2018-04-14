#include <cstdint>
#include "big_integer.h"

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
	big_integer result(*this);
	result.sign *= -1;
	return result;
}

big_integer big_integer::operator~() const {
	big_integer adding_code = this->to_adding_code();
	big_integer result; result.digits.do_empty();
    for (size_t i = 0; i < digits.get_size(); ++i) {
        result.digits.push_back(~adding_code.digits[i]);
    }
	result.sign = -sign;
	return result.to_sign_bit();
}

big_integer& big_integer::operator++() {
	return (*this = *this + 1);
}

big_integer big_integer::operator++(int) {
	big_integer tmp = *this;
	*this = *this + 1;
	return tmp;
}

big_integer& big_integer::operator--() {
	return (*this = *this - 1);
}
big_integer big_integer::operator--(int) {
	big_integer tmp = *this;
	*this = *this + 1;
	return tmp;
}