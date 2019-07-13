#include <iostream>

int main() {
    freopen("mutation.in", "r", stdin);
    freopen("mutation.out", "w", stdout);

    size_t bit_size, n;
    std::cin >> bit_size >> n;

    std::cout.precision(10);
    for (size_t i = 0; i < n; i++) {
        std::string a, b;
        std::cin >> a >> b;

        long double p = 1;
        for (size_t j = 0; j < bit_size; j++) {
            if (a[j] != b[j]) p *= 1. / bit_size;
            else p *= 1 - 1. / bit_size;
        }
        std::cout << p << std::endl;
    }
    return 0;
}
