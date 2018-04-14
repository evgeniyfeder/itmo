#include <cstdint>
#include "big_integer.h"

bool operator==(big_integer const& a, big_integer const& b) {
	if (a.digits.get_size() != b.digits.get_size() || a.sign != b.sign)
        return false;

    for (size_t i = 0; i < a.digits.get_size(); i++)
        if (a.digits[i] != b.digits[i])
            return false;
    return true;
}

bool operator!=(big_integer const& a, big_integer const& b) {
    return !(a == b);
}
bool operator<(big_integer const& a, big_integer const& b) {
	if (a.sign == 0)
		return b.sign > 0;
	else if (b.sign == 0)
		return a.sign < 0;
	else if (a.sign != b.sign)
		return a.sign < b.sign;
	else if (a.digits.get_size() < b.digits.get_size())
		return a.sign == 1 && b.sign == 1;
	else if (a.digits.get_size() > b.digits.get_size())
		return a.sign == -1 && b.sign == -1;
	else if (a.sign == -1)
		return (-a) > (-b);

    for (int i = a.digits.get_size() - 1; i >= 0; i--)
        if (a.digits[i] < b.digits[i])
            return true;
        else if (a.digits[i] > b.digits[i])
            return false;
    return false;
}

bool operator>(big_integer const& a, big_integer const& b) {
	if (a.sign == 0)
		return b.sign < 0;
	else if (b.sign == 0)
		return a.sign > 0;
	else if (a.sign != b.sign)
		return a.sign > b.sign;
	else if (a.digits.get_size() < b.digits.get_size())
		return a.sign == -1 && b.sign == -1;
	else if (a.digits.get_size() > b.digits.get_size())
		return a.sign == 1 && b.sign == 1;
	else if (a.sign == -1)
		return (-a) < (-b);

    for (int i = a.digits.get_size() - 1; i >= 0; i--)
        if (a.digits[i] > b.digits[i])
            return true;
        else if (a.digits[i] < b.digits[i])
            return false;
    return false;
}

bool operator<=(big_integer const& a, big_integer const& b) {
    return !(a > b);
}
bool operator>=(big_integer const& a, big_integer const& b) {
    return  !(a < b);
}


big_integer big_integer::do_logical_operation(big_integer const& a, big_integer const& b, uint32_t (*f)(uint32_t a, uint32_t b), bool (*get_sign)(int a, int b)) {
	big_integer result; result.digits.do_empty();
	big_integer a_adding = a.to_adding_code(), b_adding = b.to_adding_code();
    const big_integer *less, *more;
    if (a_adding.digits.get_size() > b_adding.digits.get_size())
        less = &b_adding, more = &a_adding;
    else
        less = &a_adding, more = &b_adding;

    for (size_t i = 0; i < less->digits.get_size(); i++) {
        result.digits.push_back(f(less->digits[i], more->digits[i]));
    }
    for (auto i = less->digits.get_size(); i < more->digits.get_size(); i++) {
        result.digits.push_back(f((less->sign  >= 0 ? 0 : UINT32_MAX), more->digits[i]));
    }
	result.sign = (get_sign(a.sign, b.sign) ? -1 : 1);
	result.normalize();
    return result.to_sign_bit();
}

big_integer operator&(big_integer const& a, big_integer const& b) {
	return big_integer::do_logical_operation(a, b, [](uint32_t a, uint32_t b) { return a & b; }, [](int a, int b) {return (a == -1 && b == -1); });
}

big_integer& big_integer::operator&=(big_integer const& rhs) {
    return (*this = *this & rhs);
}

big_integer operator|(big_integer const& a, big_integer const& b) {
    return big_integer::do_logical_operation(a, b, [](uint32_t a, uint32_t b) { return a | b; }, [](int a, int b) {return (a == -1 || b == -1); });
}

big_integer& big_integer::operator|=(big_integer const& rhs) {
    return  (*this = *this | rhs);
}

big_integer operator^(big_integer const& a, big_integer const& b) {
	return big_integer::do_logical_operation(a, b, [](uint32_t a, uint32_t b) { return a ^ b; }, [](int a, int b) {return (((a == 1 || a == 0) && b == -1) || (a == -1 && (b == 1 || b == 0))); });
}

big_integer& big_integer::operator^=(big_integer const& rhs) {
    return  (*this = *this ^ rhs);
}
