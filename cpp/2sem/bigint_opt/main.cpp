#include <iostream>
#include "big_integer.h"

int main() {
	big_integer a("10000000000000000000000000000000000000000000000000");
	big_integer b("10000000000");
	std::cout << a;
	std::cout << b;
	std::cout << a - b;
	return 0;
}