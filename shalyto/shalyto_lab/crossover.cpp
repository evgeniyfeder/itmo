#include<iostream>
#include <vector>
#include <string>

std::string xor_string(std::string const & a, std::string const & b, size_t n) {
    std::string result;
    for (size_t i = 0; i < n; i++) {
        if (a[i] == b[i]) result.push_back('0');
        else result.push_back('1');
    }
    return result;
}

int main() {
    freopen("crossover.in", "r", stdin);
    freopen("crossover.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::vector<std::string> input;
    size_t n, bit_size;
    std::cin >> n >> bit_size;

    for (size_t i = 0; i < n;i++) {
        std::string a;
        std::cin >> a;
        input.emplace_back(std::move(a));
    }
    std::string s;
    std::cin >> s;

    // xor
    for (size_t i = 0; i < n; i++) {
        input[i] = xor_string(input[i], s, bit_size);

    }

    // 1-dim
    bool is_1_dim = false;
    size_t pref_ind_max = 0, suf_ind_max = bit_size - 1;
    for (size_t i = 0; i < n; i++) {
        std::string &a = input[i];
        size_t pref_ind = 0, suf_ind = bit_size - 1;

        while (a[pref_ind] == '0') pref_ind++;
        while (a[suf_ind] == '0') suf_ind--;
        pref_ind_max = std::max(pref_ind, pref_ind_max);
        suf_ind_max = std::min(suf_ind, suf_ind_max);
    }
    std::cout << (pref_ind_max + (bit_size - 1 - suf_ind_max) >= bit_size ? "YES" : "NO") << std::endl;

    // 2-dim
    std::vector<std::vector<size_t>> sublen(bit_size);
    for (size_t i = 0; i < n; i++) {
        size_t p1 = 0, p2 = 0;
        while (p1 < bit_size) {
            if (p2 < bit_size && sublen[i][p2] == '0') p2++;
            else if (sublen[i][p1] == '1') {
                sublen[i][p1] = 0;
                p1++;
                p2++;
            }
            else {
                sublen[i][p1] = p2 - p1;
                p1++;
            }
        }
    }

    std::vector<size_t> b(bit_size);
    for (size_t i = 0; i < n; i++) {
        b[i] = 0;
        for (size_t j = 0; j < bit_size; j++) {
            b[i] = std::max(b[i], sublen[j][i]);
        }
    }

    bool is_2_dim = false;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < bit_size; j++) {
        }
    }

    return 0;
}
