#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <vector>
#include <cstddef>
#include <iosfwd>
#include <cstdint>
#include "vector/my_vector.h"

class big_integer
{
private:
    my_vector digits;
    int sign;
	static const size_t type_bits = sizeof(uint32_t) * 8;
	static const uint64_t base = uint64_t(UINT32_MAX) + 1;
	static const uint32_t max_num = UINT32_MAX;

	static big_integer do_logical_operation(big_integer const& a, big_integer const& b, uint32_t(*f)(uint32_t a, uint32_t b), bool(*get_sign)(int a, int b));
	void add_with_shift(big_integer const& a, int shift);

	big_integer reverse_like_adding_code() const;
	big_integer to_adding_code() const;
	big_integer to_sign_bit() const;

	void normalize();
	void check_for_zero();

	big_integer mul_short(uint32_t b) const;
	big_integer div_short(uint32_t b, uint32_t *ost) const;

    int check_prefix(big_integer const& checker, uint32_t begin_ind) const;
	void sub_prefix(big_integer const& b, size_t begin_ind);
	
public:
    big_integer();
    big_integer(big_integer const& other);
	big_integer(int a);
	~big_integer();
    explicit big_integer(std::string const& str);

    big_integer& operator=(big_integer const& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);

	friend big_integer operator&(big_integer const& a, big_integer const& b);
	friend big_integer operator|(big_integer const& a, big_integer const& b);
	friend big_integer operator^(big_integer const& a, big_integer const& b);

	friend big_integer operator<<(big_integer const& a, int b);
	friend big_integer operator>>(big_integer const& a, int b);

	friend big_integer operator+(big_integer const& a, big_integer const& b);
	friend big_integer operator-(big_integer const& a, big_integer const& b);
	friend big_integer operator*(big_integer const& a, big_integer const& b);
	friend big_integer operator/(big_integer const& a, big_integer const& b);
	friend big_integer operator%(big_integer const& a, big_integer const& b);


    friend std::string to_string(big_integer const& a);
};

big_integer operator+(big_integer const& a, big_integer const& b);
big_integer operator-(big_integer const& a, big_integer const& b);
big_integer operator*(big_integer const& a, big_integer const& b);
big_integer operator/(big_integer const& a, big_integer const& b);
big_integer operator%(big_integer const& a, big_integer const& b);

big_integer operator&(big_integer const& a, big_integer const& b);
big_integer operator|(big_integer const& a, big_integer const& b);
big_integer operator^(big_integer const& a, big_integer const& b);

big_integer operator<<(big_integer const& a, int b);
big_integer operator>>(big_integer const& a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif // BIG_INTEGER_H
