#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
std::string file_name = "period";

std::vector<int> count_z(const std::string &str) {
	std::vector<int> result(str.size());

	result[0] = 0;
	for (int i = 1, l = 0, r = 0; i < (int)str.size(); i++) {
		result[i] = std::max(0, std::min(r - i, result[i - l]));

		while (i + result[i] < (int)str.size() && str[result[i]] == str[i + result[i]])
			result[i]++;

		if (i + result[i] > r) {
			l = i;
			r = i + result[i];
		}
}

	return result;
}

int main() {
#ifdef _DEBUG
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen((file_name + ".in").c_str(), "r", stdin);
	freopen((file_name + ".out").c_str(), "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false);

	std::string s;
	std::cin >> s;

	auto zf = count_z(s);
	for (size_t i = 1; i < s.size(); i++) {
		if (s.size() % i == 0 && (size_t)zf[i] == s.size() - i) {
			std::cout << i;
			return 0;
		}
	}
	std::cout << s.size();
	return 0;
}