#include <string>
#include <iostream>
#include <vector>
std::string file_name = "substrcmp";

using hash_type = uint32_t;
int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	std::string str;
	std::cin >> str;

	std::vector<hash_type> hashes(str.size()), p_pow(str.size());

	p_pow[0] = 1;
	const hash_type p = 1000000007;
	for (size_t i = 1; i < hashes.size(); i++) {
		p_pow[i] = p_pow[i - 1] * p;
	}

	hashes[0] = str[0] - 'a' + 1;
	for (size_t i = 1; i < hashes.size(); i++) {
		hashes[i] = hashes[i - 1] + (str[i] - 'a' + 1) * p_pow[i];
	}

	size_t n;
	std::cin >> n;

	for (size_t i = 0; i < n; i++) {
		size_t a, b, c, d;
		std::cin >> a >> b >> c >> d;

		if (b - a != d - c) {
			std::cout << "No" << '\n';
			continue;
		}

		hash_type h_ab = hashes[b - 1];
		if (a != 1) h_ab -= hashes[a - 2];

		hash_type h_cd = hashes[d - 1];
		if (c != 1) h_cd -= hashes[c - 2];

		if ((a <= c && h_ab * p_pow[c - a] == h_cd) || (a > c && h_cd * p_pow[a - c] == h_ab)) {
			std::cout << "Yes" << '\n';
			continue;
		}
		std::cout << "No" << '\n';
	}
}