#include <iostream>
#include <vector>

std::string file_name = "";
int main() {
#ifndef NDEBUG
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
#endif

    return 0;
}