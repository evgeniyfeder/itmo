#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::string file_name = "keepcounted";

int count_prefix(std::vector<int> &result, const std::string &str) {
	int max = 0;

	result[0] = 0;
	for (size_t i = 1; i < str.size(); i++) {
		int l = result[i - 1];

		while (l > 0 && str[l] != str[i]) {
			l = result[l - 1];
		}

		if (str[l] == str[i])
			l++;
		result[i] = l;
		max = std::max(result[i], max);
	}
	return max;
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

	std::string text;
	std::cin >> text;

	std::string cur_s;
	cur_s += text[0];
	uint64_t res = 1;
	std::cout << res << '\n';

	std::vector<int> pf(text.size());
	for (size_t i = 1; i < text.size(); i++) {
		cur_s += text[i];
		std::reverse(cur_s.begin(), cur_s.end());

		;
		int max = count_prefix(pf, cur_s);

		res += cur_s.size() - max;
		std::reverse(cur_s.begin(), cur_s.end());
		std::cout << res << '\n';
	}
}