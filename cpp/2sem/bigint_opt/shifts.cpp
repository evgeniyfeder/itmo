#include "big_integer.h"

big_integer operator<<(big_integer const& a, int b) {
	/* Bad cases */
	if (b == 0)
		return big_integer(a);
	else if (b < 0) {
		return a >> (-b);
	}
	
	uint32_t ost = 0;
	big_integer result; result.digits.do_empty();

	while (uint32_t(b) >= big_integer::type_bits) {
		result.digits.push_back(0);
		b -= big_integer::type_bits;
	}

	uint32_t ost_size = b;
	for (size_t i = 0; i < a.digits.get_size(); i++) {
		ost = a.digits[i] >> (big_integer::type_bits - ost_size);
		result.digits.push_back(ost + (a.digits[i] << ost_size));
	}

	if (ost != 0)
		result.digits.push_back(ost);

	result.sign = a.sign;
	return result;
}

big_integer operator>>(big_integer const& a, int b) {
	if (b == 0)
		return big_integer(a);
	else if (b < 0) {
		return a >> (-b);
	}
	big_integer a_adding = a.to_adding_code();

	if ((size_t)b > a_adding.digits.get_size() * big_integer::type_bits)
		return big_integer(0);

	uint32_t ost = 0, ost_size = big_integer::type_bits - (b % big_integer::type_bits);
	big_integer result; result.digits.do_empty();

	for (size_t i = 0; i < a_adding.digits.get_size() - 1; i++) {
		if (uint32_t(b) >= big_integer::type_bits) {
			b -= big_integer::type_bits;
			continue;
		}
		// reserve data from next block
		uint32_t next_part = a_adding.digits[i + 1] & ((1 << (big_integer::type_bits - ost_size)) - 1);
		result.digits.push_back((a_adding.digits[i] >> (big_integer::type_bits - ost_size)) + (next_part << ost_size));
		ost_size = big_integer::type_bits - ost_size;
	}
	ost = a_adding.digits[a_adding.digits.get_size() - 1] >> (big_integer::type_bits - ost_size);

	if (ost_size != 0) {
		ost |= (((a.sign > 0 ? 0 : 1) << (big_integer::type_bits - ost_size)) - (a.sign > 0 ? 0 : 1)) << ost_size;
		if (ost != INT32_MAX)
			result.digits.push_back(ost);	
	}
	else if (result.digits.get_size() == 0)
		result.digits.push_back(0);

	result.sign = a.sign;
	result.normalize();
	return result.to_sign_bit();
}

big_integer& big_integer::operator<<=(int rhs) {
	return (*this = *this << rhs);
}
big_integer& big_integer::operator>>=(int rhs) {
	return (*this = *this >> rhs);
}