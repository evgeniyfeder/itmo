#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

std::string file_name = "search3";

std::vector<int> count_prefix(const std::string &str) {
	std::vector<int> result(str.size());
	
	result[0] = 0;
	for (int i = 1; i < (int)str.size(); i++) {
		int l = result[i - 1];

		while (l > 0 && str[l] != str[i]) {
			l = result[l - 1];
		}

		if (str[l] == str[i])
			l++;
		result[i] = l;
	}

	return result;
}

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

	std::string text, w;
	std::cin >> w >> text;

	std::string templ1 = w + '#' + text;
	auto pf = count_z(templ1);

	std::reverse(text.begin(), text.end());
	std::reverse(w.begin(), w.end());

	std::string templ2 = w + '#' + text;
	auto zf = count_z(templ2);
	
	std::vector<int> result;

	for (int i = 0; i < (int)text.size() - (int)w.size() + 1; i++) {
		int ip = (int)w.size() + 1 + i, iz = (int)templ2.size() - 1 - i - (int)w.size() + 1;

		if (pf[ip] + 1 + zf[iz] >= (int)w.size())
			result.push_back(i + 1);
	}

	std::cout << result.size() << '\n';
	for (auto &&x: result) {
		std::cout << x << " ";
	}
	return 0;
}